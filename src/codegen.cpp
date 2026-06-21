/*
 * codegen.cpp - LLVM IR code generation for Mini-Pascal
 * Walks the AST and emits LLVM IR using the IRBuilder API
 */
#include "codegen.h"
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LegacyPassManager.h>
#include <iostream>
#include <algorithm>

// Utility: lowercase a string for case-insensitive comparison
static std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}

CodeGen::CodeGen() : builder(context) {
    module = std::make_unique<llvm::Module>("minipc", context);
}

llvm::Type* CodeGen::getLLVMType(TypeKind tk) {
    switch (tk) {
        case TypeKind::Integer: return llvm::Type::getInt32Ty(context);
        case TypeKind::Boolean: return llvm::Type::getInt1Ty(context);
    }
    return llvm::Type::getInt32Ty(context);
}

llvm::AllocaInst* CodeGen::createAlloca(llvm::Function* f, const std::string& name, llvm::Type* ty) {
    llvm::IRBuilder<> tmp(&f->getEntryBlock(), f->getEntryBlock().begin());
    return tmp.CreateAlloca(ty, nullptr, name);
}

llvm::Function* CodeGen::declarePrintf() {
    if (auto* f = module->getFunction("printf")) return f;
    auto* ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(context),
        {llvm::PointerType::get(context, 0)}, true);
    return llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "printf", module.get());
}

llvm::Function* CodeGen::declareAtoi() {
    if (auto* f = module->getFunction("atoi")) return f;
    auto* ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(context),
        {llvm::PointerType::get(context, 0)}, false);
    return llvm::Function::Create(ft, llvm::Function::ExternalLinkage, "atoi", module.get());
}

bool CodeGen::generate(Program* prog) {
    // Declare all functions first (forward declarations)
    for (auto* d : prog->decls) {
        if (d->kind == DeclKind::Function || d->kind == DeclKind::Procedure) {
            std::vector<llvm::Type*> paramTypes;
            for (auto& p : d->params)
                paramTypes.push_back(getLLVMType(p.type));
            llvm::Type* retTy = (d->kind == DeclKind::Function) ?
                getLLVMType(d->type) : llvm::Type::getVoidTy(context);
            auto* ft = llvm::FunctionType::get(retTy, paramTypes, false);
            llvm::Function::Create(ft, llvm::Function::ExternalLinkage, toLower(d->name), module.get());
        }
    }

    // Generate function/procedure bodies
    for (auto* d : prog->decls) {
        if (d->kind == DeclKind::Function || d->kind == DeclKind::Procedure)
            genFuncDecl(d);
    }

    // Generate main: int main(int argc, char** argv)
    // Note: With opaque pointers (LLVM 15+), all pointer types are equivalent.
    auto* charPtrPtrTy = llvm::PointerType::get(context, 0);
    auto* mainTy = llvm::FunctionType::get(llvm::Type::getInt32Ty(context),
        {llvm::Type::getInt32Ty(context), charPtrPtrTy}, false);
    auto* mainFunc = llvm::Function::Create(mainTy, llvm::Function::ExternalLinkage, "main", module.get());

    auto* entry = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entry);
    currentFunc = mainFunc;
    funcRetVal = nullptr;
    currentFuncName = "";
    exitBlock = nullptr;

    // Store argc and argv
    auto argIt = mainFunc->arg_begin();
    llvm::Value* argc = &*argIt; argc->setName("argc"); argIt++;
    llvm::Value* argv = &*argIt; argv->setName("argv");

    auto* argcAlloca = createAlloca(mainFunc, "argc", llvm::Type::getInt32Ty(context));
    auto* argvAlloca = createAlloca(mainFunc, "argv", charPtrPtrTy);
    builder.CreateStore(argc, argcAlloca);
    builder.CreateStore(argv, argvAlloca);

    // Global vars for main scope
    auto oldVars = namedValues;
    namedValues.clear();
    namedValues["argc"] = argcAlloca;
    namedValues["argv"] = argvAlloca;

    // Declare global variables
    for (auto* d : prog->decls) {
        if (d->kind == DeclKind::Var) {
            auto* alloca = createAlloca(mainFunc, toLower(d->name), getLLVMType(d->type));
            builder.CreateStore(llvm::ConstantInt::get(getLLVMType(d->type), 0), alloca);
            namedValues[toLower(d->name)] = alloca;
        }
    }

    // Generate the main body
    genStmt(prog->body);

    builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0));

    namedValues = oldVars;

    // Verify
    std::string errStr;
    llvm::raw_string_ostream errStream(errStr);
    if (llvm::verifyModule(*module, &errStream)) {
        std::cerr << "LLVM IR verification failed:\n" << errStr << "\n";
        module->print(llvm::errs(), nullptr);
        return false;
    }
    return true;
}

void CodeGen::genFuncDecl(Decl* d) {
    std::string fname = toLower(d->name);
    llvm::Function* func = module->getFunction(fname);
    if (!func) return;

    auto* entry = llvm::BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(entry);

    auto oldVars = namedValues;
    auto* oldFunc = currentFunc;
    auto* oldRetVal = funcRetVal;
    auto oldFuncName = currentFuncName;
    auto* oldExitBlock = exitBlock;

    currentFunc = func;
    currentFuncName = fname;
    namedValues.clear();

    // Create exit block for early return via exit(...)
    exitBlock = llvm::BasicBlock::Create(context, "exit", func);

    // Allocate return value for functions
    if (d->kind == DeclKind::Function) {
        funcRetVal = createAlloca(func, fname + ".retval", getLLVMType(d->type));
        builder.CreateStore(llvm::ConstantInt::get(getLLVMType(d->type), 0), funcRetVal);
        namedValues[fname] = funcRetVal; // Pascal: assign to function name = set return value
    } else {
        funcRetVal = nullptr;
    }

    // Allocate and store parameters
    unsigned i = 0;
    for (auto& arg : func->args()) {
        auto& param = d->params[i];
        std::string pname = toLower(param.name);
        auto* alloca = createAlloca(func, pname, getLLVMType(param.type));
        builder.CreateStore(&arg, alloca);
        namedValues[pname] = alloca;
        i++;
    }

    // Allocate local variables
    if (d->localVars.size() > 0) {
        for (auto& lv : d->localVars) {
            std::string vname = toLower(lv.first);
            auto* alloca = createAlloca(func, vname, getLLVMType(lv.second));
            builder.CreateStore(llvm::ConstantInt::get(getLLVMType(lv.second), 0), alloca);
            namedValues[vname] = alloca;
        }
    }

    // Generate body
    genStmt(d->body);

    // Jump to exit block from wherever we are (if block not terminated)
    if (!builder.GetInsertBlock()->getTerminator())
        builder.CreateBr(exitBlock);

    // Exit block: return
    builder.SetInsertPoint(exitBlock);
    if (d->kind == DeclKind::Function) {
        auto* retVal = builder.CreateLoad(getLLVMType(d->type), funcRetVal, "retval");
        builder.CreateRet(retVal);
    } else {
        builder.CreateRetVoid();
    }

    // Restore
    namedValues = oldVars;
    currentFunc = oldFunc;
    funcRetVal = oldRetVal;
    currentFuncName = oldFuncName;
    exitBlock = oldExitBlock;
}

void CodeGen::genStmt(Stmt* s) {
    if (!s) return;
    switch (s->kind) {
        case StmtKind::Block:    genBlock(s); break;
        case StmtKind::Assign:   genAssign(s); break;
        case StmtKind::If:       genIf(s); break;
        case StmtKind::While:    genWhile(s); break;
        case StmtKind::For:      genFor(s); break;
        case StmtKind::Write:    genWrite(s); break;
        case StmtKind::ProcCall: genProcCall(s); break;
        case StmtKind::Exit:     genExit(s); break;
        default: break;
    }
}

void CodeGen::genBlock(Stmt* s) {
    for (auto* st : s->stmts) {
        if (builder.GetInsertBlock()->getTerminator()) break;
        genStmt(st);
    }
}

void CodeGen::genAssign(Stmt* s) {
    std::string name = toLower(s->name);
    auto* val = genExpr(s->expr);
    if (!val) return;

    auto it = namedValues.find(name);
    if (it == namedValues.end()) {
        std::cerr << "Error: undefined variable '" << s->name << "' at line " << s->line << "\n";
        return;
    }
    builder.CreateStore(val, it->second);
}

void CodeGen::genIf(Stmt* s) {
    auto* cond = genExpr(s->cond);
    if (!cond) return;

    // Ensure boolean (i1)
    if (cond->getType()->isIntegerTy(32))
        cond = builder.CreateICmpNE(cond, llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0), "tobool");

    auto* thenBB = llvm::BasicBlock::Create(context, "then", currentFunc);
    auto* elseBB = llvm::BasicBlock::Create(context, "else", currentFunc);
    auto* mergeBB = llvm::BasicBlock::Create(context, "ifmerge", currentFunc);

    builder.CreateCondBr(cond, thenBB, elseBB);

    builder.SetInsertPoint(thenBB);
    genStmt(s->thenStmt);
    if (!builder.GetInsertBlock()->getTerminator())
        builder.CreateBr(mergeBB);

    builder.SetInsertPoint(elseBB);
    if (s->elseStmt) genStmt(s->elseStmt);
    if (!builder.GetInsertBlock()->getTerminator())
        builder.CreateBr(mergeBB);

    builder.SetInsertPoint(mergeBB);
}

void CodeGen::genWhile(Stmt* s) {
    auto* condBB = llvm::BasicBlock::Create(context, "while.cond", currentFunc);
    auto* bodyBB = llvm::BasicBlock::Create(context, "while.body", currentFunc);
    auto* endBB = llvm::BasicBlock::Create(context, "while.end", currentFunc);

    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);

    auto* cond = genExpr(s->cond);
    if (cond->getType()->isIntegerTy(32))
        cond = builder.CreateICmpNE(cond, llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0), "tobool");
    builder.CreateCondBr(cond, bodyBB, endBB);

    builder.SetInsertPoint(bodyBB);
    genStmt(s->body);
    if (!builder.GetInsertBlock()->getTerminator())
        builder.CreateBr(condBB);

    builder.SetInsertPoint(endBB);
}

void CodeGen::genFor(Stmt* s) {
    std::string varName = toLower(s->name);
    auto* startVal = genExpr(s->expr);
    auto* endVal = genExpr(s->endExpr);

    auto it = namedValues.find(varName);
    if (it == namedValues.end()) {
        std::cerr << "Error: undefined for-loop variable '" << s->name << "'\n";
        return;
    }
    auto* varAlloca = it->second;
    builder.CreateStore(startVal, varAlloca);

    auto* condBB = llvm::BasicBlock::Create(context, "for.cond", currentFunc);
    auto* bodyBB = llvm::BasicBlock::Create(context, "for.body", currentFunc);
    auto* endBB = llvm::BasicBlock::Create(context, "for.end", currentFunc);

    builder.CreateBr(condBB);
    builder.SetInsertPoint(condBB);

    auto* curVal = builder.CreateLoad(llvm::Type::getInt32Ty(context), varAlloca, varName);
    llvm::Value* cond;
    if (s->forDir == ForDir::To)
        cond = builder.CreateICmpSLE(curVal, endVal, "for.cmp");
    else
        cond = builder.CreateICmpSGE(curVal, endVal, "for.cmp");
    builder.CreateCondBr(cond, bodyBB, endBB);

    builder.SetInsertPoint(bodyBB);
    genStmt(s->body);

    // Increment/decrement
    auto* cur = builder.CreateLoad(llvm::Type::getInt32Ty(context), varAlloca, "cur");
    llvm::Value* next;
    if (s->forDir == ForDir::To)
        next = builder.CreateAdd(cur, llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 1), "inc");
    else
        next = builder.CreateSub(cur, llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 1), "dec");
    builder.CreateStore(next, varAlloca);

    if (!builder.GetInsertBlock()->getTerminator())
        builder.CreateBr(condBB);

    builder.SetInsertPoint(endBB);
}

void CodeGen::genWrite(Stmt* s) {
    auto* printfFunc = declarePrintf();

    for (auto* arg : s->args) {
        if (arg->kind == ExprKind::StringLit) {
            // Print string literal
            auto* str = builder.CreateGlobalString(arg->strVal, "str");
            builder.CreateCall(printfFunc, {str});
        } else {
            // Print integer with %d
            auto* val = genExpr(arg);
            if (!val) continue;
            if (val->getType()->isIntegerTy(1))
                val = builder.CreateZExt(val, llvm::Type::getInt32Ty(context), "boolext");
            auto* fmt = builder.CreateGlobalString("%d", "fmt");
            builder.CreateCall(printfFunc, {fmt, val});
        }
    }

    if (s->writeLn) {
        auto* nl = builder.CreateGlobalString("\n", "nl");
        builder.CreateCall(printfFunc, {nl});
    }
}

void CodeGen::genProcCall(Stmt* s) {
    std::string fname = toLower(s->name);
    auto* func = module->getFunction(fname);
    if (!func) {
        std::cerr << "Error: undefined procedure '" << s->name
                  << "' at line " << s->line << "\n";
        return;
    }
    if (func->arg_size() != s->args.size()) {
        std::cerr << "Error: procedure '" << s->name << "' expects "
                  << func->arg_size() << " argument(s), got "
                  << s->args.size() << " at line " << s->line << "\n";
        return;
    }
    std::vector<llvm::Value*> args;
    for (auto* a : s->args) {
        auto* v = genExpr(a);
        if (v) args.push_back(v);
    }
    builder.CreateCall(func, args);
}

void CodeGen::genExit(Stmt* s) {
    // exit(expr) in a function sets return value and jumps to exit block
    if (s->expr && funcRetVal) {
        auto* val = genExpr(s->expr);
        builder.CreateStore(val, funcRetVal);
    }
    if (exitBlock)
        builder.CreateBr(exitBlock);
}

llvm::Value* CodeGen::genExpr(Expr* e) {
    if (!e) return nullptr;
    switch (e->kind) {
        case ExprKind::IntLit:
            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), e->intVal);
        case ExprKind::BoolLit:
            return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), e->boolVal ? 1 : 0);
        case ExprKind::StringLit:
            return builder.CreateGlobalString(e->strVal, "str");
        case ExprKind::Ident: {
            std::string name = toLower(e->name);
            auto it = namedValues.find(name);
            if (it == namedValues.end()) {
                std::cerr << "Error: undefined variable '" << e->name << "' at line " << e->line << "\n";
                return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
            }
            return builder.CreateLoad(it->second->getAllocatedType(), it->second, name);
        }
        case ExprKind::BinOp:
            return genBinOp(e);
        case ExprKind::UnaryOp: {
            auto* operand = genExpr(e->left);
            if (!operand) return nullptr;
            if (e->unaryOp == UnaryOpKind::Neg)
                return builder.CreateNeg(operand, "neg");
            else // Not
                return builder.CreateNot(operand, "not");
        }
        case ExprKind::FuncCall:
            return genFuncCall(e);
    }
    return nullptr;
}

llvm::Value* CodeGen::genBinOp(Expr* e) {
    auto* L = genExpr(e->left);
    auto* R = genExpr(e->right);
    if (!L || !R) return nullptr;

    // Promote booleans to i32 for arithmetic
    if (L->getType()->isIntegerTy(1) && R->getType()->isIntegerTy(32))
        L = builder.CreateZExt(L, llvm::Type::getInt32Ty(context));
    if (R->getType()->isIntegerTy(1) && L->getType()->isIntegerTy(32))
        R = builder.CreateZExt(R, llvm::Type::getInt32Ty(context));
    if (L->getType()->isIntegerTy(1) && R->getType()->isIntegerTy(1)) {
        // For comparison ops, keep as i1; for arithmetic, extend
        if (e->binOp == BinOpKind::Add || e->binOp == BinOpKind::Sub ||
            e->binOp == BinOpKind::Mul || e->binOp == BinOpKind::Div || e->binOp == BinOpKind::Mod) {
            L = builder.CreateZExt(L, llvm::Type::getInt32Ty(context));
            R = builder.CreateZExt(R, llvm::Type::getInt32Ty(context));
        }
    }

    switch (e->binOp) {
        case BinOpKind::Add: return builder.CreateAdd(L, R, "add");
        case BinOpKind::Sub: return builder.CreateSub(L, R, "sub");
        case BinOpKind::Mul: return builder.CreateMul(L, R, "mul");
        case BinOpKind::Div: return builder.CreateSDiv(L, R, "div");
        case BinOpKind::Mod: return builder.CreateSRem(L, R, "mod");
        case BinOpKind::Eq:  return builder.CreateICmpEQ(L, R, "eq");
        case BinOpKind::Neq: return builder.CreateICmpNE(L, R, "neq");
        case BinOpKind::Lt:  return builder.CreateICmpSLT(L, R, "lt");
        case BinOpKind::Gt:  return builder.CreateICmpSGT(L, R, "gt");
        case BinOpKind::Lte: return builder.CreateICmpSLE(L, R, "lte");
        case BinOpKind::Gte: return builder.CreateICmpSGE(L, R, "gte");
        case BinOpKind::And: return builder.CreateAnd(L, R, "and");
        case BinOpKind::Or:  return builder.CreateOr(L, R, "or");
    }
    return nullptr;
}

llvm::Value* CodeGen::genFuncCall(Expr* e) {
    std::string fname = toLower(e->name);

    // Built-in: paramstr(n) - gets argv[n] as integer via atoi
    // Returns 0 when n >= argc, so missing CLI args don't segfault.
    if (fname == "paramstr") {
        if (e->args.size() != 1) {
            std::cerr << "Error: paramstr expects 1 argument, got "
                      << e->args.size() << " at line " << e->line << "\n";
            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
        }
        auto* atoi = declareAtoi();
        auto* argcAlloca = namedValues["argc"];
        auto* argvAlloca = namedValues["argv"];
        if (!argvAlloca || !argcAlloca) {
            std::cerr << "Error: paramstr() only available in main scope at line "
                      << e->line << "\n";
            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
        }

        auto* i32Ty = llvm::Type::getInt32Ty(context);
        auto* idx = genExpr(e->args[0]);
        auto* argcVal = builder.CreateLoad(i32Ty, argcAlloca, "argc.val");

        // Bounds-check: if (idx >= argc) return 0
        auto* result = createAlloca(currentFunc, "paramstr.result", i32Ty);
        builder.CreateStore(llvm::ConstantInt::get(i32Ty, 0), result);

        auto* okBB    = llvm::BasicBlock::Create(context, "paramstr.ok",    currentFunc);
        auto* doneBB  = llvm::BasicBlock::Create(context, "paramstr.done",  currentFunc);
        auto* outOfRange = builder.CreateICmpSGE(idx, argcVal, "paramstr.oor");
        builder.CreateCondBr(outOfRange, doneBB, okBB);

        builder.SetInsertPoint(okBB);
        auto* argvPtr = builder.CreateLoad(
            llvm::PointerType::get(context, 0), argvAlloca, "argv");
        auto* elemPtr = builder.CreateGEP(
            llvm::PointerType::get(context, 0), argvPtr, idx, "argvelem");
        auto* strPtr = builder.CreateLoad(
            llvm::PointerType::get(context, 0), elemPtr, "argstr");
        auto* val = builder.CreateCall(atoi, {strPtr}, "argval");
        builder.CreateStore(val, result);
        builder.CreateBr(doneBB);

        builder.SetInsertPoint(doneBB);
        return builder.CreateLoad(i32Ty, result, "paramstr.val");
    }

    // User-defined function
    auto* func = module->getFunction(fname);
    if (!func) {
        std::cerr << "Error: undefined function '" << e->name
                  << "' at line " << e->line << "\n";
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
    }
    if (func->arg_size() != e->args.size()) {
        std::cerr << "Error: function '" << e->name << "' expects "
                  << func->arg_size() << " argument(s), got "
                  << e->args.size() << " at line " << e->line << "\n";
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context), 0);
    }
    std::vector<llvm::Value*> args;
    for (auto* a : e->args) {
        auto* v = genExpr(a);
        if (v) args.push_back(v);
    }
    return builder.CreateCall(func, args, "call");
}

bool CodeGen::writeToFile(const std::string& filename) {
    std::error_code ec;
    llvm::raw_fd_ostream out(filename, ec);
    if (ec) {
        std::cerr << "Error opening output file: " << ec.message() << "\n";
        return false;
    }
    module->print(out, nullptr);
    return true;
}

void CodeGen::dump() {
    module->print(llvm::outs(), nullptr);
}
