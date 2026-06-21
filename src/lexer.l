%{
/*
 * lexer.l - Flex lexical analyzer for Mini-Pascal
 * Tokenizes: keywords, identifiers, numbers, strings, operators, punctuation
 */
#include <string>
#include "ast.h"
#include "parser.tab.h"

extern int yylineno;
%}

%option noyywrap
%option yylineno

%%

 /* === Whitespace and Comments === */
[ \t\r]+                { /* skip whitespace */ }
\n                      { /* newline tracked by yylineno */ }
\{[^}]*\}              { /* block comment { } */ }
\(\*([^*]|\*[^)])*\*\) { /* block comment (* *) */ }
\/\/[^\n]*              { /* line comment // */ }

 /* === Keywords (case-insensitive) === */
(?i:program)    { return TOK_PROGRAM; }
(?i:var)        { return TOK_VAR; }
(?i:begin)      { return TOK_BEGIN; }
(?i:end)        { return TOK_END; }
(?i:integer)    { return TOK_INTEGER; }
(?i:boolean)    { return TOK_BOOLEAN; }
(?i:if)         { return TOK_IF; }
(?i:then)       { return TOK_THEN; }
(?i:else)       { return TOK_ELSE; }
(?i:while)      { return TOK_WHILE; }
(?i:do)         { return TOK_DO; }
(?i:for)        { return TOK_FOR; }
(?i:to)         { return TOK_TO; }
(?i:downto)     { return TOK_DOWNTO; }
(?i:function)   { return TOK_FUNCTION; }
(?i:procedure)  { return TOK_PROCEDURE; }
(?i:true)       { yylval.boolVal = true; return TOK_TRUE; }
(?i:false)      { yylval.boolVal = false; return TOK_FALSE; }
(?i:and)        { return TOK_AND; }
(?i:or)         { return TOK_OR; }
(?i:not)        { return TOK_NOT; }
(?i:div)        { return TOK_DIV; }
(?i:mod)        { return TOK_MOD; }
(?i:write)      { return TOK_WRITE; }
(?i:writeln)    { return TOK_WRITELN; }
(?i:exit)       { return TOK_EXIT; }

 /* === Literals === */
[0-9]+          { yylval.intVal = atoi(yytext); return TOK_INT_LIT; }
\'([^']|\'\')*\' {
    /* String literal - remove surrounding quotes and unescape '' to ' */
    std::string s(yytext + 1, strlen(yytext) - 2);
    std::string result;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\'' && i + 1 < s.size() && s[i+1] == '\'') { result += '\''; i++; }
        else result += s[i];
    }
    yylval.strVal = strdup(result.c_str());
    return TOK_STR_LIT;
}

 /* === Identifiers === */
[a-zA-Z_][a-zA-Z0-9_]* { yylval.strVal = strdup(yytext); return TOK_IDENT; }

 /* === Operators === */
":="    { return TOK_ASSIGN; }
"<>"    { return TOK_NEQ; }
"<="    { return TOK_LTE; }
">="    { return TOK_GTE; }
"<"     { return TOK_LT; }
">"     { return TOK_GT; }
"="     { return TOK_EQ; }
"+"     { return TOK_PLUS; }
"-"     { return TOK_MINUS; }
"*"     { return TOK_STAR; }

 /* === Punctuation === */
";"     { return TOK_SEMI; }
":"     { return TOK_COLON; }
","     { return TOK_COMMA; }
"."     { return TOK_DOT; }
"("     { return TOK_LPAREN; }
")"     { return TOK_RPAREN; }

 /* === Error === */
.       { fprintf(stderr, "Error: unexpected character '%s' at line %d\n", yytext, yylineno); }

%%
