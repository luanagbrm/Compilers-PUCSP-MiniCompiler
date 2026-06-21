#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <map>
#include <string>

class CodeGen {
public:
    CodeGen();
    bool generate(Program* prog);
    bool writeToFile(const std::string& filename);
    void dump();

private:
    llvm::LLVMContext context;
    std::unique_ptr<llvm::Module> module;
    llvm::IRBuilder<> builder;

    // Symbol table: variable name -> alloca
    std::map<std::string, llvm::AllocaInst*> namedValues;
    // Current function being compiled
    llvm::Function* currentFunc = nullptr;
    // Return value alloca for functions (Pascal assigns to func name)
    llvm::AllocaInst* funcRetVal = nullptr;
    std::string currentFuncName;
    // Exit block for early return via exit(...)
    llvm::BasicBlock* exitBlock = nullptr;

    // Helpers
    llvm::Type* getLLVMType(TypeKind tk);
    llvm::AllocaInst* createAlloca(llvm::Function* f, const std::string& name, llvm::Type* ty);
    llvm::Function* declarePrintf();
    llvm::Function* declareAtoi();

    // Code generation
    void genDecl(Decl* d);
    void genFuncDecl(Decl* d);
    void genStmt(Stmt* s);
    void genBlock(Stmt* s);
    void genAssign(Stmt* s);
    void genIf(Stmt* s);
    void genWhile(Stmt* s);
    void genFor(Stmt* s);
    void genWrite(Stmt* s);
    void genProcCall(Stmt* s);
    void genExit(Stmt* s);
    llvm::Value* genExpr(Expr* e);
    llvm::Value* genBinOp(Expr* e);
    llvm::Value* genFuncCall(Expr* e);
};

#endif // CODEGEN_H
