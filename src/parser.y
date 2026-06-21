%{
/*
 * parser.y - Bison grammar for Mini-Pascal
 * Context-Free Grammar with semantic actions producing AST nodes
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include "ast.h"

extern int yylineno;
extern int yylex();
extern FILE* yyin;
void yyerror(const char* s);

Program* programAST = nullptr;
%}

%union {
    int intVal;
    bool boolVal;
    char* strVal;
    Expr* expr;
    Stmt* stmt;
    Decl* decl;
    std::vector<ExprPtr>* exprList;
    std::vector<StmtPtr>* stmtList;
    std::vector<Decl*>* declList;
    std::vector<Param>* paramList;
    std::vector<std::pair<std::string,TypeKind>>* localVarList;
    std::vector<std::string>* nameList;
    TypeKind typeKind;
    ForDir forDir;
}

%token TOK_PROGRAM TOK_VAR TOK_BEGIN TOK_END
%token TOK_INTEGER TOK_BOOLEAN
%token TOK_IF TOK_THEN TOK_ELSE
%token TOK_WHILE TOK_DO TOK_FOR TOK_TO TOK_DOWNTO
%token TOK_FUNCTION TOK_PROCEDURE
%token TOK_AND TOK_OR TOK_NOT TOK_DIV TOK_MOD
%token TOK_WRITE TOK_WRITELN TOK_EXIT
%token TOK_ASSIGN TOK_EQ TOK_NEQ TOK_LT TOK_GT TOK_LTE TOK_GTE
%token TOK_PLUS TOK_MINUS TOK_STAR
%token TOK_SEMI TOK_COLON TOK_COMMA TOK_DOT TOK_LPAREN TOK_RPAREN

%token <intVal> TOK_INT_LIT
%token <boolVal> TOK_TRUE TOK_FALSE
%token <strVal> TOK_IDENT TOK_STR_LIT

%type <expr> expr simple_expr term factor
%type <stmt> stmt compound_stmt
%type <stmtList> stmt_list
%type <exprList> expr_list
%type <declList> decl_section var_decl_block var_decl_items var_decl_line subprog_decls
%type <decl> subprog_decl
%type <paramList> param_list param_group
%type <localVarList> local_vars local_var_items local_var_line
%type <nameList> ident_list
%type <typeKind> type_spec
%type <forDir> for_dir

/* Dangling else resolution */
%nonassoc TOK_THEN
%nonassoc TOK_ELSE
%right UMINUS

%%

/* ============================================================
 * PROGRAM
 * ============================================================ */

program:
    TOK_PROGRAM TOK_IDENT TOK_SEMI decl_section compound_stmt TOK_DOT {
        programAST = new Program();
        programAST->name = $2; free($2);
        if ($4) { programAST->decls = *$4; delete $4; }
        programAST->body = $5;
    }
    ;

decl_section:
    var_decl_block subprog_decls {
        auto list = new std::vector<Decl*>();
        if ($1) { list->insert(list->end(), $1->begin(), $1->end()); delete $1; }
        if ($2) { list->insert(list->end(), $2->begin(), $2->end()); delete $2; }
        $$ = list;
    }
    ;

/* ============================================================
 * VARIABLE DECLARATIONS
 * ============================================================ */

var_decl_block:
    /* empty */ { $$ = nullptr; }
    | TOK_VAR var_decl_items { $$ = $2; }
    ;

var_decl_items:
    var_decl_line { $$ = $1; }
    | var_decl_items var_decl_line {
        $1->insert($1->end(), $2->begin(), $2->end());
        delete $2; $$ = $1;
    }
    ;

var_decl_line:
    ident_list TOK_COLON type_spec TOK_SEMI {
        auto list = new std::vector<Decl*>();
        for (auto& name : *$1)
            list->push_back(mkVarDecl(name, $3));
        delete $1;
        $$ = list;
    }
    ;

ident_list:
    TOK_IDENT {
        auto list = new std::vector<std::string>();
        list->push_back($1); free($1);
        $$ = list;
    }
    | ident_list TOK_COMMA TOK_IDENT {
        $1->push_back($3); free($3);
        $$ = $1;
    }
    ;

type_spec:
    TOK_INTEGER { $$ = TypeKind::Integer; }
    | TOK_BOOLEAN { $$ = TypeKind::Boolean; }
    ;

/* ============================================================
 * FUNCTION / PROCEDURE DECLARATIONS
 * ============================================================ */

subprog_decls:
    /* empty */ { $$ = nullptr; }
    | subprog_decls subprog_decl {
        if (!$1) $1 = new std::vector<Decl*>();
        $1->push_back($2); $$ = $1;
    }
    ;

subprog_decl:
    TOK_FUNCTION TOK_IDENT TOK_LPAREN param_list TOK_RPAREN TOK_COLON type_spec TOK_SEMI
        local_vars compound_stmt TOK_SEMI {
        $$ = mkFuncDecl($2, $4, $7, $9, $10); free($2);
    }
    | TOK_PROCEDURE TOK_IDENT TOK_LPAREN param_list TOK_RPAREN TOK_SEMI
        local_vars compound_stmt TOK_SEMI {
        $$ = mkProcDecl($2, $4, $7, $8); free($2);
    }
    | TOK_FUNCTION TOK_IDENT TOK_LPAREN TOK_RPAREN TOK_COLON type_spec TOK_SEMI
        local_vars compound_stmt TOK_SEMI {
        $$ = mkFuncDecl($2, nullptr, $6, $8, $9); free($2);
    }
    | TOK_PROCEDURE TOK_IDENT TOK_LPAREN TOK_RPAREN TOK_SEMI
        local_vars compound_stmt TOK_SEMI {
        $$ = mkProcDecl($2, nullptr, $6, $7); free($2);
    }
    | TOK_PROCEDURE TOK_IDENT TOK_SEMI
        local_vars compound_stmt TOK_SEMI {
        $$ = mkProcDecl($2, nullptr, $4, $5); free($2);
    }
    ;

param_list:
    param_group { $$ = $1; }
    | param_list TOK_SEMI param_group {
        $1->insert($1->end(), $3->begin(), $3->end());
        delete $3; $$ = $1;
    }
    ;

param_group:
    ident_list TOK_COLON type_spec {
        auto list = new std::vector<Param>();
        for (auto& name : *$1)
            list->push_back({name, $3});
        delete $1; $$ = list;
    }
    ;

local_vars:
    /* empty */ { $$ = nullptr; }
    | TOK_VAR local_var_items { $$ = $2; }
    ;

local_var_items:
    local_var_line { $$ = $1; }
    | local_var_items local_var_line {
        $1->insert($1->end(), $2->begin(), $2->end());
        delete $2; $$ = $1;
    }
    ;

local_var_line:
    ident_list TOK_COLON type_spec TOK_SEMI {
        auto list = new std::vector<std::pair<std::string,TypeKind>>();
        for (auto& name : *$1)
            list->push_back({name, $3});
        delete $1; $$ = list;
    }
    ;

/* ============================================================
 * STATEMENTS
 * ============================================================ */

compound_stmt:
    TOK_BEGIN stmt_list TOK_END {
        $$ = mkBlock($2, yylineno);
    }
    ;

stmt_list:
    stmt {
        auto list = new std::vector<StmtPtr>();
        if ($1) list->push_back($1);
        $$ = list;
    }
    | stmt_list TOK_SEMI stmt {
        if ($3) $1->push_back($3);
        $$ = $1;
    }
    ;

stmt:
    /* empty */ { $$ = nullptr; }
    | TOK_IDENT TOK_ASSIGN expr {
        $$ = mkAssign($1, $3, yylineno); free($1);
    }
    | TOK_IDENT TOK_LPAREN expr_list TOK_RPAREN {
        $$ = mkProcCall($1, $3, yylineno); free($1);
    }
    | TOK_IDENT {
        /* procedure call with no args */
        $$ = mkProcCall($1, nullptr, yylineno); free($1);
    }
    | compound_stmt { $$ = $1; }
    | TOK_IF expr TOK_THEN stmt {
        $$ = mkIf($2, $4, nullptr, yylineno);
    }
    | TOK_IF expr TOK_THEN stmt TOK_ELSE stmt {
        $$ = mkIf($2, $4, $6, yylineno);
    }
    | TOK_WHILE expr TOK_DO stmt {
        $$ = mkWhile($2, $4, yylineno);
    }
    | TOK_FOR TOK_IDENT TOK_ASSIGN expr for_dir expr TOK_DO stmt {
        $$ = mkFor($2, $4, $6, $5, $8, yylineno); free($2);
    }
    | TOK_WRITE TOK_LPAREN expr_list TOK_RPAREN {
        $$ = mkWrite($3, false, yylineno);
    }
    | TOK_WRITELN TOK_LPAREN expr_list TOK_RPAREN {
        $$ = mkWrite($3, true, yylineno);
    }
    | TOK_WRITELN {
        $$ = mkWrite(nullptr, true, yylineno);
    }
    | TOK_EXIT TOK_LPAREN expr TOK_RPAREN {
        $$ = mkExit($3, yylineno);
    }
    ;

for_dir:
    TOK_TO     { $$ = ForDir::To; }
    | TOK_DOWNTO { $$ = ForDir::DownTo; }
    ;

/* ============================================================
 * EXPRESSIONS
 * ============================================================ */

expr:
    simple_expr { $$ = $1; }
    | simple_expr TOK_EQ simple_expr   { $$ = mkBinOp(BinOpKind::Eq, $1, $3, yylineno); }
    | simple_expr TOK_NEQ simple_expr  { $$ = mkBinOp(BinOpKind::Neq, $1, $3, yylineno); }
    | simple_expr TOK_LT simple_expr   { $$ = mkBinOp(BinOpKind::Lt, $1, $3, yylineno); }
    | simple_expr TOK_GT simple_expr   { $$ = mkBinOp(BinOpKind::Gt, $1, $3, yylineno); }
    | simple_expr TOK_LTE simple_expr  { $$ = mkBinOp(BinOpKind::Lte, $1, $3, yylineno); }
    | simple_expr TOK_GTE simple_expr  { $$ = mkBinOp(BinOpKind::Gte, $1, $3, yylineno); }
    ;

simple_expr:
    term { $$ = $1; }
    | simple_expr TOK_PLUS term   { $$ = mkBinOp(BinOpKind::Add, $1, $3, yylineno); }
    | simple_expr TOK_MINUS term  { $$ = mkBinOp(BinOpKind::Sub, $1, $3, yylineno); }
    | simple_expr TOK_OR term     { $$ = mkBinOp(BinOpKind::Or, $1, $3, yylineno); }
    ;

term:
    factor { $$ = $1; }
    | term TOK_STAR factor  { $$ = mkBinOp(BinOpKind::Mul, $1, $3, yylineno); }
    | term TOK_DIV factor   { $$ = mkBinOp(BinOpKind::Div, $1, $3, yylineno); }
    | term TOK_MOD factor   { $$ = mkBinOp(BinOpKind::Mod, $1, $3, yylineno); }
    | term TOK_AND factor   { $$ = mkBinOp(BinOpKind::And, $1, $3, yylineno); }
    ;

factor:
    TOK_INT_LIT { $$ = mkIntLit($1, yylineno); }
    | TOK_TRUE  { $$ = mkBoolLit(true, yylineno); }
    | TOK_FALSE { $$ = mkBoolLit(false, yylineno); }
    | TOK_STR_LIT { $$ = mkStringLit($1, yylineno); free($1); }
    | TOK_IDENT {
        $$ = mkIdent($1, yylineno); free($1);
    }
    | TOK_IDENT TOK_LPAREN expr_list TOK_RPAREN {
        $$ = mkFuncCall($1, $3, yylineno); free($1);
    }
    | TOK_LPAREN expr TOK_RPAREN { $$ = $2; }
    | TOK_NOT factor { $$ = mkUnaryOp(UnaryOpKind::Not, $2, yylineno); }
    | TOK_MINUS factor %prec UMINUS { $$ = mkUnaryOp(UnaryOpKind::Neg, $2, yylineno); }
    ;

expr_list:
    expr {
        auto list = new std::vector<ExprPtr>();
        list->push_back($1); $$ = list;
    }
    | expr_list TOK_COMMA expr {
        $1->push_back($3); $$ = $1;
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
