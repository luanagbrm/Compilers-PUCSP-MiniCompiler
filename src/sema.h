#ifndef SEMA_H
#define SEMA_H

/*
 * sema.h - Static semantic analysis for Mini-Pascal
 *
 * Walks the AST and validates:
 *   - identifier resolution (variables, functions, procedures)
 *   - operator/operand type compatibility (e.g. no `bool + int`, no `not 5`)
 *   - assignment type compatibility (target type must match expression)
 *   - function/procedure call arity and argument types
 *   - return-value path of functions (assigning to function name)
 *   - well-formed program structure
 *
 * Errors are reported on stderr with the source line number from the AST.
 * Codegen should only run when `Sema::analyze` returns true.
 */

#include "ast.h"
#include <map>
#include <string>
#include <vector>

class Sema {
public:
    bool analyze(Program* prog);
    int errorCount() const { return errors; }

private:
    // Resolved type of an expression. The enum mirrors TypeKind for declared
    // values, plus "String" for string literals (only legal as a write/writeln
    // argument) and "Error" used to suppress cascading errors after a failure.
    enum class Ty { Integer, Boolean, String, Error };

    struct Symbol {
        enum class Kind { Var, Param, Function, Procedure } kind;
        Ty type = Ty::Error;                  // result type (Var/Param/Function)
        std::vector<Ty> paramTypes;           // for Function/Procedure
    };

    using Scope = std::map<std::string, Symbol>;

    std::vector<Scope> scopes;
    std::string currentFunc;                  // empty when not inside a function
    Ty currentFuncReturn = Ty::Error;
    int errors = 0;

    // Scope helpers
    void pushScope();
    void popScope();
    bool declare(const std::string& name, const Symbol& sym, int line);
    const Symbol* lookup(const std::string& name) const;

    // Walkers
    void checkDecl(Decl* d);
    void checkSubprogBody(Decl* d);
    void checkStmt(Stmt* s);
    Ty   checkExpr(Expr* e);
    Ty   checkBinOp(Expr* e);
    Ty   checkCall(const std::string& name, const std::vector<ExprPtr>& args, int line, bool needsResult);

    // Utilities
    static Ty fromTypeKind(TypeKind tk);
    static const char* tyName(Ty t);
    void error(int line, const std::string& msg);
};

#endif // SEMA_H
