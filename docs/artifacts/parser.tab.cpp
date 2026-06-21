/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

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

#line 91 "build/parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_PROGRAM = 3,                /* TOK_PROGRAM  */
  YYSYMBOL_TOK_VAR = 4,                    /* TOK_VAR  */
  YYSYMBOL_TOK_BEGIN = 5,                  /* TOK_BEGIN  */
  YYSYMBOL_TOK_END = 6,                    /* TOK_END  */
  YYSYMBOL_TOK_INTEGER = 7,                /* TOK_INTEGER  */
  YYSYMBOL_TOK_BOOLEAN = 8,                /* TOK_BOOLEAN  */
  YYSYMBOL_TOK_IF = 9,                     /* TOK_IF  */
  YYSYMBOL_TOK_THEN = 10,                  /* TOK_THEN  */
  YYSYMBOL_TOK_ELSE = 11,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 12,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_DO = 13,                    /* TOK_DO  */
  YYSYMBOL_TOK_FOR = 14,                   /* TOK_FOR  */
  YYSYMBOL_TOK_TO = 15,                    /* TOK_TO  */
  YYSYMBOL_TOK_DOWNTO = 16,                /* TOK_DOWNTO  */
  YYSYMBOL_TOK_FUNCTION = 17,              /* TOK_FUNCTION  */
  YYSYMBOL_TOK_PROCEDURE = 18,             /* TOK_PROCEDURE  */
  YYSYMBOL_TOK_AND = 19,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 20,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 21,                   /* TOK_NOT  */
  YYSYMBOL_TOK_DIV = 22,                   /* TOK_DIV  */
  YYSYMBOL_TOK_MOD = 23,                   /* TOK_MOD  */
  YYSYMBOL_TOK_WRITE = 24,                 /* TOK_WRITE  */
  YYSYMBOL_TOK_WRITELN = 25,               /* TOK_WRITELN  */
  YYSYMBOL_TOK_EXIT = 26,                  /* TOK_EXIT  */
  YYSYMBOL_TOK_ASSIGN = 27,                /* TOK_ASSIGN  */
  YYSYMBOL_TOK_EQ = 28,                    /* TOK_EQ  */
  YYSYMBOL_TOK_NEQ = 29,                   /* TOK_NEQ  */
  YYSYMBOL_TOK_LT = 30,                    /* TOK_LT  */
  YYSYMBOL_TOK_GT = 31,                    /* TOK_GT  */
  YYSYMBOL_TOK_LTE = 32,                   /* TOK_LTE  */
  YYSYMBOL_TOK_GTE = 33,                   /* TOK_GTE  */
  YYSYMBOL_TOK_PLUS = 34,                  /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 35,                 /* TOK_MINUS  */
  YYSYMBOL_TOK_STAR = 36,                  /* TOK_STAR  */
  YYSYMBOL_TOK_SEMI = 37,                  /* TOK_SEMI  */
  YYSYMBOL_TOK_COLON = 38,                 /* TOK_COLON  */
  YYSYMBOL_TOK_COMMA = 39,                 /* TOK_COMMA  */
  YYSYMBOL_TOK_DOT = 40,                   /* TOK_DOT  */
  YYSYMBOL_TOK_LPAREN = 41,                /* TOK_LPAREN  */
  YYSYMBOL_TOK_RPAREN = 42,                /* TOK_RPAREN  */
  YYSYMBOL_TOK_INT_LIT = 43,               /* TOK_INT_LIT  */
  YYSYMBOL_TOK_TRUE = 44,                  /* TOK_TRUE  */
  YYSYMBOL_TOK_FALSE = 45,                 /* TOK_FALSE  */
  YYSYMBOL_TOK_IDENT = 46,                 /* TOK_IDENT  */
  YYSYMBOL_TOK_STR_LIT = 47,               /* TOK_STR_LIT  */
  YYSYMBOL_UMINUS = 48,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_decl_section = 51,              /* decl_section  */
  YYSYMBOL_var_decl_block = 52,            /* var_decl_block  */
  YYSYMBOL_var_decl_items = 53,            /* var_decl_items  */
  YYSYMBOL_var_decl_line = 54,             /* var_decl_line  */
  YYSYMBOL_ident_list = 55,                /* ident_list  */
  YYSYMBOL_type_spec = 56,                 /* type_spec  */
  YYSYMBOL_subprog_decls = 57,             /* subprog_decls  */
  YYSYMBOL_subprog_decl = 58,              /* subprog_decl  */
  YYSYMBOL_param_list = 59,                /* param_list  */
  YYSYMBOL_param_group = 60,               /* param_group  */
  YYSYMBOL_local_vars = 61,                /* local_vars  */
  YYSYMBOL_local_var_items = 62,           /* local_var_items  */
  YYSYMBOL_local_var_line = 63,            /* local_var_line  */
  YYSYMBOL_compound_stmt = 64,             /* compound_stmt  */
  YYSYMBOL_stmt_list = 65,                 /* stmt_list  */
  YYSYMBOL_stmt = 66,                      /* stmt  */
  YYSYMBOL_for_dir = 67,                   /* for_dir  */
  YYSYMBOL_expr = 68,                      /* expr  */
  YYSYMBOL_simple_expr = 69,               /* simple_expr  */
  YYSYMBOL_term = 70,                      /* term  */
  YYSYMBOL_factor = 71,                    /* factor  */
  YYSYMBOL_expr_list = 72                  /* expr_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   158

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    77,    77,    86,    99,   100,   104,   105,   112,   122,
     127,   134,   135,   143,   144,   151,   155,   159,   163,   167,
     174,   175,   182,   191,   192,   196,   197,   204,   217,   223,
     228,   235,   236,   239,   242,   246,   247,   250,   253,   256,
     259,   262,   265,   268,   274,   275,   283,   284,   285,   286,
     287,   288,   289,   293,   294,   295,   296,   300,   301,   302,
     303,   304,   308,   309,   310,   311,   312,   315,   318,   319,
     320,   324,   328
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_PROGRAM",
  "TOK_VAR", "TOK_BEGIN", "TOK_END", "TOK_INTEGER", "TOK_BOOLEAN",
  "TOK_IF", "TOK_THEN", "TOK_ELSE", "TOK_WHILE", "TOK_DO", "TOK_FOR",
  "TOK_TO", "TOK_DOWNTO", "TOK_FUNCTION", "TOK_PROCEDURE", "TOK_AND",
  "TOK_OR", "TOK_NOT", "TOK_DIV", "TOK_MOD", "TOK_WRITE", "TOK_WRITELN",
  "TOK_EXIT", "TOK_ASSIGN", "TOK_EQ", "TOK_NEQ", "TOK_LT", "TOK_GT",
  "TOK_LTE", "TOK_GTE", "TOK_PLUS", "TOK_MINUS", "TOK_STAR", "TOK_SEMI",
  "TOK_COLON", "TOK_COMMA", "TOK_DOT", "TOK_LPAREN", "TOK_RPAREN",
  "TOK_INT_LIT", "TOK_TRUE", "TOK_FALSE", "TOK_IDENT", "TOK_STR_LIT",
  "UMINUS", "$accept", "program", "decl_section", "var_decl_block",
  "var_decl_items", "var_decl_line", "ident_list", "type_spec",
  "subprog_decls", "subprog_decl", "param_list", "param_group",
  "local_vars", "local_var_items", "local_var_line", "compound_stmt",
  "stmt_list", "stmt", "for_dir", "expr", "simple_expr", "term", "factor",
  "expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-126)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      18,   -19,    33,    -2,  -126,    67,    39,    85,  -126,  -126,
      39,  -126,    66,     4,    55,    90,  -126,    54,    72,    13,
      13,    73,    79,    80,    81,   -10,  -126,     2,  -126,  -126,
      77,    83,  -126,  -126,  -126,    87,  -126,    13,    13,    13,
    -126,  -126,  -126,    84,  -126,   116,    44,    19,  -126,   114,
     103,    13,    13,    13,    13,    13,  -126,     4,    91,    12,
    -126,  -126,  -126,    89,    13,     4,    13,    13,    13,    13,
      13,    13,    13,    13,    13,    13,    13,    13,    13,     4,
      13,  -126,     1,    47,    92,  -126,    52,  -126,   -22,   129,
      23,  -126,    64,   124,    19,    48,    48,    48,    48,    48,
      48,    19,    19,  -126,  -126,  -126,  -126,  -126,    95,    13,
    -126,  -126,  -126,  -126,    98,    76,   -27,  -126,    39,    85,
     100,   -23,  -126,     4,  -126,  -126,    13,  -126,    54,    54,
      39,   101,    78,    39,  -126,   104,   129,   105,  -126,   125,
     106,  -126,  -126,    54,    54,  -126,  -126,    85,   129,     4,
     129,   107,   108,   109,    85,  -126,    85,   129,  -126,  -126,
     111,   113,    85,  -126,  -126,   115,  -126
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     0,    13,     9,
       5,     6,     0,    31,     0,     3,     7,     0,     0,     0,
       0,     0,     0,    42,     0,    34,    35,     0,    29,     2,
       0,     0,    14,    11,    12,     0,    10,     0,     0,     0,
      62,    63,    64,    66,    65,     0,    46,    53,    57,     0,
       0,     0,     0,     0,     0,     0,    28,    31,     0,     0,
       8,    69,    70,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
       0,    71,     0,     0,     0,    32,     0,    30,     0,    23,
       0,    68,     0,    36,    56,    47,    48,    49,    50,    51,
      52,    54,    55,    61,    59,    60,    58,    38,     0,     0,
      40,    41,    43,    33,     0,     0,     0,    20,     0,     0,
       0,     0,    67,    31,    44,    45,     0,    72,     0,     0,
       0,     0,     0,    24,    25,     0,    23,     0,    37,     0,
       0,    22,    21,     0,     0,    26,    19,     0,    23,    31,
      23,     0,     0,     0,     0,    39,     0,    23,    27,    18,
       0,     0,     0,    16,    17,     0,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -126,  -126,  -126,  -126,  -126,   141,    -5,   -77,  -126,  -126,
      63,    24,  -125,  -126,    25,    -7,  -126,   -53,  -126,   -17,
      30,    14,   -31,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     8,    10,    11,   115,    35,    15,    32,
     116,   117,   119,   133,   134,    26,    27,    28,   126,    81,
      46,    47,    48,    82
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      14,    12,    45,    49,    87,    12,    61,    62,    56,    13,
     130,   147,    93,    19,   130,   131,    20,    54,    21,   137,
     114,     1,    63,   154,     9,   156,   107,     3,    22,    23,
      24,    55,   162,     4,    37,     5,    84,    85,    75,    57,
     109,    76,    77,   110,   103,   104,   105,   106,    38,    89,
      25,   140,   141,    90,    39,    78,    40,    41,    42,    43,
      44,    33,    34,   108,    66,   120,   151,   152,    66,     9,
     138,     6,    67,    68,    69,    70,    71,    72,    73,    74,
      94,    83,    73,    74,    86,     9,   109,   101,   102,   111,
      13,   109,   127,    92,   113,    29,   155,    95,    96,    97,
      98,    99,   100,   109,    17,    18,   122,    30,    31,   139,
     124,   125,   135,   132,   129,    18,   144,    18,    36,    50,
      51,    52,    53,    58,    60,    64,    65,    79,   132,    59,
      80,    91,    88,   118,   112,   123,   128,   136,   149,   143,
     153,   146,   148,   150,   157,   158,   159,   160,   163,   161,
     164,    16,   166,   121,   142,   165,     0,     0,   145
};

static const yytype_int16 yycheck[] =
{
       7,     6,    19,    20,    57,    10,    37,    38,     6,     5,
      37,   136,    65,     9,    37,    42,    12,    27,    14,    42,
      42,     3,    39,   148,    46,   150,    79,    46,    24,    25,
      26,    41,   157,     0,    21,    37,    53,    54,    19,    37,
      39,    22,    23,    42,    75,    76,    77,    78,    35,    37,
      46,   128,   129,    41,    41,    36,    43,    44,    45,    46,
      47,     7,     8,    80,    20,    42,   143,   144,    20,    46,
     123,     4,    28,    29,    30,    31,    32,    33,    34,    35,
      66,    52,    34,    35,    55,    46,    39,    73,    74,    42,
       5,    39,   109,    64,    42,    40,   149,    67,    68,    69,
      70,    71,    72,    39,    38,    39,    42,    17,    18,   126,
      15,    16,   119,   118,    38,    39,    38,    39,    46,    46,
      41,    41,    41,    46,    37,    41,    10,    13,   133,    46,
      27,    42,    41,     4,    42,    11,    38,    37,    13,    38,
     147,    37,    37,    37,    37,    37,    37,   154,    37,   156,
      37,    10,    37,    90,   130,   162,    -1,    -1,   133
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    50,    46,     0,    37,     4,    51,    52,    46,
      53,    54,    55,     5,    64,    57,    54,    38,    39,     9,
      12,    14,    24,    25,    26,    46,    64,    65,    66,    40,
      17,    18,    58,     7,     8,    56,    46,    21,    35,    41,
      43,    44,    45,    46,    47,    68,    69,    70,    71,    68,
      46,    41,    41,    41,    27,    41,     6,    37,    46,    46,
      37,    71,    71,    68,    41,    10,    20,    28,    29,    30,
      31,    32,    33,    34,    35,    19,    22,    23,    36,    13,
      27,    68,    72,    72,    68,    68,    72,    66,    41,    37,
      41,    42,    72,    66,    70,    69,    69,    69,    69,    69,
      69,    70,    70,    71,    71,    71,    71,    66,    68,    39,
      42,    42,    42,    42,    42,    55,    59,    60,     4,    61,
      42,    59,    42,    11,    15,    16,    67,    68,    38,    38,
      37,    42,    55,    62,    63,    64,    37,    42,    66,    68,
      56,    56,    60,    38,    38,    63,    37,    61,    37,    13,
      37,    56,    56,    64,    61,    66,    61,    37,    37,    37,
      64,    64,    61,    37,    37,    64,    37
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    52,    52,    53,    53,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    58,    58,
      59,    59,    60,    61,    61,    62,    62,    63,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    67,    67,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    69,    69,    70,    70,    70,
      70,    70,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     2,     0,     2,     1,     2,     4,     1,
       3,     1,     1,     0,     2,    11,     9,    10,     8,     6,
       1,     3,     3,     0,     2,     1,     2,     4,     3,     1,
       3,     0,     3,     4,     1,     1,     4,     6,     4,     8,
       4,     4,     1,     4,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     1,     3,     3,
       3,     3,     1,     1,     1,     1,     1,     4,     3,     2,
       2,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: TOK_PROGRAM TOK_IDENT TOK_SEMI decl_section compound_stmt TOK_DOT  */
#line 77 "src/parser.y"
                                                                      {
        programAST = new Program();
        programAST->name = (yyvsp[-4].strVal); free((yyvsp[-4].strVal));
        if ((yyvsp[-2].declList)) { programAST->decls = *(yyvsp[-2].declList); delete (yyvsp[-2].declList); }
        programAST->body = (yyvsp[-1].stmt);
    }
#line 1262 "build/parser.tab.cpp"
    break;

  case 3: /* decl_section: var_decl_block subprog_decls  */
#line 86 "src/parser.y"
                                 {
        auto list = new std::vector<Decl*>();
        if ((yyvsp[-1].declList)) { list->insert(list->end(), (yyvsp[-1].declList)->begin(), (yyvsp[-1].declList)->end()); delete (yyvsp[-1].declList); }
        if ((yyvsp[0].declList)) { list->insert(list->end(), (yyvsp[0].declList)->begin(), (yyvsp[0].declList)->end()); delete (yyvsp[0].declList); }
        (yyval.declList) = list;
    }
#line 1273 "build/parser.tab.cpp"
    break;

  case 4: /* var_decl_block: %empty  */
#line 99 "src/parser.y"
                { (yyval.declList) = nullptr; }
#line 1279 "build/parser.tab.cpp"
    break;

  case 5: /* var_decl_block: TOK_VAR var_decl_items  */
#line 100 "src/parser.y"
                             { (yyval.declList) = (yyvsp[0].declList); }
#line 1285 "build/parser.tab.cpp"
    break;

  case 6: /* var_decl_items: var_decl_line  */
#line 104 "src/parser.y"
                  { (yyval.declList) = (yyvsp[0].declList); }
#line 1291 "build/parser.tab.cpp"
    break;

  case 7: /* var_decl_items: var_decl_items var_decl_line  */
#line 105 "src/parser.y"
                                   {
        (yyvsp[-1].declList)->insert((yyvsp[-1].declList)->end(), (yyvsp[0].declList)->begin(), (yyvsp[0].declList)->end());
        delete (yyvsp[0].declList); (yyval.declList) = (yyvsp[-1].declList);
    }
#line 1300 "build/parser.tab.cpp"
    break;

  case 8: /* var_decl_line: ident_list TOK_COLON type_spec TOK_SEMI  */
#line 112 "src/parser.y"
                                            {
        auto list = new std::vector<Decl*>();
        for (auto& name : *(yyvsp[-3].nameList))
            list->push_back(mkVarDecl(name, (yyvsp[-1].typeKind)));
        delete (yyvsp[-3].nameList);
        (yyval.declList) = list;
    }
#line 1312 "build/parser.tab.cpp"
    break;

  case 9: /* ident_list: TOK_IDENT  */
#line 122 "src/parser.y"
              {
        auto list = new std::vector<std::string>();
        list->push_back((yyvsp[0].strVal)); free((yyvsp[0].strVal));
        (yyval.nameList) = list;
    }
#line 1322 "build/parser.tab.cpp"
    break;

  case 10: /* ident_list: ident_list TOK_COMMA TOK_IDENT  */
#line 127 "src/parser.y"
                                     {
        (yyvsp[-2].nameList)->push_back((yyvsp[0].strVal)); free((yyvsp[0].strVal));
        (yyval.nameList) = (yyvsp[-2].nameList);
    }
#line 1331 "build/parser.tab.cpp"
    break;

  case 11: /* type_spec: TOK_INTEGER  */
#line 134 "src/parser.y"
                { (yyval.typeKind) = TypeKind::Integer; }
#line 1337 "build/parser.tab.cpp"
    break;

  case 12: /* type_spec: TOK_BOOLEAN  */
#line 135 "src/parser.y"
                  { (yyval.typeKind) = TypeKind::Boolean; }
#line 1343 "build/parser.tab.cpp"
    break;

  case 13: /* subprog_decls: %empty  */
#line 143 "src/parser.y"
                { (yyval.declList) = nullptr; }
#line 1349 "build/parser.tab.cpp"
    break;

  case 14: /* subprog_decls: subprog_decls subprog_decl  */
#line 144 "src/parser.y"
                                 {
        if (!(yyvsp[-1].declList)) (yyvsp[-1].declList) = new std::vector<Decl*>();
        (yyvsp[-1].declList)->push_back((yyvsp[0].decl)); (yyval.declList) = (yyvsp[-1].declList);
    }
#line 1358 "build/parser.tab.cpp"
    break;

  case 15: /* subprog_decl: TOK_FUNCTION TOK_IDENT TOK_LPAREN param_list TOK_RPAREN TOK_COLON type_spec TOK_SEMI local_vars compound_stmt TOK_SEMI  */
#line 152 "src/parser.y"
                                          {
        (yyval.decl) = mkFuncDecl((yyvsp[-9].strVal), (yyvsp[-7].paramList), (yyvsp[-4].typeKind), (yyvsp[-2].localVarList), (yyvsp[-1].stmt)); free((yyvsp[-9].strVal));
    }
#line 1366 "build/parser.tab.cpp"
    break;

  case 16: /* subprog_decl: TOK_PROCEDURE TOK_IDENT TOK_LPAREN param_list TOK_RPAREN TOK_SEMI local_vars compound_stmt TOK_SEMI  */
#line 156 "src/parser.y"
                                          {
        (yyval.decl) = mkProcDecl((yyvsp[-7].strVal), (yyvsp[-5].paramList), (yyvsp[-2].localVarList), (yyvsp[-1].stmt)); free((yyvsp[-7].strVal));
    }
#line 1374 "build/parser.tab.cpp"
    break;

  case 17: /* subprog_decl: TOK_FUNCTION TOK_IDENT TOK_LPAREN TOK_RPAREN TOK_COLON type_spec TOK_SEMI local_vars compound_stmt TOK_SEMI  */
#line 160 "src/parser.y"
                                          {
        (yyval.decl) = mkFuncDecl((yyvsp[-8].strVal), nullptr, (yyvsp[-4].typeKind), (yyvsp[-2].localVarList), (yyvsp[-1].stmt)); free((yyvsp[-8].strVal));
    }
#line 1382 "build/parser.tab.cpp"
    break;

  case 18: /* subprog_decl: TOK_PROCEDURE TOK_IDENT TOK_LPAREN TOK_RPAREN TOK_SEMI local_vars compound_stmt TOK_SEMI  */
#line 164 "src/parser.y"
                                          {
        (yyval.decl) = mkProcDecl((yyvsp[-6].strVal), nullptr, (yyvsp[-2].localVarList), (yyvsp[-1].stmt)); free((yyvsp[-6].strVal));
    }
#line 1390 "build/parser.tab.cpp"
    break;

  case 19: /* subprog_decl: TOK_PROCEDURE TOK_IDENT TOK_SEMI local_vars compound_stmt TOK_SEMI  */
#line 168 "src/parser.y"
                                          {
        (yyval.decl) = mkProcDecl((yyvsp[-4].strVal), nullptr, (yyvsp[-2].localVarList), (yyvsp[-1].stmt)); free((yyvsp[-4].strVal));
    }
#line 1398 "build/parser.tab.cpp"
    break;

  case 20: /* param_list: param_group  */
#line 174 "src/parser.y"
                { (yyval.paramList) = (yyvsp[0].paramList); }
#line 1404 "build/parser.tab.cpp"
    break;

  case 21: /* param_list: param_list TOK_SEMI param_group  */
#line 175 "src/parser.y"
                                      {
        (yyvsp[-2].paramList)->insert((yyvsp[-2].paramList)->end(), (yyvsp[0].paramList)->begin(), (yyvsp[0].paramList)->end());
        delete (yyvsp[0].paramList); (yyval.paramList) = (yyvsp[-2].paramList);
    }
#line 1413 "build/parser.tab.cpp"
    break;

  case 22: /* param_group: ident_list TOK_COLON type_spec  */
#line 182 "src/parser.y"
                                   {
        auto list = new std::vector<Param>();
        for (auto& name : *(yyvsp[-2].nameList))
            list->push_back({name, (yyvsp[0].typeKind)});
        delete (yyvsp[-2].nameList); (yyval.paramList) = list;
    }
#line 1424 "build/parser.tab.cpp"
    break;

  case 23: /* local_vars: %empty  */
#line 191 "src/parser.y"
                { (yyval.localVarList) = nullptr; }
#line 1430 "build/parser.tab.cpp"
    break;

  case 24: /* local_vars: TOK_VAR local_var_items  */
#line 192 "src/parser.y"
                              { (yyval.localVarList) = (yyvsp[0].localVarList); }
#line 1436 "build/parser.tab.cpp"
    break;

  case 25: /* local_var_items: local_var_line  */
#line 196 "src/parser.y"
                   { (yyval.localVarList) = (yyvsp[0].localVarList); }
#line 1442 "build/parser.tab.cpp"
    break;

  case 26: /* local_var_items: local_var_items local_var_line  */
#line 197 "src/parser.y"
                                     {
        (yyvsp[-1].localVarList)->insert((yyvsp[-1].localVarList)->end(), (yyvsp[0].localVarList)->begin(), (yyvsp[0].localVarList)->end());
        delete (yyvsp[0].localVarList); (yyval.localVarList) = (yyvsp[-1].localVarList);
    }
#line 1451 "build/parser.tab.cpp"
    break;

  case 27: /* local_var_line: ident_list TOK_COLON type_spec TOK_SEMI  */
#line 204 "src/parser.y"
                                            {
        auto list = new std::vector<std::pair<std::string,TypeKind>>();
        for (auto& name : *(yyvsp[-3].nameList))
            list->push_back({name, (yyvsp[-1].typeKind)});
        delete (yyvsp[-3].nameList); (yyval.localVarList) = list;
    }
#line 1462 "build/parser.tab.cpp"
    break;

  case 28: /* compound_stmt: TOK_BEGIN stmt_list TOK_END  */
#line 217 "src/parser.y"
                                {
        (yyval.stmt) = mkBlock((yyvsp[-1].stmtList), yylineno);
    }
#line 1470 "build/parser.tab.cpp"
    break;

  case 29: /* stmt_list: stmt  */
#line 223 "src/parser.y"
         {
        auto list = new std::vector<StmtPtr>();
        if ((yyvsp[0].stmt)) list->push_back((yyvsp[0].stmt));
        (yyval.stmtList) = list;
    }
#line 1480 "build/parser.tab.cpp"
    break;

  case 30: /* stmt_list: stmt_list TOK_SEMI stmt  */
#line 228 "src/parser.y"
                              {
        if ((yyvsp[0].stmt)) (yyvsp[-2].stmtList)->push_back((yyvsp[0].stmt));
        (yyval.stmtList) = (yyvsp[-2].stmtList);
    }
#line 1489 "build/parser.tab.cpp"
    break;

  case 31: /* stmt: %empty  */
#line 235 "src/parser.y"
                { (yyval.stmt) = nullptr; }
#line 1495 "build/parser.tab.cpp"
    break;

  case 32: /* stmt: TOK_IDENT TOK_ASSIGN expr  */
#line 236 "src/parser.y"
                                {
        (yyval.stmt) = mkAssign((yyvsp[-2].strVal), (yyvsp[0].expr), yylineno); free((yyvsp[-2].strVal));
    }
#line 1503 "build/parser.tab.cpp"
    break;

  case 33: /* stmt: TOK_IDENT TOK_LPAREN expr_list TOK_RPAREN  */
#line 239 "src/parser.y"
                                                {
        (yyval.stmt) = mkProcCall((yyvsp[-3].strVal), (yyvsp[-1].exprList), yylineno); free((yyvsp[-3].strVal));
    }
#line 1511 "build/parser.tab.cpp"
    break;

  case 34: /* stmt: TOK_IDENT  */
#line 242 "src/parser.y"
                {
        /* procedure call with no args */
        (yyval.stmt) = mkProcCall((yyvsp[0].strVal), nullptr, yylineno); free((yyvsp[0].strVal));
    }
#line 1520 "build/parser.tab.cpp"
    break;

  case 35: /* stmt: compound_stmt  */
#line 246 "src/parser.y"
                    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1526 "build/parser.tab.cpp"
    break;

  case 36: /* stmt: TOK_IF expr TOK_THEN stmt  */
#line 247 "src/parser.y"
                                {
        (yyval.stmt) = mkIf((yyvsp[-2].expr), (yyvsp[0].stmt), nullptr, yylineno);
    }
#line 1534 "build/parser.tab.cpp"
    break;

  case 37: /* stmt: TOK_IF expr TOK_THEN stmt TOK_ELSE stmt  */
#line 250 "src/parser.y"
                                              {
        (yyval.stmt) = mkIf((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), yylineno);
    }
#line 1542 "build/parser.tab.cpp"
    break;

  case 38: /* stmt: TOK_WHILE expr TOK_DO stmt  */
#line 253 "src/parser.y"
                                 {
        (yyval.stmt) = mkWhile((yyvsp[-2].expr), (yyvsp[0].stmt), yylineno);
    }
#line 1550 "build/parser.tab.cpp"
    break;

  case 39: /* stmt: TOK_FOR TOK_IDENT TOK_ASSIGN expr for_dir expr TOK_DO stmt  */
#line 256 "src/parser.y"
                                                                 {
        (yyval.stmt) = mkFor((yyvsp[-6].strVal), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[-3].forDir), (yyvsp[0].stmt), yylineno); free((yyvsp[-6].strVal));
    }
#line 1558 "build/parser.tab.cpp"
    break;

  case 40: /* stmt: TOK_WRITE TOK_LPAREN expr_list TOK_RPAREN  */
#line 259 "src/parser.y"
                                                {
        (yyval.stmt) = mkWrite((yyvsp[-1].exprList), false, yylineno);
    }
#line 1566 "build/parser.tab.cpp"
    break;

  case 41: /* stmt: TOK_WRITELN TOK_LPAREN expr_list TOK_RPAREN  */
#line 262 "src/parser.y"
                                                  {
        (yyval.stmt) = mkWrite((yyvsp[-1].exprList), true, yylineno);
    }
#line 1574 "build/parser.tab.cpp"
    break;

  case 42: /* stmt: TOK_WRITELN  */
#line 265 "src/parser.y"
                  {
        (yyval.stmt) = mkWrite(nullptr, true, yylineno);
    }
#line 1582 "build/parser.tab.cpp"
    break;

  case 43: /* stmt: TOK_EXIT TOK_LPAREN expr TOK_RPAREN  */
#line 268 "src/parser.y"
                                          {
        (yyval.stmt) = mkExit((yyvsp[-1].expr), yylineno);
    }
#line 1590 "build/parser.tab.cpp"
    break;

  case 44: /* for_dir: TOK_TO  */
#line 274 "src/parser.y"
               { (yyval.forDir) = ForDir::To; }
#line 1596 "build/parser.tab.cpp"
    break;

  case 45: /* for_dir: TOK_DOWNTO  */
#line 275 "src/parser.y"
                 { (yyval.forDir) = ForDir::DownTo; }
#line 1602 "build/parser.tab.cpp"
    break;

  case 46: /* expr: simple_expr  */
#line 283 "src/parser.y"
                { (yyval.expr) = (yyvsp[0].expr); }
#line 1608 "build/parser.tab.cpp"
    break;

  case 47: /* expr: simple_expr TOK_EQ simple_expr  */
#line 284 "src/parser.y"
                                       { (yyval.expr) = mkBinOp(BinOpKind::Eq, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1614 "build/parser.tab.cpp"
    break;

  case 48: /* expr: simple_expr TOK_NEQ simple_expr  */
#line 285 "src/parser.y"
                                       { (yyval.expr) = mkBinOp(BinOpKind::Neq, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1620 "build/parser.tab.cpp"
    break;

  case 49: /* expr: simple_expr TOK_LT simple_expr  */
#line 286 "src/parser.y"
                                       { (yyval.expr) = mkBinOp(BinOpKind::Lt, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1626 "build/parser.tab.cpp"
    break;

  case 50: /* expr: simple_expr TOK_GT simple_expr  */
#line 287 "src/parser.y"
                                       { (yyval.expr) = mkBinOp(BinOpKind::Gt, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1632 "build/parser.tab.cpp"
    break;

  case 51: /* expr: simple_expr TOK_LTE simple_expr  */
#line 288 "src/parser.y"
                                       { (yyval.expr) = mkBinOp(BinOpKind::Lte, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1638 "build/parser.tab.cpp"
    break;

  case 52: /* expr: simple_expr TOK_GTE simple_expr  */
#line 289 "src/parser.y"
                                       { (yyval.expr) = mkBinOp(BinOpKind::Gte, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1644 "build/parser.tab.cpp"
    break;

  case 53: /* simple_expr: term  */
#line 293 "src/parser.y"
         { (yyval.expr) = (yyvsp[0].expr); }
#line 1650 "build/parser.tab.cpp"
    break;

  case 54: /* simple_expr: simple_expr TOK_PLUS term  */
#line 294 "src/parser.y"
                                  { (yyval.expr) = mkBinOp(BinOpKind::Add, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1656 "build/parser.tab.cpp"
    break;

  case 55: /* simple_expr: simple_expr TOK_MINUS term  */
#line 295 "src/parser.y"
                                  { (yyval.expr) = mkBinOp(BinOpKind::Sub, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1662 "build/parser.tab.cpp"
    break;

  case 56: /* simple_expr: simple_expr TOK_OR term  */
#line 296 "src/parser.y"
                                  { (yyval.expr) = mkBinOp(BinOpKind::Or, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1668 "build/parser.tab.cpp"
    break;

  case 57: /* term: factor  */
#line 300 "src/parser.y"
           { (yyval.expr) = (yyvsp[0].expr); }
#line 1674 "build/parser.tab.cpp"
    break;

  case 58: /* term: term TOK_STAR factor  */
#line 301 "src/parser.y"
                            { (yyval.expr) = mkBinOp(BinOpKind::Mul, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1680 "build/parser.tab.cpp"
    break;

  case 59: /* term: term TOK_DIV factor  */
#line 302 "src/parser.y"
                            { (yyval.expr) = mkBinOp(BinOpKind::Div, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1686 "build/parser.tab.cpp"
    break;

  case 60: /* term: term TOK_MOD factor  */
#line 303 "src/parser.y"
                            { (yyval.expr) = mkBinOp(BinOpKind::Mod, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1692 "build/parser.tab.cpp"
    break;

  case 61: /* term: term TOK_AND factor  */
#line 304 "src/parser.y"
                            { (yyval.expr) = mkBinOp(BinOpKind::And, (yyvsp[-2].expr), (yyvsp[0].expr), yylineno); }
#line 1698 "build/parser.tab.cpp"
    break;

  case 62: /* factor: TOK_INT_LIT  */
#line 308 "src/parser.y"
                { (yyval.expr) = mkIntLit((yyvsp[0].intVal), yylineno); }
#line 1704 "build/parser.tab.cpp"
    break;

  case 63: /* factor: TOK_TRUE  */
#line 309 "src/parser.y"
                { (yyval.expr) = mkBoolLit(true, yylineno); }
#line 1710 "build/parser.tab.cpp"
    break;

  case 64: /* factor: TOK_FALSE  */
#line 310 "src/parser.y"
                { (yyval.expr) = mkBoolLit(false, yylineno); }
#line 1716 "build/parser.tab.cpp"
    break;

  case 65: /* factor: TOK_STR_LIT  */
#line 311 "src/parser.y"
                  { (yyval.expr) = mkStringLit((yyvsp[0].strVal), yylineno); free((yyvsp[0].strVal)); }
#line 1722 "build/parser.tab.cpp"
    break;

  case 66: /* factor: TOK_IDENT  */
#line 312 "src/parser.y"
                {
        (yyval.expr) = mkIdent((yyvsp[0].strVal), yylineno); free((yyvsp[0].strVal));
    }
#line 1730 "build/parser.tab.cpp"
    break;

  case 67: /* factor: TOK_IDENT TOK_LPAREN expr_list TOK_RPAREN  */
#line 315 "src/parser.y"
                                                {
        (yyval.expr) = mkFuncCall((yyvsp[-3].strVal), (yyvsp[-1].exprList), yylineno); free((yyvsp[-3].strVal));
    }
#line 1738 "build/parser.tab.cpp"
    break;

  case 68: /* factor: TOK_LPAREN expr TOK_RPAREN  */
#line 318 "src/parser.y"
                                 { (yyval.expr) = (yyvsp[-1].expr); }
#line 1744 "build/parser.tab.cpp"
    break;

  case 69: /* factor: TOK_NOT factor  */
#line 319 "src/parser.y"
                     { (yyval.expr) = mkUnaryOp(UnaryOpKind::Not, (yyvsp[0].expr), yylineno); }
#line 1750 "build/parser.tab.cpp"
    break;

  case 70: /* factor: TOK_MINUS factor  */
#line 320 "src/parser.y"
                                    { (yyval.expr) = mkUnaryOp(UnaryOpKind::Neg, (yyvsp[0].expr), yylineno); }
#line 1756 "build/parser.tab.cpp"
    break;

  case 71: /* expr_list: expr  */
#line 324 "src/parser.y"
         {
        auto list = new std::vector<ExprPtr>();
        list->push_back((yyvsp[0].expr)); (yyval.exprList) = list;
    }
#line 1765 "build/parser.tab.cpp"
    break;

  case 72: /* expr_list: expr_list TOK_COMMA expr  */
#line 328 "src/parser.y"
                               {
        (yyvsp[-2].exprList)->push_back((yyvsp[0].expr)); (yyval.exprList) = (yyvsp[-2].exprList);
    }
#line 1773 "build/parser.tab.cpp"
    break;


#line 1777 "build/parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 333 "src/parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse error at line %d: %s\n", yylineno, s);
}
