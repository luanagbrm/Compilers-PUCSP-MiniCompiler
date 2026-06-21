/*
 * sema.cpp - Static semantic analysis for Mini-Pascal
 * See sema.h for the contract.
 */
#include "sema.h"
#include <algorithm>
#include <iostream>

namespace {
// Identifiers in Pascal are case-insensitive, so symbols are stored lowercase.
std::string toLower(const std::string& s) {
    std::string r = s;
    std::transform(r.begin(), r.end(), r.begin(), ::tolower);
    return r;
}
}  // namespace

const char* Sema::tyName(Ty t) {
    switch (t) {
        case Ty::Integer: return "integer";
        case Ty::Boolean: return "boolean";
        case Ty::String:  return "string";
        case Ty::Error:   return "<error>";
    }
    return "<error>";
}

Sema::Ty Sema::fromTypeKind(TypeKind tk) {
    return tk == TypeKind::Boolean ? Ty::Boolean : Ty::Integer;
}

void Sema::error(int line, const std::string& msg) {
    std::cerr << "[sema] line " << line << ": " << msg << "\n";
    errors++;
}

void Sema::pushScope() { scopes.emplace_back(); }
void Sema::popScope()  { if (!scopes.empty()) scopes.pop_back(); }

bool Sema::declare(const std::string& name, const Symbol& sym, int line) {
    auto key = toLower(name);
    auto& current = scopes.back();
    if (current.count(key)) {
        error(line, "redeclaration of '" + name + "' in the same scope");
        return false;
    }
    current[key] = sym;
    return true;
}

const Sema::Symbol* Sema::lookup(const std::string& name) const {
    auto key = toLower(name);
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto found = it->find(key);
        if (found != it->end()) return &found->second;
    }
    return nullptr;
}

bool Sema::analyze(Program* prog) {
    if (!prog) {
        error(0, "no program AST");
        return false;
    }
    pushScope();  // global scope

    // Pre-declare the one built-in: paramstr(integer): integer
    Symbol paramstr{Symbol::Kind::Function, Ty::Integer, {Ty::Integer}};
    scopes.back()[ "paramstr" ] = paramstr;

    // First pass: declare globals (vars + function/procedure signatures) so
    // that bodies can reference any subprogram regardless of order.
    for (auto* d : prog->decls) checkDecl(d);

    // Second pass: type-check function/procedure bodies now that all
    // signatures are known.
    for (auto* d : prog->decls)
        if (d->kind != DeclKind::Var) checkSubprogBody(d);

    // Main body is checked in the global scope.
    if (prog->body) checkStmt(prog->body);

    popScope();
    return errors == 0;
}

void Sema::checkDecl(Decl* d) {
    if (d->kind == DeclKind::Var) {
        Symbol s{Symbol::Kind::Var, fromTypeKind(d->type), {}};
        declare(d->name, s, /*line*/ 0);
        return;
    }

    // Function or Procedure: record signature in the global scope.
    Symbol sig;
    sig.kind = (d->kind == DeclKind::Function) ? Symbol::Kind::Function
                                               : Symbol::Kind::Procedure;
    sig.type = (d->kind == DeclKind::Function) ? fromTypeKind(d->type)
                                               : Ty::Error;  // unused for procs
    for (auto& p : d->params) sig.paramTypes.push_back(fromTypeKind(p.type));
    declare(d->name, sig, 0);
}

void Sema::checkSubprogBody(Decl* d) {
    pushScope();
    auto savedFunc = currentFunc;
    auto savedRet  = currentFuncReturn;

    currentFunc = toLower(d->name);
    currentFuncReturn = (d->kind == DeclKind::Function)
        ? fromTypeKind(d->type) : Ty::Error;

    // Parameters
    for (auto& p : d->params) {
        Symbol s{Symbol::Kind::Param, fromTypeKind(p.type), {}};
        declare(p.name, s, 0);
    }

    // Local variables
    for (auto& lv : d->localVars) {
        Symbol s{Symbol::Kind::Var, fromTypeKind(lv.second), {}};
        declare(lv.first, s, 0);
    }

    // Inside a function body, the function's own name behaves as a writable
    // pseudo-variable holding the return value (Pascal idiom).
    if (d->kind == DeclKind::Function) {
        Symbol s{Symbol::Kind::Var, fromTypeKind(d->type), {}};
        // Declared into the local scope so it shadows nothing at the top level.
        scopes.back()[currentFunc] = s;
    }

    if (d->body) checkStmt(d->body);

    currentFunc = savedFunc;
    currentFuncReturn = savedRet;
    popScope();
}

void Sema::checkStmt(Stmt* s) {
    if (!s) return;
    switch (s->kind) {
        case StmtKind::Block:
            for (auto* sub : s->stmts) checkStmt(sub);
            break;

        case StmtKind::Assign: {
            const Symbol* sym = lookup(s->name);
            if (!sym) {
                error(s->line, "assignment to undeclared identifier '" + s->name + "'");
                checkExpr(s->expr);  // still walk RHS for cascading errors
                break;
            }
            if (sym->kind == Symbol::Kind::Procedure ||
                (sym->kind == Symbol::Kind::Function && toLower(s->name) != currentFunc)) {
                error(s->line, "cannot assign to "
                      + std::string(sym->kind == Symbol::Kind::Procedure ? "procedure" : "function")
                      + " '" + s->name + "'");
                checkExpr(s->expr);
                break;
            }
            Ty rhs = checkExpr(s->expr);
            if (rhs != Ty::Error && rhs != sym->type) {
                error(s->line, "cannot assign " + std::string(tyName(rhs))
                      + " to '" + s->name + "' of type " + tyName(sym->type));
            }
            break;
        }

        case StmtKind::If: {
            Ty c = checkExpr(s->cond);
            if (c != Ty::Error && c != Ty::Boolean)
                error(s->line, "if-condition must be boolean, got " + std::string(tyName(c)));
            checkStmt(s->thenStmt);
            checkStmt(s->elseStmt);
            break;
        }

        case StmtKind::While: {
            Ty c = checkExpr(s->cond);
            if (c != Ty::Error && c != Ty::Boolean)
                error(s->line, "while-condition must be boolean, got " + std::string(tyName(c)));
            checkStmt(s->body);
            break;
        }

        case StmtKind::For: {
            const Symbol* sym = lookup(s->name);
            if (!sym)
                error(s->line, "for-loop variable '" + s->name + "' is undeclared");
            else if (sym->type != Ty::Integer)
                error(s->line, "for-loop variable '" + s->name + "' must be integer");
            Ty start = checkExpr(s->expr);
            Ty end   = checkExpr(s->endExpr);
            if (start != Ty::Error && start != Ty::Integer)
                error(s->line, "for-loop start expression must be integer");
            if (end != Ty::Error && end != Ty::Integer)
                error(s->line, "for-loop end expression must be integer");
            checkStmt(s->body);
            break;
        }

        case StmtKind::Write: {
            for (auto* a : s->args) {
                Ty t = checkExpr(a);
                if (t == Ty::Error) continue;
                if (t != Ty::Integer && t != Ty::Boolean && t != Ty::String)
                    error(a->line, "write/writeln argument has unsupported type "
                          + std::string(tyName(t)));
            }
            break;
        }

        case StmtKind::ProcCall:
            // Arity/types validated by checkCall; needsResult=false for procs.
            checkCall(s->name, s->args, s->line, /*needsResult=*/false);
            break;

        case StmtKind::Exit: {
            if (currentFunc.empty()) {
                error(s->line, "exit() can only be used inside a function or procedure");
                if (s->expr) checkExpr(s->expr);
                break;
            }
            if (currentFuncReturn == Ty::Error) {
                // Inside a procedure: exit() without arguments only.
                if (s->expr)
                    error(s->line, "exit() in a procedure must not take an argument");
                break;
            }
            // Inside a function: exit must carry a value of the return type.
            if (!s->expr) {
                error(s->line, "exit() in function '" + currentFunc + "' requires a value");
                break;
            }
            Ty got = checkExpr(s->expr);
            if (got != Ty::Error && got != currentFuncReturn) {
                error(s->line, "exit() returns " + std::string(tyName(got))
                      + ", expected " + tyName(currentFuncReturn));
            }
            break;
        }

        default: break;
    }
}

Sema::Ty Sema::checkExpr(Expr* e) {
    if (!e) return Ty::Error;
    switch (e->kind) {
        case ExprKind::IntLit:    return Ty::Integer;
        case ExprKind::BoolLit:   return Ty::Boolean;
        case ExprKind::StringLit: return Ty::String;
        case ExprKind::Ident: {
            const Symbol* sym = lookup(e->name);
            if (!sym) {
                error(e->line, "undeclared identifier '" + e->name + "'");
                return Ty::Error;
            }
            if (sym->kind == Symbol::Kind::Procedure) {
                error(e->line, "procedure '" + e->name + "' used as a value");
                return Ty::Error;
            }
            // A function used as a bare identifier inside its own body refers
            // to its return-value slot; outside that body it requires `()`.
            if (sym->kind == Symbol::Kind::Function && toLower(e->name) != currentFunc) {
                error(e->line, "function '" + e->name + "' used without arguments");
                return Ty::Error;
            }
            return sym->type;
        }
        case ExprKind::BinOp:    return checkBinOp(e);
        case ExprKind::UnaryOp: {
            Ty t = checkExpr(e->left);
            if (t == Ty::Error) return Ty::Error;
            if (e->unaryOp == UnaryOpKind::Neg) {
                if (t != Ty::Integer) {
                    error(e->line, "unary '-' requires integer, got " + std::string(tyName(t)));
                    return Ty::Error;
                }
                return Ty::Integer;
            }
            // Not
            if (t != Ty::Boolean) {
                error(e->line, "'not' requires boolean, got " + std::string(tyName(t)));
                return Ty::Error;
            }
            return Ty::Boolean;
        }
        case ExprKind::FuncCall:
            return checkCall(e->name, e->args, e->line, /*needsResult=*/true);
    }
    return Ty::Error;
}

Sema::Ty Sema::checkBinOp(Expr* e) {
    Ty L = checkExpr(e->left);
    Ty R = checkExpr(e->right);
    if (L == Ty::Error || R == Ty::Error) return Ty::Error;

    auto requireBoth = [&](Ty want, const char* opName) -> bool {
        if (L != want || R != want) {
            error(e->line, std::string(opName) + " requires "
                  + tyName(want) + " operands, got "
                  + tyName(L) + " and " + tyName(R));
            return false;
        }
        return true;
    };

    switch (e->binOp) {
        case BinOpKind::Add:
        case BinOpKind::Sub:
        case BinOpKind::Mul:
        case BinOpKind::Div:
        case BinOpKind::Mod:
            return requireBoth(Ty::Integer,
                e->binOp == BinOpKind::Add ? "+" :
                e->binOp == BinOpKind::Sub ? "-" :
                e->binOp == BinOpKind::Mul ? "*" :
                e->binOp == BinOpKind::Div ? "div" : "mod") ? Ty::Integer : Ty::Error;

        case BinOpKind::And:
        case BinOpKind::Or:
            return requireBoth(Ty::Boolean,
                e->binOp == BinOpKind::And ? "and" : "or") ? Ty::Boolean : Ty::Error;

        case BinOpKind::Eq:
        case BinOpKind::Neq:
        case BinOpKind::Lt:
        case BinOpKind::Gt:
        case BinOpKind::Lte:
        case BinOpKind::Gte:
            if (L != R || (L != Ty::Integer && L != Ty::Boolean)) {
                error(e->line, "comparison operands must be matching integer or boolean, got "
                      + std::string(tyName(L)) + " and " + tyName(R));
                return Ty::Error;
            }
            return Ty::Boolean;
    }
    return Ty::Error;
}

Sema::Ty Sema::checkCall(const std::string& name,
                         const std::vector<ExprPtr>& args,
                         int line, bool needsResult) {
    const Symbol* sym = lookup(name);
    if (!sym) {
        error(line, std::string(needsResult ? "call to undeclared function '"
                                            : "call to undeclared procedure '")
              + name + "'");
        return Ty::Error;
    }
    bool isFunc = sym->kind == Symbol::Kind::Function;
    bool isProc = sym->kind == Symbol::Kind::Procedure;
    if (!isFunc && !isProc) {
        error(line, "'" + name + "' is not callable");
        return Ty::Error;
    }
    if (needsResult && !isFunc) {
        error(line, "procedure '" + name + "' cannot be used in an expression");
        return Ty::Error;
    }
    if (!needsResult && !isProc && !isFunc) {
        error(line, "'" + name + "' is not a procedure");
        return Ty::Error;
    }

    if (sym->paramTypes.size() != args.size()) {
        error(line, std::string(isFunc ? "function '" : "procedure '") + name
              + "' expects " + std::to_string(sym->paramTypes.size())
              + " argument(s), got " + std::to_string(args.size()));
        // Still walk the args to surface nested errors.
        for (auto* a : args) checkExpr(a);
        return isFunc ? sym->type : Ty::Error;
    }

    for (size_t i = 0; i < args.size(); ++i) {
        Ty got = checkExpr(args[i]);
        Ty want = sym->paramTypes[i];
        if (got != Ty::Error && got != want) {
            error(args[i]->line, "argument " + std::to_string(i + 1) + " of '"
                  + name + "' expects " + tyName(want)
                  + ", got " + tyName(got));
        }
    }
    return isFunc ? sym->type : Ty::Error;
}
