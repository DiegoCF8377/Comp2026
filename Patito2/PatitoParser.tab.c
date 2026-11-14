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
#line 1 "PatitoParser.y"

#include <stdio.h>
#include <stdlib.h>
#include "PatitoParser.tab.h"
#include "semantic_structures.h"
#include "semantic_cube.h"
#include "stack.h"
#include "quadruples.h"
#include <string.h>

Stack operator_stack;
Stack operand_stack;
Stack type_stack;

QuadrupleList quadruples;
static int temp_counter = 0;




void yyerror(const char *s);
int yylex(void);

extern FILE *yyin;
extern int yylineno;

#line 98 "PatitoParser.tab.c"

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

#include "PatitoParser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_Tprogram = 3,                   /* Tprogram  */
  YYSYMBOL_Tmain = 4,                      /* Tmain  */
  YYSYMBOL_Tend = 5,                       /* Tend  */
  YYSYMBOL_Tvar = 6,                       /* Tvar  */
  YYSYMBOL_Tint = 7,                       /* Tint  */
  YYSYMBOL_Tfloat = 8,                     /* Tfloat  */
  YYSYMBOL_Tvoid = 9,                      /* Tvoid  */
  YYSYMBOL_Tif = 10,                       /* Tif  */
  YYSYMBOL_Telse = 11,                     /* Telse  */
  YYSYMBOL_Twhile = 12,                    /* Twhile  */
  YYSYMBOL_Tdo = 13,                       /* Tdo  */
  YYSYMBOL_Tprint = 14,                    /* Tprint  */
  YYSYMBOL_Tread = 15,                     /* Tread  */
  YYSYMBOL_Treturn = 16,                   /* Treturn  */
  YYSYMBOL_semicolon = 17,                 /* semicolon  */
  YYSYMBOL_colon = 18,                     /* colon  */
  YYSYMBOL_comma = 19,                     /* comma  */
  YYSYMBOL_assign_op = 20,                 /* assign_op  */
  YYSYMBOL_lbrace = 21,                    /* lbrace  */
  YYSYMBOL_rbrace = 22,                    /* rbrace  */
  YYSYMBOL_lparen = 23,                    /* lparen  */
  YYSYMBOL_rparen = 24,                    /* rparen  */
  YYSYMBOL_lbracket = 25,                  /* lbracket  */
  YYSYMBOL_rbracket = 26,                  /* rbracket  */
  YYSYMBOL_gt = 27,                        /* gt  */
  YYSYMBOL_lt = 28,                        /* lt  */
  YYSYMBOL_ne = 29,                        /* ne  */
  YYSYMBOL_eq = 30,                        /* eq  */
  YYSYMBOL_plus = 31,                      /* plus  */
  YYSYMBOL_minus = 32,                     /* minus  */
  YYSYMBOL_mult = 33,                      /* mult  */
  YYSYMBOL_divi = 34,                      /* divi  */
  YYSYMBOL_cte_string = 35,                /* cte_string  */
  YYSYMBOL_cte_float = 36,                 /* cte_float  */
  YYSYMBOL_cte_int = 37,                   /* cte_int  */
  YYSYMBOL_id = 38,                        /* id  */
  YYSYMBOL_unknown = 39,                   /* unknown  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_PROGRAMA = 41,                  /* PROGRAMA  */
  YYSYMBOL_ProgramaFuncs = 42,             /* ProgramaFuncs  */
  YYSYMBOL_EXPRESION = 43,                 /* EXPRESION  */
  YYSYMBOL_44_1 = 44,                      /* $@1  */
  YYSYMBOL_45_2 = 45,                      /* $@2  */
  YYSYMBOL_46_3 = 46,                      /* $@3  */
  YYSYMBOL_47_4 = 47,                      /* $@4  */
  YYSYMBOL_ASSIGN = 48,                    /* ASSIGN  */
  YYSYMBOL_CTE = 49,                       /* CTE  */
  YYSYMBOL_STATEMENT = 50,                 /* STATEMENT  */
  YYSYMBOL_StatementInBrackets = 51,       /* StatementInBrackets  */
  YYSYMBOL_BODY = 52,                      /* BODY  */
  YYSYMBOL_BodyCont = 53,                  /* BodyCont  */
  YYSYMBOL_EXP = 54,                       /* EXP  */
  YYSYMBOL_55_5 = 55,                      /* $@5  */
  YYSYMBOL_56_6 = 56,                      /* $@6  */
  YYSYMBOL_TERMINO = 57,                   /* TERMINO  */
  YYSYMBOL_58_7 = 58,                      /* $@7  */
  YYSYMBOL_59_8 = 59,                      /* $@8  */
  YYSYMBOL_InnerF_CALL = 60,               /* InnerF_CALL  */
  YYSYMBOL_F_CALL = 61,                    /* F_CALL  */
  YYSYMBOL_FCallInitial = 62,              /* FCallInitial  */
  YYSYMBOL_FCallContinuation = 63,         /* FCallContinuation  */
  YYSYMBOL_FCallMultiple = 64,             /* FCallMultiple  */
  YYSYMBOL_RETURN = 65,                    /* RETURN  */
  YYSYMBOL_READ = 66,                      /* READ  */
  YYSYMBOL_VarsOpcional = 67,              /* VarsOpcional  */
  YYSYMBOL_VARS = 68,                      /* VARS  */
  YYSYMBOL_VarStart = 69,                  /* VarStart  */
  YYSYMBOL_70_9 = 70,                      /* $@9  */
  YYSYMBOL_IdList = 71,                    /* IdList  */
  YYSYMBOL_TYPE = 72,                      /* TYPE  */
  YYSYMBOL_PRINT = 73,                     /* PRINT  */
  YYSYMBOL_PrintContenido = 74,            /* PrintContenido  */
  YYSYMBOL_75_10 = 75,                     /* $@10  */
  YYSYMBOL_76_11 = 76,                     /* $@11  */
  YYSYMBOL_PrintContenidoContinuacion = 77, /* PrintContenidoContinuacion  */
  YYSYMBOL_CYCLE = 78,                     /* CYCLE  */
  YYSYMBOL_CONDITION = 79,                 /* CONDITION  */
  YYSYMBOL_ConditionElse = 80,             /* ConditionElse  */
  YYSYMBOL_FACTOR = 81,                    /* FACTOR  */
  YYSYMBOL_FactorStart = 82,               /* FactorStart  */
  YYSYMBOL_FactorContinuacion = 83,        /* FactorContinuacion  */
  YYSYMBOL_FUNCS = 84,                     /* FUNCS  */
  YYSYMBOL_85_12 = 85,                     /* $@12  */
  YYSYMBOL_FuncsType = 86,                 /* FuncsType  */
  YYSYMBOL_FuncsIDsOpcional = 87,          /* FuncsIDsOpcional  */
  YYSYMBOL_FuncsIDs = 88,                  /* FuncsIDs  */
  YYSYMBOL_89_13 = 89,                     /* $@13  */
  YYSYMBOL_FuncsIDsContinuacion = 90       /* FuncsIDsContinuacion  */
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

#if 1

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
#endif /* 1 */

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
#define YYLAST   137

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    93,    93,   101,   102,   106,   112,   111,   116,   116,
     119,   119,   122,   122,   130,   156,   165,   176,   177,   178,
     179,   180,   181,   182,   183,   187,   188,   191,   194,   195,
     201,   200,   210,   209,   218,   228,   227,   237,   236,   245,
     252,   259,   262,   263,   266,   269,   270,   274,   296,   314,
     315,   319,   324,   323,   330,   338,   343,   350,   355,   361,
     366,   365,   372,   371,   387,   388,   392,   397,   405,   413,
     414,   418,   423,   428,   435,   440,   445,   452,   463,   471,
     470,   483,   488,   495,   496,   501,   500,   509,   510
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "Tprogram", "Tmain", "Tend",
  "Tvar", "Tint", "Tfloat", "Tvoid", "Tif", "Telse", "Twhile", "Tdo",
  "Tprint", "Tread", "Treturn", "semicolon", "colon", "comma", "assign_op",
  "lbrace", "rbrace", "lparen", "rparen", "lbracket", "rbracket", "gt",
  "lt", "ne", "eq", "plus", "minus", "mult", "divi", "cte_string",
  "cte_float", "cte_int", "id", "unknown", "$accept", "PROGRAMA",
  "ProgramaFuncs", "EXPRESION", "$@1", "$@2", "$@3", "$@4", "ASSIGN",
  "CTE", "STATEMENT", "StatementInBrackets", "BODY", "BodyCont", "EXP",
  "$@5", "$@6", "TERMINO", "$@7", "$@8", "InnerF_CALL", "F_CALL",
  "FCallInitial", "FCallContinuation", "FCallMultiple", "RETURN", "READ",
  "VarsOpcional", "VARS", "VarStart", "$@9", "IdList", "TYPE", "PRINT",
  "PrintContenido", "$@10", "$@11", "PrintContenidoContinuacion", "CYCLE",
  "CONDITION", "ConditionElse", "FACTOR", "FactorStart",
  "FactorContinuacion", "FUNCS", "$@12", "FuncsType", "FuncsIDsOpcional",
  "FuncsIDs", "$@13", "FuncsIDsContinuacion", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-104)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-53)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      15,    14,    21,    54,  -104,    66,    35,    39,  -104,  -104,
    -104,   -10,  -104,  -104,  -104,    70,  -104,    39,    37,     4,
      38,    56,  -104,  -104,    63,  -104,    13,    76,    59,    46,
      62,    64,    13,    65,    68,    22,    13,   -16,  -104,    13,
      67,    69,  -104,  -104,  -104,  -104,  -104,  -104,  -104,    55,
      35,    22,    22,    80,    -1,    57,    22,    19,    19,  -104,
    -104,    73,    81,  -104,    34,     9,  -104,  -104,  -104,  -104,
      13,    71,    22,    22,  -104,  -104,  -104,    82,    75,  -104,
    -104,    78,    79,    84,  -104,  -104,    85,    86,    87,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,  -104,
    -104,  -104,  -104,    88,    89,    90,  -104,     4,    91,    13,
      99,    22,    94,    94,    98,   100,  -104,    22,    22,    22,
      22,    22,    22,    22,    22,  -104,    22,  -104,  -104,  -104,
      66,    93,    13,    96,    -1,  -104,  -104,  -104,  -104,     1,
       1,     1,     1,     9,     9,  -104,  -104,  -104,   102,    56,
      13,   101,   105,   106,  -104,    55,  -104,   103,  -104,  -104,
    -104,  -104,  -104,   108,  -104
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,    50,     0,     4,    49,    55,
      51,     0,    57,    58,    81,     0,    82,     4,     0,     0,
       0,     0,     3,    79,     0,    56,    29,     0,     0,    54,
       0,     0,     0,     0,     0,     0,    25,     0,    18,    29,
       0,     0,    21,    17,    23,    22,    20,    19,     2,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      15,    77,     0,    78,     5,    34,    72,    39,    73,    74,
      25,     0,     0,    43,    28,    27,    41,     0,     0,    83,
      53,     0,     0,     0,    62,    60,     0,     0,     0,    77,
      75,    76,    47,     6,     8,    12,    10,    30,    32,    35,
      37,    26,    24,     0,    46,     0,    42,     0,     0,     0,
       0,     0,    65,    65,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,    14,     0,    44,    40,    85,
      50,    70,     0,     0,     0,    63,    61,    59,    48,     7,
       9,    13,    11,    31,    33,    36,    38,    45,    88,     0,
       0,     0,     0,     0,    64,     0,    86,     0,    69,    68,
      66,    67,    87,     0,    80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,   109,   -32,  -104,  -104,  -104,  -104,  -104,  -104,
     -31,    58,   -22,    92,  -103,  -104,  -104,   -72,  -104,  -104,
     -26,  -104,  -104,     6,  -104,  -104,  -104,     0,  -104,    83,
    -104,  -104,   -17,  -104,     2,  -104,  -104,    24,  -104,  -104,
    -104,   -56,  -104,    12,  -104,  -104,  -104,  -104,   -21,  -104,
    -104
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    15,    85,   117,   118,   120,   119,    38,    63,
      39,    71,    27,    40,    64,   121,   122,    65,   123,   124,
      66,    42,   105,   106,   127,    43,    44,     7,     8,    10,
      50,    11,    16,    45,    86,   113,   112,   135,    46,    47,
     151,    67,    68,    69,    17,    28,    18,    78,    79,   148,
     156
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    53,    24,    62,    72,    70,    41,    73,    19,    20,
      41,    12,    13,    41,   139,   140,   141,   142,     1,    81,
      82,     4,    56,    30,    88,    31,    32,    33,    34,    35,
      57,    58,    97,    98,    84,    59,    60,    61,    36,    70,
     103,   104,    99,   100,    41,    56,    12,    13,    14,   143,
     144,    37,     3,    57,    58,    59,    60,    89,    59,    60,
      61,    93,    94,    95,    96,    97,    98,   145,   146,    90,
      91,     5,     6,     9,    21,    23,    25,    26,   131,   133,
      29,    48,    49,    41,   -52,    51,    76,    52,    54,    75,
     129,    55,    83,    77,   104,    87,    73,   102,    92,   108,
     107,   152,   109,   110,   150,   125,    41,   111,   126,   114,
     115,   116,   132,   134,   128,   137,   130,   138,   159,   158,
     153,   155,   160,   161,    41,   164,    22,   157,   101,   163,
     149,    74,   147,    80,   162,     0,   154,   136
};

static const yytype_int16 yycheck[] =
{
      26,    32,    19,    35,    20,    36,    32,    23,    18,    19,
      36,     7,     8,    39,   117,   118,   119,   120,     3,    51,
      52,     0,    23,    10,    56,    12,    13,    14,    15,    16,
      31,    32,    31,    32,    35,    36,    37,    38,    25,    70,
      72,    73,    33,    34,    70,    23,     7,     8,     9,   121,
     122,    38,    38,    31,    32,    36,    37,    38,    36,    37,
      38,    27,    28,    29,    30,    31,    32,   123,   124,    57,
      58,    17,     6,    38,     4,    38,    38,    21,   109,   111,
      17,     5,    23,   109,    38,    23,    17,    23,    23,    22,
     107,    23,    12,    38,   126,    38,    23,    26,    17,    24,
      18,   132,    24,    24,    11,    17,   132,    23,    19,    24,
      24,    24,    13,    19,    24,    17,    25,    17,    17,   150,
      24,    19,    17,    17,   150,    17,    17,   149,    70,    26,
     130,    39,   126,    50,   155,    -1,   134,   113
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    41,    38,     0,    17,     6,    67,    68,    38,
      69,    71,     7,     8,     9,    42,    72,    84,    86,    18,
      19,     4,    42,    38,    72,    38,    21,    52,    85,    17,
      10,    12,    13,    14,    15,    16,    25,    38,    48,    50,
      53,    60,    61,    65,    66,    73,    78,    79,     5,    23,
      70,    23,    23,    50,    23,    23,    23,    31,    32,    36,
      37,    38,    43,    49,    54,    57,    60,    81,    82,    83,
      50,    51,    20,    23,    53,    22,    17,    38,    87,    88,
      69,    43,    43,    12,    35,    43,    74,    38,    43,    38,
      83,    83,    17,    27,    28,    29,    30,    31,    32,    33,
      34,    51,    26,    43,    43,    62,    63,    18,    24,    24,
      24,    23,    76,    75,    24,    24,    24,    44,    45,    47,
      46,    55,    56,    58,    59,    17,    19,    64,    24,    72,
      25,    50,    13,    43,    19,    77,    77,    17,    17,    54,
      54,    54,    54,    57,    57,    81,    81,    63,    89,    67,
      11,    80,    50,    24,    74,    19,    90,    52,    50,    17,
      17,    17,    88,    26,    17
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    44,    43,    45,    43,
      46,    43,    47,    43,    48,    49,    49,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    51,    52,    53,    53,
      55,    54,    56,    54,    54,    58,    57,    59,    57,    57,
      60,    61,    62,    62,    63,    64,    64,    65,    66,    67,
      67,    68,    70,    69,    69,    71,    71,    72,    72,    73,
      75,    74,    76,    74,    77,    77,    78,    78,    79,    80,
      80,    81,    81,    81,    82,    82,    82,    83,    83,    85,
      84,    86,    86,    87,    87,    89,    88,    90,    90
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     2,     0,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     4,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     2,     3,     2,     0,
       0,     4,     0,     4,     1,     0,     4,     0,     4,     1,
       4,     2,     1,     0,     2,     2,     0,     3,     5,     1,
       0,     2,     0,     6,     4,     1,     3,     1,     1,     5,
       0,     3,     0,     3,     2,     0,     7,     7,     7,     2,
       0,     3,     1,     1,     1,     2,     2,     1,     1,     0,
      11,     1,     1,     1,     0,     0,     5,     2,     0
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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
  switch (yykind)
    {
    case YYSYMBOL_cte_string: /* cte_string  */
#line 90 "PatitoParser.y"
            { free(((*yyvaluep).str)); }
#line 1241 "PatitoParser.tab.c"
        break;

    case YYSYMBOL_cte_float: /* cte_float  */
#line 90 "PatitoParser.y"
            { free(((*yyvaluep).str)); }
#line 1247 "PatitoParser.tab.c"
        break;

    case YYSYMBOL_cte_int: /* cte_int  */
#line 90 "PatitoParser.y"
            { free(((*yyvaluep).str)); }
#line 1253 "PatitoParser.tab.c"
        break;

    case YYSYMBOL_id: /* id  */
#line 90 "PatitoParser.y"
            { free(((*yyvaluep).str)); }
#line 1259 "PatitoParser.tab.c"
        break;

    case YYSYMBOL_IdList: /* IdList  */
#line 91 "PatitoParser.y"
            { idlist_destroy(((*yyvaluep).ids)); }
#line 1265 "PatitoParser.tab.c"
        break;

      default:
        break;
    }
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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* PROGRAMA: Tprogram id semicolon VarsOpcional ProgramaFuncs Tmain BODY Tend  */
#line 94 "PatitoParser.y"
    {
        printf("Function name: %s\n", (yyvsp[-6].str));
        free((yyvsp[-6].str));
    }
#line 1541 "PatitoParser.tab.c"
    break;

  case 5: /* EXPRESION: EXP  */
#line 107 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1549 "PatitoParser.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 112 "PatitoParser.y"
      {stack_push_operator(&operator_stack, gt);}
#line 1555 "PatitoParser.tab.c"
    break;

  case 7: /* EXPRESION: EXP gt $@1 EXP  */
#line 114 "PatitoParser.y"
      {(yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter); }
#line 1561 "PatitoParser.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 116 "PatitoParser.y"
            {stack_push_operator(&operator_stack, lt);}
#line 1567 "PatitoParser.tab.c"
    break;

  case 9: /* EXPRESION: EXP lt $@2 EXP  */
#line 117 "PatitoParser.y"
         {(yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);}
#line 1573 "PatitoParser.tab.c"
    break;

  case 10: /* $@3: %empty  */
#line 119 "PatitoParser.y"
             {stack_push_operator(&operator_stack, eq);}
#line 1579 "PatitoParser.tab.c"
    break;

  case 11: /* EXPRESION: EXP eq $@3 EXP  */
#line 120 "PatitoParser.y"
          {(yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);}
#line 1585 "PatitoParser.tab.c"
    break;

  case 12: /* $@4: %empty  */
#line 122 "PatitoParser.y"
             {stack_push_operator(&operator_stack, ne);}
#line 1591 "PatitoParser.tab.c"
    break;

  case 13: /* EXPRESION: EXP ne $@4 EXP  */
#line 123 "PatitoParser.y"
          {(yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);}
#line 1597 "PatitoParser.tab.c"
    break;

  case 14: /* ASSIGN: id assign_op EXPRESION semicolon  */
#line 131 "PatitoParser.y"
      {
          char *expression_operand = NULL;
          int expression_type;

          if (pop_expression_value(&expression_operand, &expression_type,&operand_stack,&type_stack)) {

              validate_assignment((yyvsp[-3].str), expression_type);

              quadruples_add(
                  &quadruples,
                  "=",
                  expression_operand,
                  "-",
                  (yyvsp[-3].str)
              );

              free(expression_operand);
          }

          free((yyvsp[-3].str));
      }
#line 1623 "PatitoParser.tab.c"
    break;

  case 15: /* CTE: cte_int  */
#line 157 "PatitoParser.y"
      {
          push_expression_value((yyvsp[0].str), Tint,&operand_stack,&type_stack);

          (yyval.type) = Tint;

          free((yyvsp[0].str));
      }
#line 1635 "PatitoParser.tab.c"
    break;

  case 16: /* CTE: cte_float  */
#line 166 "PatitoParser.y"
      {
          push_expression_value((yyvsp[0].str), Tfloat,&operand_stack,&type_stack);

          (yyval.type) = Tfloat;

          free((yyvsp[0].str));
      }
#line 1647 "PatitoParser.tab.c"
    break;

  case 30: /* $@5: %empty  */
#line 201 "PatitoParser.y"
      {
          stack_push_operator(&operator_stack, plus);
      }
#line 1655 "PatitoParser.tab.c"
    break;

  case 31: /* EXP: EXP plus $@5 TERMINO  */
#line 205 "PatitoParser.y"
      {
          (yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }
#line 1663 "PatitoParser.tab.c"
    break;

  case 32: /* $@6: %empty  */
#line 210 "PatitoParser.y"
      {
          stack_push_operator(&operator_stack, minus);
      }
#line 1671 "PatitoParser.tab.c"
    break;

  case 33: /* EXP: EXP minus $@6 TERMINO  */
#line 214 "PatitoParser.y"
      {
          (yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }
#line 1679 "PatitoParser.tab.c"
    break;

  case 34: /* EXP: TERMINO  */
#line 219 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1687 "PatitoParser.tab.c"
    break;

  case 35: /* $@7: %empty  */
#line 228 "PatitoParser.y"
      {
          stack_push_operator(&operator_stack, mult);
      }
#line 1695 "PatitoParser.tab.c"
    break;

  case 36: /* TERMINO: TERMINO mult $@7 FACTOR  */
#line 232 "PatitoParser.y"
      {
          (yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }
#line 1703 "PatitoParser.tab.c"
    break;

  case 37: /* $@8: %empty  */
#line 237 "PatitoParser.y"
      {
          stack_push_operator(&operator_stack, divi);
      }
#line 1711 "PatitoParser.tab.c"
    break;

  case 38: /* TERMINO: TERMINO divi $@8 FACTOR  */
#line 241 "PatitoParser.y"
      {
          (yyval.type) = reduce_pending_operation(&operator_stack,&quadruples,&operand_stack,&type_stack,&temp_counter);
      }
#line 1719 "PatitoParser.tab.c"
    break;

  case 39: /* TERMINO: FACTOR  */
#line 246 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1727 "PatitoParser.tab.c"
    break;

  case 40: /* InnerF_CALL: id lparen FCallInitial rparen  */
#line 253 "PatitoParser.y"
      {
          (yyval.type) = get_function_return_type((yyvsp[-3].str));
          free((yyvsp[-3].str));
      }
#line 1736 "PatitoParser.tab.c"
    break;

  case 47: /* RETURN: Treturn EXPRESION semicolon  */
#line 275 "PatitoParser.y"
      {
          char *operand = NULL;
          int expression_type;

          if (pop_expression_value(&operand, &expression_type,&operand_stack,&type_stack)) {
              validate_return(expression_type);

              quadruples_add(
                  &quadruples,
                  "RETURN",
                  operand,
                  "-",
                  "-"
              );

              free(operand);
          }
      }
#line 1759 "PatitoParser.tab.c"
    break;

  case 48: /* READ: Tread lparen id rparen semicolon  */
#line 297 "PatitoParser.y"
      {
          validate_read((yyvsp[-2].str));

          quadruples_add(
              &quadruples,
              "READ",
              "-",
              "-",
              (yyvsp[-2].str)
          );

          free((yyvsp[-2].str));
      }
#line 1777 "PatitoParser.tab.c"
    break;

  case 52: /* $@9: %empty  */
#line 324 "PatitoParser.y"
      {
          declare_id_list((yyvsp[-3].ids), (yyvsp[-1].type));
          idlist_destroy((yyvsp[-3].ids));
      }
#line 1786 "PatitoParser.tab.c"
    break;

  case 54: /* VarStart: IdList colon TYPE semicolon  */
#line 331 "PatitoParser.y"
      {
          declare_id_list((yyvsp[-3].ids), (yyvsp[-1].type));
          idlist_destroy((yyvsp[-3].ids));
      }
#line 1795 "PatitoParser.tab.c"
    break;

  case 55: /* IdList: id  */
#line 339 "PatitoParser.y"
      {
          (yyval.ids) = idlist_create((yyvsp[0].str));
      }
#line 1803 "PatitoParser.tab.c"
    break;

  case 56: /* IdList: IdList comma id  */
#line 344 "PatitoParser.y"
      {
          (yyval.ids) = idlist_append((yyvsp[-2].ids), (yyvsp[0].str));
      }
#line 1811 "PatitoParser.tab.c"
    break;

  case 57: /* TYPE: Tint  */
#line 351 "PatitoParser.y"
      {
          (yyval.type) = Tint;
      }
#line 1819 "PatitoParser.tab.c"
    break;

  case 58: /* TYPE: Tfloat  */
#line 356 "PatitoParser.y"
      {
          (yyval.type) = Tfloat;
      }
#line 1827 "PatitoParser.tab.c"
    break;

  case 60: /* $@10: %empty  */
#line 366 "PatitoParser.y"
      {
          emit_print(&quadruples,&operand_stack,&type_stack);
      }
#line 1835 "PatitoParser.tab.c"
    break;

  case 62: /* $@11: %empty  */
#line 372 "PatitoParser.y"
      {
          quadruples_add(
              &quadruples,
              "PRINT",
              (yyvsp[0].str),
              "-",
              "-"
          );

          free((yyvsp[0].str));
      }
#line 1851 "PatitoParser.tab.c"
    break;

  case 66: /* CYCLE: Twhile lparen EXPRESION rparen Tdo STATEMENT semicolon  */
#line 393 "PatitoParser.y"
      {
          validate_condition((yyvsp[-4].type));
          discard_expression(&operand_stack,&type_stack);
      }
#line 1860 "PatitoParser.tab.c"
    break;

  case 67: /* CYCLE: Tdo STATEMENT Twhile lparen EXPRESION rparen semicolon  */
#line 398 "PatitoParser.y"
      {
          validate_condition((yyvsp[-2].type));
          discard_expression(&operand_stack,&type_stack);
      }
#line 1869 "PatitoParser.tab.c"
    break;

  case 68: /* CONDITION: Tif lparen EXPRESION rparen STATEMENT ConditionElse semicolon  */
#line 406 "PatitoParser.y"
      {
          validate_condition((yyvsp[-4].type));
          discard_expression(&operand_stack,&type_stack);
      }
#line 1878 "PatitoParser.tab.c"
    break;

  case 71: /* FACTOR: lparen EXPRESION rparen  */
#line 419 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[-1].type);
      }
#line 1886 "PatitoParser.tab.c"
    break;

  case 72: /* FACTOR: InnerF_CALL  */
#line 424 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1894 "PatitoParser.tab.c"
    break;

  case 73: /* FACTOR: FactorStart  */
#line 429 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1902 "PatitoParser.tab.c"
    break;

  case 74: /* FactorStart: FactorContinuacion  */
#line 436 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1910 "PatitoParser.tab.c"
    break;

  case 75: /* FactorStart: plus FactorContinuacion  */
#line 441 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1918 "PatitoParser.tab.c"
    break;

  case 76: /* FactorStart: minus FactorContinuacion  */
#line 446 "PatitoParser.y"
      {
          (yyval.type) = apply_unary_minus(&quadruples,&operand_stack,&type_stack,&temp_counter);
      }
#line 1926 "PatitoParser.tab.c"
    break;

  case 77: /* FactorContinuacion: id  */
#line 453 "PatitoParser.y"
      {
          int variable_type = get_variable_type((yyvsp[0].str));

          push_expression_value((yyvsp[0].str), variable_type,&operand_stack,&type_stack);

          (yyval.type) = variable_type;

          free((yyvsp[0].str));
      }
#line 1940 "PatitoParser.tab.c"
    break;

  case 78: /* FactorContinuacion: CTE  */
#line 464 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1948 "PatitoParser.tab.c"
    break;

  case 79: /* $@12: %empty  */
#line 471 "PatitoParser.y"
      {
          begin_function((yyvsp[0].str), (yyvsp[-1].type));
          free((yyvsp[0].str));
      }
#line 1957 "PatitoParser.tab.c"
    break;

  case 80: /* FUNCS: FuncsType id $@12 lparen FuncsIDsOpcional rparen lbracket VarsOpcional BODY rbracket semicolon  */
#line 477 "PatitoParser.y"
      {
          finish_function();
      }
#line 1965 "PatitoParser.tab.c"
    break;

  case 81: /* FuncsType: Tvoid  */
#line 484 "PatitoParser.y"
      {
          (yyval.type) = Tvoid;
      }
#line 1973 "PatitoParser.tab.c"
    break;

  case 82: /* FuncsType: TYPE  */
#line 489 "PatitoParser.y"
      {
          (yyval.type) = (yyvsp[0].type);
      }
#line 1981 "PatitoParser.tab.c"
    break;

  case 85: /* $@13: %empty  */
#line 501 "PatitoParser.y"
      {
          declare_parameter((yyvsp[-2].str), (yyvsp[0].type));
          free((yyvsp[-2].str));
      }
#line 1990 "PatitoParser.tab.c"
    break;


#line 1994 "PatitoParser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 513 "PatitoParser.y"


void yyerror(const char *s) {
    fprintf(stderr,
        "[SYNTAX ERROR] Line %d: %s\n",
        yylineno,
        s
    );
}

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");

    if (!input) {
        perror("Error opening source file");
        return 1;
    }

    yyin = input;
    
    stack_init(&operator_stack, 20);
    stack_init(&operand_stack, 20);
    stack_init(&type_stack, 20);

    quadruples_init(&quadruples, 100);

    init_semantic_cube();
    init_semantic_context();

    yydebug = 0;

    int result = yyparse();

    if (result == 0 && semantic_context.semantic_errors == 0) {
        printf("\nCompilation successful!\n");
    } else {
        printf("\nCompilation failed.\n");
        printf("Semantic errors: %d\n",
            semantic_context.semantic_errors);
    }

    fclose(input);
    printf("\nGENERATED QUADRUPLES:\n");

    quadruples_print(&quadruples, stdout);

    stack_destroy(&operator_stack);
    stack_destroy(&operand_stack);
    stack_destroy(&type_stack);

    quadruples_destroy(&quadruples);
    
    return (result != 0 || semantic_context.semantic_errors > 0);
}
