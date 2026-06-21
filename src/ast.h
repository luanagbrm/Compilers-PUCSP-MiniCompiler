#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>

// Forward declarations
struct Expr;
struct Stmt;
struct Decl;

using ExprPtr = Expr*;
using StmtPtr = Stmt*;
using ExprList = std::vector<ExprPtr>;
using StmtList = std::vector<StmtPtr>;

// ===== EXPRESSIONS =====

enum class ExprKind {
    IntLit, BoolLit, StringLit, Ident,
    BinOp, UnaryOp, FuncCall
};

enum class BinOpKind {
    Add, Sub, Mul, Div, Mod,
    Eq, Neq, Lt, Gt, Lte, Gte,
    And, Or
};

enum class UnaryOpKind { Neg, Not };

struct Expr {
    ExprKind kind;
    int intVal;
    bool boolVal;
    std::string strVal;
    std::string name;
    BinOpKind binOp;
    UnaryOpKind unaryOp;
    ExprPtr left = nullptr;
    ExprPtr right = nullptr;
    ExprList args;
    int line = 0;
};

inline ExprPtr mkIntLit(int v, int line) {
    auto e = new Expr(); e->kind = ExprKind::IntLit; e->intVal = v; e->line = line; return e;
}
inline ExprPtr mkBoolLit(bool v, int line) {
    auto e = new Expr(); e->kind = ExprKind::BoolLit; e->boolVal = v; e->line = line; return e;
}
inline ExprPtr mkStringLit(const std::string& s, int line) {
    auto e = new Expr(); e->kind = ExprKind::StringLit; e->strVal = s; e->line = line; return e;
}
inline ExprPtr mkIdent(const std::string& n, int line) {
    auto e = new Expr(); e->kind = ExprKind::Ident; e->name = n; e->line = line; return e;
}
inline ExprPtr mkBinOp(BinOpKind op, ExprPtr l, ExprPtr r, int line) {
    auto e = new Expr(); e->kind = ExprKind::BinOp; e->binOp = op; e->left = l; e->right = r; e->line = line; return e;
}
inline ExprPtr mkUnaryOp(UnaryOpKind op, ExprPtr operand, int line) {
    auto e = new Expr(); e->kind = ExprKind::UnaryOp; e->unaryOp = op; e->left = operand; e->line = line; return e;
}
inline ExprPtr mkFuncCall(const std::string& name, ExprList* args, int line) {
    auto e = new Expr(); e->kind = ExprKind::FuncCall; e->name = name;
    if (args) { e->args = *args; delete args; }
    e->line = line; return e;
}

// ===== STATEMENTS =====

enum class StmtKind {
    Assign, If, While, For, ProcCall,
    Write, WriteLn, Block, Exit
};

enum class ForDir { To, DownTo };

struct Stmt {
    StmtKind kind;
    std::string name;
    ExprPtr expr = nullptr;
    ExprPtr cond = nullptr;
    ExprPtr endExpr = nullptr;
    StmtPtr thenStmt = nullptr;
    StmtPtr elseStmt = nullptr;
    StmtPtr body = nullptr;
    StmtList stmts;
    ExprList args;
    ForDir forDir = ForDir::To;
    bool writeLn = false;
    int line = 0;
};

inline StmtPtr mkAssign(const std::string& name, ExprPtr expr, int line) {
    auto s = new Stmt(); s->kind = StmtKind::Assign; s->name = name; s->expr = expr; s->line = line; return s;
}
inline StmtPtr mkIf(ExprPtr cond, StmtPtr then, StmtPtr els, int line) {
    auto s = new Stmt(); s->kind = StmtKind::If; s->cond = cond; s->thenStmt = then; s->elseStmt = els; s->line = line; return s;
}
inline StmtPtr mkWhile(ExprPtr cond, StmtPtr body, int line) {
    auto s = new Stmt(); s->kind = StmtKind::While; s->cond = cond; s->body = body; s->line = line; return s;
}
inline StmtPtr mkFor(const std::string& var, ExprPtr start, ExprPtr end, ForDir dir, StmtPtr body, int line) {
    auto s = new Stmt(); s->kind = StmtKind::For; s->name = var; s->expr = start; s->endExpr = end; s->forDir = dir; s->body = body; s->line = line; return s;
}
inline StmtPtr mkProcCall(const std::string& name, ExprList* args, int line) {
    auto s = new Stmt(); s->kind = StmtKind::ProcCall; s->name = name;
    if (args) { s->args = *args; delete args; }
    s->line = line; return s;
}
inline StmtPtr mkWrite(ExprList* args, bool ln, int line) {
    auto s = new Stmt(); s->kind = StmtKind::Write; s->writeLn = ln;
    if (args) { s->args = *args; delete args; }
    s->line = line; return s;
}
inline StmtPtr mkBlock(StmtList* stmts, int line) {
    auto s = new Stmt(); s->kind = StmtKind::Block;
    if (stmts) { s->stmts = *stmts; delete stmts; }
    s->line = line; return s;
}
inline StmtPtr mkExit(ExprPtr expr, int line) {
    auto s = new Stmt(); s->kind = StmtKind::Exit; s->expr = expr; s->line = line; return s;
}

// ===== DECLARATIONS =====

enum class TypeKind { Integer, Boolean };

struct Param {
    std::string name;
    TypeKind type;
};

enum class DeclKind { Var, Function, Procedure };

struct Decl {
    DeclKind kind;
    std::string name;
    TypeKind type;
    std::vector<Param> params;
    std::vector<std::pair<std::string, TypeKind>> localVars;
    StmtPtr body = nullptr;
};

inline Decl* mkVarDecl(const std::string& name, TypeKind type) {
    auto d = new Decl(); d->kind = DeclKind::Var; d->name = name; d->type = type; return d;
}
inline Decl* mkFuncDecl(const std::string& name, std::vector<Param>* params, TypeKind retType,
                         std::vector<std::pair<std::string,TypeKind>>* locals, StmtPtr body) {
    auto d = new Decl(); d->kind = DeclKind::Function; d->name = name; d->type = retType; d->body = body;
    if (params) { d->params = *params; delete params; }
    if (locals) { d->localVars = *locals; delete locals; }
    return d;
}
inline Decl* mkProcDecl(const std::string& name, std::vector<Param>* params,
                         std::vector<std::pair<std::string,TypeKind>>* locals, StmtPtr body) {
    auto d = new Decl(); d->kind = DeclKind::Procedure; d->name = name; d->body = body;
    if (params) { d->params = *params; delete params; }
    if (locals) { d->localVars = *locals; delete locals; }
    return d;
}

// ===== PROGRAM =====

struct Program {
    std::string name;
    std::vector<Decl*> decls;
    StmtPtr body = nullptr;
};

#endif // AST_H
