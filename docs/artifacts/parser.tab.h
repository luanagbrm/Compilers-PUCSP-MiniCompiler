/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BUILD_PARSER_TAB_H_INCLUDED
# define YY_YY_BUILD_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_PROGRAM = 258,             /* TOK_PROGRAM  */
    TOK_VAR = 259,                 /* TOK_VAR  */
    TOK_BEGIN = 260,               /* TOK_BEGIN  */
    TOK_END = 261,                 /* TOK_END  */
    TOK_INTEGER = 262,             /* TOK_INTEGER  */
    TOK_BOOLEAN = 263,             /* TOK_BOOLEAN  */
    TOK_IF = 264,                  /* TOK_IF  */
    TOK_THEN = 265,                /* TOK_THEN  */
    TOK_ELSE = 266,                /* TOK_ELSE  */
    TOK_WHILE = 267,               /* TOK_WHILE  */
    TOK_DO = 268,                  /* TOK_DO  */
    TOK_FOR = 269,                 /* TOK_FOR  */
    TOK_TO = 270,                  /* TOK_TO  */
    TOK_DOWNTO = 271,              /* TOK_DOWNTO  */
    TOK_FUNCTION = 272,            /* TOK_FUNCTION  */
    TOK_PROCEDURE = 273,           /* TOK_PROCEDURE  */
    TOK_AND = 274,                 /* TOK_AND  */
    TOK_OR = 275,                  /* TOK_OR  */
    TOK_NOT = 276,                 /* TOK_NOT  */
    TOK_DIV = 277,                 /* TOK_DIV  */
    TOK_MOD = 278,                 /* TOK_MOD  */
    TOK_WRITE = 279,               /* TOK_WRITE  */
    TOK_WRITELN = 280,             /* TOK_WRITELN  */
    TOK_EXIT = 281,                /* TOK_EXIT  */
    TOK_ASSIGN = 282,              /* TOK_ASSIGN  */
    TOK_EQ = 283,                  /* TOK_EQ  */
    TOK_NEQ = 284,                 /* TOK_NEQ  */
    TOK_LT = 285,                  /* TOK_LT  */
    TOK_GT = 286,                  /* TOK_GT  */
    TOK_LTE = 287,                 /* TOK_LTE  */
    TOK_GTE = 288,                 /* TOK_GTE  */
    TOK_PLUS = 289,                /* TOK_PLUS  */
    TOK_MINUS = 290,               /* TOK_MINUS  */
    TOK_STAR = 291,                /* TOK_STAR  */
    TOK_SEMI = 292,                /* TOK_SEMI  */
    TOK_COLON = 293,               /* TOK_COLON  */
    TOK_COMMA = 294,               /* TOK_COMMA  */
    TOK_DOT = 295,                 /* TOK_DOT  */
    TOK_LPAREN = 296,              /* TOK_LPAREN  */
    TOK_RPAREN = 297,              /* TOK_RPAREN  */
    TOK_INT_LIT = 298,             /* TOK_INT_LIT  */
    TOK_TRUE = 299,                /* TOK_TRUE  */
    TOK_FALSE = 300,               /* TOK_FALSE  */
    TOK_IDENT = 301,               /* TOK_IDENT  */
    TOK_STR_LIT = 302,             /* TOK_STR_LIT  */
    UMINUS = 303                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "src/parser.y"

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

#line 129 "build/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BUILD_PARSER_TAB_H_INCLUDED  */
