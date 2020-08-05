/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "def.h"
#include <string.h>

#define YYSTYPE Pnode

extern struct SCode *tot_prog;
struct SCode *current_prog;

FILE *yyin;

struct SCode *sub_prog10 ;

extern char *yytext;
extern Value lexval;
extern int line;
extern FILE *yyin;
extern int oid_g;

char *lista_id[SYMTAB_SIZE];
char *lista_id_locale[50];
int indice_locale = 0;
symb_class current_class;

extern struct bucket *symbol_table;

int indice = 0;
Pnode root = NULL;

struct bucket *temp_env;
struct bucket **temp_descr;
struct bucket *current_env;

char *id_func;
symb_type current_type;
int numero_param_formali = 0;
int oid_locale = 0;
int *current_oid;
int isRead = 0;


#line 112 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FUNC = 258,
    BODY = 259,
    END = 260,
    IF = 261,
    THEN = 262,
    ELSE = 263,
    WHILE = 264,
    DO = 265,
    FOR = 266,
    TO = 267,
    BREAK = 268,
    RETURN = 269,
    WRITE = 270,
    WRITELN = 271,
    READ = 272,
    AND = 273,
    OR = 274,
    NOT = 275,
    EQ = 276,
    NE = 277,
    GE = 278,
    GT = 279,
    LT = 280,
    LE = 281,
    MUL = 282,
    PLUS = 283,
    DIV = 284,
    MINUS = 285,
    DECL = 286,
    VOID = 287,
    INTEGER = 288,
    STRING = 289,
    BOOLEAN = 290,
    REAL = 291,
    REALCONST = 292,
    INTCONST = 293,
    STRCONST = 294,
    ID = 295,
    BOOLCONST = 296,
    ASSIGN = 297,
    ERROR = 298
  };
#endif
/* Tokens.  */
#define FUNC 258
#define BODY 259
#define END 260
#define IF 261
#define THEN 262
#define ELSE 263
#define WHILE 264
#define DO 265
#define FOR 266
#define TO 267
#define BREAK 268
#define RETURN 269
#define WRITE 270
#define WRITELN 271
#define READ 272
#define AND 273
#define OR 274
#define NOT 275
#define EQ 276
#define NE 277
#define GE 278
#define GT 279
#define LT 280
#define LE 281
#define MUL 282
#define PLUS 283
#define DIV 284
#define MINUS 285
#define DECL 286
#define VOID 287
#define INTEGER 288
#define STRING 289
#define BOOLEAN 290
#define REAL 291
#define REALCONST 292
#define INTCONST 293
#define STRCONST 294
#define ID 295
#define BOOLCONST 296
#define ASSIGN 297
#define ERROR 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   152

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  53
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

#define YYUNDEFTOK  2
#define YYMAXUTOK   298


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      47,    48,     2,     2,    46,     2,    44,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    45,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    48,    48,    52,    53,    55,    55,    57,    57,    62,
      68,    93,   116,   137,   157,   178,   179,   181,   181,   181,
     182,   181,   209,   210,   212,   213,   215,   215,   215,   217,
     219,   220,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   232,   232,   234,   237,   238,   240,   243,   243,   246,
     248,   249,   251,   251,   251,   253,   256,   257,   259,   260,
     262,   265,   267,   268,   270,   273,   275,   276,   277,   278,
     279,   280,   282,   285,   287,   288,   290,   293,   295,   296,
     299,   303,   304,   305,   306,   307,   308,   312,   313,   315,
     316,   317,   318,   320,   320,   322,   323,   325,   327,   328
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNC", "BODY", "END", "IF", "THEN",
  "ELSE", "WHILE", "DO", "FOR", "TO", "BREAK", "RETURN", "WRITE",
  "WRITELN", "READ", "AND", "OR", "NOT", "EQ", "NE", "GE", "GT", "LT",
  "LE", "MUL", "PLUS", "DIV", "MINUS", "DECL", "VOID", "INTEGER", "STRING",
  "BOOLEAN", "REAL", "REALCONST", "INTCONST", "STRCONST", "ID",
  "BOOLCONST", "ASSIGN", "ERROR", "'.'", "';'", "','", "'('", "')'",
  "$accept", "program", "var_decl_list", "var_decl", "$@1", "id_list",
  "@2", "type", "func_decl_list", "func_decl", "@3", "$@4", "$@5", "$@6",
  "opt_param_list", "param_list", "param_decl", "$@7", "@8", "body",
  "stat_list", "stat", "assign_stat", "@9", "if_stat", "opt_else_stat",
  "while_stat", "for_stat", "@10", "return_stat", "opt_expr", "read_stat",
  "$@11", "$@12", "write_stat", "write_op", "expr_list", "expr",
  "logic_op", "bool_term", "rel_op", "rel_term", "low_prec_op", "low_term",
  "high_prec_op", "factor", "unary_op", "const", "func_call", "@13",
  "opt_expr_list", "cond_expr", "cast", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,    46,    59,    44,    40,    41
};
# endif

#define YYPACT_NINF (-93)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-94)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -35,    32,    56,   -35,    16,   -93,    23,    64,    56,   -93,
      27,    49,   -93,     8,    38,   -93,    58,    67,   -93,     6,
       6,    65,   -93,     6,   -93,   -93,   -93,    59,   103,    66,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,    62,   -93,   -93,
      16,   -93,   -93,   -93,   -93,   -93,    68,    63,     6,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,    59,   -93,     6,    11,
     -93,    53,    25,   -93,     6,   -93,   -93,   -93,    70,    74,
     -93,   -93,    69,    71,    72,    73,   -93,     8,     6,   -93,
     -93,    75,    43,   -11,     8,   -93,   -93,     6,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,     6,     6,   -93,   -93,
       6,   -93,     6,     8,    77,    16,     6,     6,   -93,    78,
       9,    79,   -93,    82,    81,     6,   -93,   104,   -93,    36,
      25,   -93,    -8,   111,     6,   -93,    69,   -93,    83,   -93,
       6,    91,   -93,   -93,    52,     8,   119,   -93,   -93,    39,
      85,   -93,   -93,   -93,   -93,    94,     6,   -93,   -93,     6,
     -93,    67,    67,    15,    76,   -35,   -93,   -93,     8,    64,
     125,    89,   -93,   -93,   -93
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,    16,     4,     0,     1,     0,     0,    16,     3,
       9,     0,    17,     0,     0,    15,     0,     0,    18,     0,
       0,     0,    40,    51,    56,    57,    52,    41,     0,     0,
      32,    33,    34,    35,    36,    37,    38,     0,    39,     2,
       0,    14,    10,    12,    13,    11,     0,     0,     0,    88,
      87,    98,    99,    90,    89,    91,    82,    92,     0,     0,
      61,    65,    73,    77,     0,    83,    84,    85,     0,     0,
      47,    49,    50,     0,     0,     0,    29,    31,     0,     8,
       6,    23,     0,     0,     0,    62,    63,     0,    66,    67,
      69,    68,    70,    71,    74,    75,     0,     0,    78,    79,
       0,    80,     0,     0,     0,     0,     0,    96,    30,     0,
      59,     0,    22,    25,     0,     0,    81,    45,    60,    64,
      72,    76,     0,     0,     0,    53,    42,    95,     0,    55,
       0,     0,    26,    27,     0,     0,     0,    86,    46,     0,
       0,    94,    58,    19,    24,     0,     0,    44,    43,     0,
      54,     0,     0,     0,     0,     4,    28,    97,     0,     0,
       0,     0,    48,    20,    21
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,    -3,   -93,   -93,   -36,   -93,   -55,   127,   -93,
     -93,   -93,   -93,   -93,   -93,     4,   -93,   -93,   -93,   -22,
     -68,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,   -92,   -17,   -93,    51,
     -93,    44,   -93,    42,   -93,   -51,   -93,   -93,   -12,   -93,
     -93,   -93,   -93
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     4,    11,    16,    46,     7,     8,
      18,    47,   151,   164,   111,   112,   113,   114,   145,    14,
      28,    29,    30,    74,    31,   136,    32,    33,   104,    34,
      71,    35,    73,   140,    36,    37,   109,   110,    87,    60,
      96,    61,    97,    62,   100,    63,    64,    65,    66,    75,
     128,    67,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       9,    38,    59,    69,    79,    -5,    72,    85,    86,   108,
      85,    86,    48,   101,    19,   127,   117,    20,    84,    21,
     157,    22,    23,    24,    25,    26,    49,    85,    86,    85,
      86,    82,     5,    85,    86,   123,    50,   116,   142,    51,
     137,    83,    52,    53,    54,    55,    56,    57,    27,   121,
     115,   149,    98,    58,    99,   130,    10,    85,    86,     6,
     146,    85,    86,    12,    94,    38,    95,   147,    13,   125,
      85,    86,    38,    -7,    88,    89,    90,    91,    92,    93,
      17,    94,    39,    95,   103,   122,   158,    85,    86,   126,
     160,    38,    85,    86,    85,    86,   155,   156,   134,    41,
      42,    43,    44,    45,    40,    70,   -93,   139,    76,    78,
      81,    77,   135,    80,   106,   -26,   138,   102,   105,   124,
     107,   133,   143,    38,   148,   152,   129,   131,   132,   153,
     162,   141,   154,   150,   163,    15,   144,   161,   118,   120,
     119,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,   159
};

static const yytype_int16 yycheck[] =
{
       3,    13,    19,    20,    40,    40,    23,    18,    19,    77,
      18,    19,     6,    64,     6,   107,    84,     9,     7,    11,
       5,    13,    14,    15,    16,    17,    20,    18,    19,    18,
      19,    48,     0,    18,    19,   103,    30,    48,   130,    33,
      48,    58,    36,    37,    38,    39,    40,    41,    40,   100,
       7,    12,    27,    47,    29,    46,    40,    18,    19,     3,
       8,    18,    19,    40,    28,    77,    30,   135,     4,   105,
      18,    19,    84,    46,    21,    22,    23,    24,    25,    26,
      31,    28,    44,    30,    10,   102,    10,    18,    19,   106,
     158,   103,    18,    19,    18,    19,   151,   152,   115,    32,
      33,    34,    35,    36,    46,    40,    47,   124,     5,    47,
      47,    45,     8,    45,    42,    40,     5,    47,    47,    42,
      47,    40,    31,   135,     5,    31,    48,    48,    46,   146,
       5,    48,   149,    48,    45,     8,   132,   159,    87,    97,
      96,    -1,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,
      -1,    -1,   155
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,    52,    53,     0,     3,    57,    58,    51,
      40,    54,    40,     4,    68,    57,    55,    31,    59,     6,
       9,    11,    13,    14,    15,    16,    17,    40,    69,    70,
      71,    73,    75,    76,    78,    80,    83,    84,    97,    44,
      46,    32,    33,    34,    35,    36,    56,    60,     6,    20,
      30,    33,    36,    37,    38,    39,    40,    41,    47,    86,
      88,    90,    92,    94,    95,    96,    97,   100,   101,    86,
      40,    79,    86,    81,    72,    98,     5,    45,    47,    54,
      45,    47,    86,    86,     7,    18,    19,    87,    21,    22,
      23,    24,    25,    26,    28,    30,    89,    91,    27,    29,
      93,    94,    47,    10,    77,    47,    42,    47,    69,    85,
      86,    63,    64,    65,    66,     7,    48,    69,    88,    90,
      92,    94,    86,    69,    42,    54,    86,    85,    99,    48,
      46,    48,    46,    40,    86,     8,    74,    48,     5,    86,
      82,    48,    85,    31,    64,    67,     8,    69,     5,    12,
      48,    61,    31,    86,    86,    56,    56,     5,    10,    51,
      69,    68,     5,    45,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    53,    52,    55,    54,    54,
      56,    56,    56,    56,    56,    57,    57,    59,    60,    61,
      62,    58,    63,    63,    64,    64,    66,    67,    65,    68,
      69,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    72,    71,    73,    74,    74,    75,    77,    76,    78,
      79,    79,    81,    82,    80,    83,    84,    84,    85,    85,
      86,    86,    87,    87,    88,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    91,    91,    92,    92,    93,    93,
      94,    94,    94,    94,    94,    94,    94,    95,    95,    96,
      96,    96,    96,    98,    97,    99,    99,   100,   101,   101
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     0,     0,     5,     0,     4,     1,
       1,     1,     1,     1,     1,     2,     0,     0,     0,     0,
       0,    14,     1,     0,     3,     1,     0,     0,     5,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     6,     2,     0,     5,     0,    10,     2,
       1,     0,     0,     0,     6,     4,     1,     1,     3,     1,
       3,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       2,     3,     1,     1,     1,     1,     4,     1,     1,     1,
       1,     1,     1,     0,     5,     1,     0,     7,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 48 "parser.y"
                                                {root = yyval = nontermnode(N_PROGRAM); yyval->child = nontermnode(N_VAR_DECL_LIST); yyval->child->child = yyvsp[-3]; 
                                                 yyval->child->brother = nontermnode(N_FUNC_DECL_LIST); yyval->child->brother->child = yyvsp[-2];
                                                 yyval->child->brother->brother = yyvsp[-1]; insert_func("smain",S_VOID_,init_pf(0),NULL,symbol_table);}
#line 1542 "y.tab.c"
    break;

  case 3:
#line 52 "parser.y"
                                       {yyval = yyvsp[-1]; yyvsp[-1]->brother = yyvsp[0];}
#line 1548 "y.tab.c"
    break;

  case 4:
#line 53 "parser.y"
                {yyval = NULL;}
#line 1554 "y.tab.c"
    break;

  case 5:
#line 55 "parser.y"
           {current_class = VAR;}
#line 1560 "y.tab.c"
    break;

  case 6:
#line 55 "parser.y"
                                                       {yyval = nontermnode(N_VAR_DECL); yyval->child = nontermnode(N_ID_LIST); yyval->child->child = yyvsp[-3]; yyval->child->brother = yyvsp[-1];}
#line 1566 "y.tab.c"
    break;

  case 7:
#line 57 "parser.y"
             {yyval = idnode();}
#line 1572 "y.tab.c"
    break;

  case 8:
#line 57 "parser.y"
                                          {yyval = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];
          if (!isRead) {
            lista_id[indice++] = yyvsp[-2]->value.sval;    
          }
          }
#line 1582 "y.tab.c"
    break;

  case 9:
#line 62 "parser.y"
             {yyval = idnode(); 
        if (!isRead) {
            lista_id[indice++] = yyval->value.sval;    
          }}
#line 1591 "y.tab.c"
    break;

  case 10:
#line 68 "parser.y"
               {yyval = keynode(T_INTEGER);


                if (current_class == FUN)
                {
                  current_type = S_INTEGER;
                } else {
                  
                  int i;

                  for (i = 0; i < indice; i++)
                  {
                    insert(lista_id[i], current_class, S_INTEGER, current_env, current_oid);
                    if (current_class == PAR)
                    {
                      temp_descr[numero_param_formali - 1] = find_in_chain(lista_id[i], &current_env[hash(lista_id[i])]);
                    }
                    
                  }
                  
                  
                  indice = 0;
                };
                
                }
#line 1621 "y.tab.c"
    break;

  case 11:
#line 93 "parser.y"
            {yyval = keynode(T_REAL); 
              if (current_class == FUN)
                {
                  current_type = S_REAL;
                } else {
                  
                  int i;

                  for (i = 0; i < indice; i++)
                  {
                    insert(lista_id[i], current_class, S_REAL, current_env, current_oid);

                    if (current_class == PAR)
                    {
                      temp_descr[numero_param_formali - 1] = find_in_chain(lista_id[i], &current_env[hash(lista_id[i])]);
                    }
                    
                  }
                  
                  indice = 0;
                };
                
            }
#line 1649 "y.tab.c"
    break;

  case 12:
#line 116 "parser.y"
              {yyval = keynode(T_STRING);
                if (current_class == FUN)
                {
                  current_type = S_STRING;
                } else {
                  
                  int i;

                  for (i = 0; i < indice; i++)
                  {
                    insert(lista_id[i], current_class, S_STRING, current_env, current_oid);
                    if (current_class == PAR)
                    {
                      temp_descr[numero_param_formali - 1] = find_in_chain(lista_id[i], &current_env[hash(lista_id[i])]);
                    }
                    
                  }
                  
                  indice = 0;
                };
              }
#line 1675 "y.tab.c"
    break;

  case 13:
#line 137 "parser.y"
               {yyval = keynode(T_BOOLEAN);
                if (current_class == FUN)
                {
                  current_type = S_BOOLEAN_;
                } else {
                  
                  int i;

                  for (i = 0; i < indice; i++)
                  {
                    insert(lista_id[i], current_class, S_BOOLEAN_, current_env, current_oid);
                    if (current_class == PAR)
                    {
                      temp_descr[numero_param_formali - 1] = find_in_chain(lista_id[i], &current_env[hash(lista_id[i])]);
                    }
                  }
              
                  indice = 0;
                };
              }
#line 1700 "y.tab.c"
    break;

  case 14:
#line 157 "parser.y"
            {yyval = keynode(T_VOID);
              if (current_class == FUN)
                {
                  current_type = S_VOID_;
                } else {
                  
                  int i;

                  for (i = 0; i < indice; i++)
                  {
                    insert(lista_id[i], current_class, S_VOID_, current_env, current_oid);
                    if (current_class == PAR)
                    {
                        temp_descr[numero_param_formali-1] = find_in_chain(lista_id[i],&current_env[hash(lista_id[i])]);           
                    }
                  }
                  
                  indice = 0;
                };
            }
#line 1725 "y.tab.c"
    break;

  case 15:
#line 178 "parser.y"
                                          {yyval = yyvsp[-1]; yyvsp[-1]->brother = yyvsp[0];}
#line 1731 "y.tab.c"
    break;

  case 16:
#line 179 "parser.y"
                 {yyval = NULL;}
#line 1737 "y.tab.c"
    break;

  case 17:
#line 181 "parser.y"
                    {yyval = idnode(); id_func = yyval->value.sval;}
#line 1743 "y.tab.c"
    break;

  case 18:
#line 181 "parser.y"
                                                               {current_env = temp_env; current_oid = &oid_locale;}
#line 1749 "y.tab.c"
    break;

  case 19:
#line 181 "parser.y"
                                                                                                                                               {current_class = FUN;}
#line 1755 "y.tab.c"
    break;

  case 20:
#line 182 "parser.y"
            {current_env = symbol_table; current_oid = &oid_g;}
#line 1761 "y.tab.c"
    break;

  case 21:
#line 182 "parser.y"
                                                                {yyval = nontermnode(N_FUNC_DECL); 
            yyval->child = yyvsp[-11];

            if (yyvsp[-8] == NULL)
            {
              yyvsp[-11]->brother = yyvsp[-4];
            }
            else
            {
              yyvsp[-11]->brother = yyvsp[-8];
              yyvsp[-8]->brother = yyvsp[-4];
            }
            
            yyvsp[-4]->brother = nontermnode(N_VAR_DECL_LIST); yyvsp[-4]->brother->child = yyvsp[-3]; yyvsp[-4]->brother->brother = yyvsp[-2];
            

            struct param_formali pf = init_pf(numero_param_formali);
            pf.descr = temp_descr;
            insert_func(id_func,current_type,pf,temp_env,symbol_table);
            
            numero_param_formali = 0;
            oid_locale = 0;
            temp_env = init_symbol_table(SYMTAB_SIZE);
            temp_descr = (struct bucket **)malloc(25 * sizeof(struct bucket *));}
#line 1790 "y.tab.c"
    break;

  case 22:
#line 209 "parser.y"
                            {yyval = nontermnode(N_OPT_PARAM_LIST); yyval->child = yyvsp[0];}
#line 1796 "y.tab.c"
    break;

  case 23:
#line 210 "parser.y"
                 {yyval = NULL;}
#line 1802 "y.tab.c"
    break;

  case 24:
#line 212 "parser.y"
                                       {yyval = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];}
#line 1808 "y.tab.c"
    break;

  case 25:
#line 213 "parser.y"
                        {yyval = yyvsp[0];}
#line 1814 "y.tab.c"
    break;

  case 26:
#line 215 "parser.y"
             {current_class = PAR; numero_param_formali++;}
#line 1820 "y.tab.c"
    break;

  case 27:
#line 215 "parser.y"
                                                              {yyval = idnode(); lista_id[indice++] = yyval->value.sval;}
#line 1826 "y.tab.c"
    break;

  case 28:
#line 215 "parser.y"
                                                                                                                              {yyval = nontermnode(N_PARAM_DECL); yyval->child = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];}
#line 1832 "y.tab.c"
    break;

  case 29:
#line 217 "parser.y"
                          {yyval = nontermnode(N_STAT_LIST); yyval->child = yyvsp[-1];}
#line 1838 "y.tab.c"
    break;

  case 30:
#line 219 "parser.y"
                               {yyval = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];}
#line 1844 "y.tab.c"
    break;

  case 31:
#line 220 "parser.y"
                     {yyval = yyvsp[-1];}
#line 1850 "y.tab.c"
    break;

  case 32:
#line 222 "parser.y"
                   {yyval = yyvsp[0];}
#line 1856 "y.tab.c"
    break;

  case 33:
#line 223 "parser.y"
               {yyval = yyvsp[0];}
#line 1862 "y.tab.c"
    break;

  case 34:
#line 224 "parser.y"
                  {yyval = yyvsp[0];}
#line 1868 "y.tab.c"
    break;

  case 35:
#line 225 "parser.y"
                {yyval = yyvsp[0];}
#line 1874 "y.tab.c"
    break;

  case 36:
#line 226 "parser.y"
                   {yyval = yyvsp[0];}
#line 1880 "y.tab.c"
    break;

  case 37:
#line 227 "parser.y"
                 {yyval = yyvsp[0];}
#line 1886 "y.tab.c"
    break;

  case 38:
#line 228 "parser.y"
                  {yyval = yyvsp[0];}
#line 1892 "y.tab.c"
    break;

  case 39:
#line 229 "parser.y"
                 {yyval = yyvsp[0];}
#line 1898 "y.tab.c"
    break;

  case 40:
#line 230 "parser.y"
             {yyval = keynode(T_BREAK);}
#line 1904 "y.tab.c"
    break;

  case 41:
#line 232 "parser.y"
                 {yyval = idnode();}
#line 1910 "y.tab.c"
    break;

  case 42:
#line 232 "parser.y"
                                              {yyval = nontermnode(N_ASSIGN_STAT); yyval->child = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];}
#line 1916 "y.tab.c"
    break;

  case 43:
#line 234 "parser.y"
                                                   {yyval = nontermnode(N_IF_STAT); yyval->child = yyvsp[-4];
          yyvsp[-4]->brother = nontermnode(N_STAT_LIST); yyvsp[-4]->brother->child = yyvsp[-2]; yyvsp[-4]->brother->brother = yyvsp[-1];}
#line 1923 "y.tab.c"
    break;

  case 44:
#line 237 "parser.y"
                               {yyval = nontermnode(N_STAT_LIST); yyval->child = yyvsp[0];}
#line 1929 "y.tab.c"
    break;

  case 45:
#line 238 "parser.y"
                {yyval = NULL;}
#line 1935 "y.tab.c"
    break;

  case 46:
#line 240 "parser.y"
                                         {yyval = nontermnode(N_WHILE_STAT); yyval->child = yyvsp[-3];
             yyvsp[-3]->brother = nontermnode(N_STAT_LIST); yyvsp[-3]->brother->child = yyvsp[-1];}
#line 1942 "y.tab.c"
    break;

  case 47:
#line 243 "parser.y"
                  {yyval = idnode();}
#line 1948 "y.tab.c"
    break;

  case 48:
#line 243 "parser.y"
                                                                        {yyval = nontermnode(N_FOR_STAT); yyval->child = yyvsp[-7]; 
            yyvsp[-7]->brother = yyvsp[-5]; yyvsp[-5]->brother = yyvsp[-3]; yyvsp[-3]->brother = nontermnode(N_STAT_LIST); yyvsp[-3]->brother->child = yyvsp[-1];}
#line 1955 "y.tab.c"
    break;

  case 49:
#line 246 "parser.y"
                              {yyval = nontermnode(N_RETURN_STAT); yyval->child = yyvsp[0];}
#line 1961 "y.tab.c"
    break;

  case 50:
#line 248 "parser.y"
                {yyval = yyvsp[0];}
#line 1967 "y.tab.c"
    break;

  case 51:
#line 249 "parser.y"
           {yyval = NULL;}
#line 1973 "y.tab.c"
    break;

  case 52:
#line 251 "parser.y"
                 {isRead = 1;}
#line 1979 "y.tab.c"
    break;

  case 53:
#line 251 "parser.y"
                                          {isRead = 0;}
#line 1985 "y.tab.c"
    break;

  case 54:
#line 251 "parser.y"
                                                            {yyval = nontermnode(N_READ_STAT);yyval->child = nontermnode(N_ID_LIST); yyval->child->child = yyvsp[-2];}
#line 1991 "y.tab.c"
    break;

  case 55:
#line 253 "parser.y"
                                        {yyval = nontermnode(N_WRITE_STAT); yyval->op_code = yyvsp[-3]->type; yyval->child = yyvsp[-3]; yyvsp[-3]->brother = nontermnode(N_EXPR_LIST); 
                                        yyvsp[-3]->brother->child = yyvsp[-1];}
#line 1998 "y.tab.c"
    break;

  case 56:
#line 256 "parser.y"
                 {yyval = keynode(T_WRITE);}
#line 2004 "y.tab.c"
    break;

  case 57:
#line 257 "parser.y"
                   {yyval = keynode(T_WRITELN);}
#line 2010 "y.tab.c"
    break;

  case 58:
#line 259 "parser.y"
                               {yyval = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];}
#line 2016 "y.tab.c"
    break;

  case 59:
#line 260 "parser.y"
                 {yyval = yyvsp[0];}
#line 2022 "y.tab.c"
    break;

  case 60:
#line 262 "parser.y"
                               {yyval = nontermnode(N_LOGIC_EXPR);yyval->child = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];
                                yyval->op_code = yyvsp[-1]->type;
                                }
#line 2030 "y.tab.c"
    break;

  case 61:
#line 265 "parser.y"
                  {yyval = yyvsp[0];}
#line 2036 "y.tab.c"
    break;

  case 62:
#line 267 "parser.y"
               {yyval = keynode(T_AND);}
#line 2042 "y.tab.c"
    break;

  case 63:
#line 268 "parser.y"
              {yyval = keynode(T_OR);}
#line 2048 "y.tab.c"
    break;

  case 64:
#line 270 "parser.y"
                                      {yyval = nontermnode(N_REL_EXPR); yyval->child = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];
                                        yyval->op_code = yyvsp[-1]->type;
                                      }
#line 2056 "y.tab.c"
    break;

  case 65:
#line 273 "parser.y"
                     {yyval = yyvsp[0];}
#line 2062 "y.tab.c"
    break;

  case 66:
#line 275 "parser.y"
           {yyval = keynode(T_EQ);}
#line 2068 "y.tab.c"
    break;

  case 67:
#line 276 "parser.y"
           {yyval = keynode(T_NE);}
#line 2074 "y.tab.c"
    break;

  case 68:
#line 277 "parser.y"
            {yyval = keynode(T_GT);}
#line 2080 "y.tab.c"
    break;

  case 69:
#line 278 "parser.y"
            {yyval = keynode(T_GE);}
#line 2086 "y.tab.c"
    break;

  case 70:
#line 279 "parser.y"
            {yyval = keynode(T_LT);}
#line 2092 "y.tab.c"
    break;

  case 71:
#line 280 "parser.y"
            {yyval = keynode(T_LE);}
#line 2098 "y.tab.c"
    break;

  case 72:
#line 282 "parser.y"
                                         {yyval = nontermnode(N_MATH_EXPR); yyval->child = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];
                                          yyval->op_code = yyvsp[-1]->type;
                                         }
#line 2106 "y.tab.c"
    break;

  case 73:
#line 285 "parser.y"
                    {yyval = yyvsp[0];}
#line 2112 "y.tab.c"
    break;

  case 74:
#line 287 "parser.y"
                   {yyval = keynode(T_PLUS);}
#line 2118 "y.tab.c"
    break;

  case 75:
#line 288 "parser.y"
                    {yyval = keynode(T_MINUS);}
#line 2124 "y.tab.c"
    break;

  case 76:
#line 290 "parser.y"
                                        {yyval = nontermnode(N_MATH_EXPR); yyval->child = yyvsp[-2]; yyvsp[-2]->brother = yyvsp[0];
                                          yyval->op_code = yyvsp[-1]->type;
                                        }
#line 2132 "y.tab.c"
    break;

  case 77:
#line 293 "parser.y"
                  {yyval = yyvsp[0];}
#line 2138 "y.tab.c"
    break;

  case 78:
#line 295 "parser.y"
                   {yyval = keynode(T_MUL);}
#line 2144 "y.tab.c"
    break;

  case 79:
#line 296 "parser.y"
                   {yyval = keynode(T_DIV);}
#line 2150 "y.tab.c"
    break;

  case 80:
#line 299 "parser.y"
                         {yyval = nontermnode(N_NEG_EXPR); yyval->child = yyvsp[0];
                          yyval->op_code = yyvsp[-1]->type;
                          }
#line 2158 "y.tab.c"
    break;

  case 81:
#line 303 "parser.y"
                      {yyval = yyvsp[-1];}
#line 2164 "y.tab.c"
    break;

  case 82:
#line 304 "parser.y"
            {yyval = idnode();}
#line 2170 "y.tab.c"
    break;

  case 83:
#line 305 "parser.y"
               {yyval = yyvsp[0];}
#line 2176 "y.tab.c"
    break;

  case 84:
#line 306 "parser.y"
                   {yyval = yyvsp[0];}
#line 2182 "y.tab.c"
    break;

  case 85:
#line 307 "parser.y"
                   {yyval = yyvsp[0];}
#line 2188 "y.tab.c"
    break;

  case 86:
#line 308 "parser.y"
                           {yyval = nontermnode(N_CASTING); yyval->child = yyvsp[-1];
                            yyval->op_code = yyvsp[-3]->type;
                           }
#line 2196 "y.tab.c"
    break;

  case 87:
#line 312 "parser.y"
                 {yyval = keynode(T_MINUS);}
#line 2202 "y.tab.c"
    break;

  case 88:
#line 313 "parser.y"
               {yyval = keynode(T_NOT);}
#line 2208 "y.tab.c"
    break;

  case 89:
#line 315 "parser.y"
                 {yyval = intconstnode();}
#line 2214 "y.tab.c"
    break;

  case 90:
#line 316 "parser.y"
                  {yyval = realconstnode();}
#line 2220 "y.tab.c"
    break;

  case 91:
#line 317 "parser.y"
                 {yyval = strconstnode();}
#line 2226 "y.tab.c"
    break;

  case 92:
#line 318 "parser.y"
                  {yyval = boolconstnode();}
#line 2232 "y.tab.c"
    break;

  case 93:
#line 320 "parser.y"
               {yyval = idnode();}
#line 2238 "y.tab.c"
    break;

  case 94:
#line 320 "parser.y"
                                                      {yyval = nontermnode(N_FUNC_CALL); yyval->child = yyvsp[-3]; yyvsp[-3]->brother = yyvsp[-1];}
#line 2244 "y.tab.c"
    break;

  case 95:
#line 322 "parser.y"
                          {yyval = nontermnode(N_EXPR_LIST); yyval->child = yyvsp[0];}
#line 2250 "y.tab.c"
    break;

  case 96:
#line 323 "parser.y"
                {yyval = NULL;}
#line 2256 "y.tab.c"
    break;

  case 97:
#line 325 "parser.y"
                                            {yyval = nontermnode(N_COND_EXPR); yyval->child = yyvsp[-5]; yyvsp[-5]->brother = yyvsp[-3]; yyvsp[-3]->brother = yyvsp[-1];}
#line 2262 "y.tab.c"
    break;

  case 98:
#line 327 "parser.y"
               {yyval = keynode(T_INTEGER);}
#line 2268 "y.tab.c"
    break;

  case 99:
#line 328 "parser.y"
            {yyval = keynode(T_REAL);}
#line 2274 "y.tab.c"
    break;


#line 2278 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 331 "parser.y"


Pnode nontermnode(Nonterminal nonterm)
{
    Pnode p = newnode(T_NONTERMINAL);
    p->value.ival = nonterm;
    return(p);
}

Pnode idnode()
{
    Pnode p = newnode(T_ID);
    p->value.sval = lexval.sval;
    return(p);
}

Pnode keynode(Typenode keyword)
{
    return(newnode(keyword));
}

Pnode intconstnode()
{
    Pnode p = newnode(T_INTCONST);
    p->value.ival = lexval.ival;
    p->sem_type = S_INTEGER;
    return(p);
}

Pnode realconstnode()
{
    Pnode p = newnode(T_REALCONST);
    p->value.fval = lexval.fval;
    p->sem_type = S_REAL;
    return(p);
}

Pnode strconstnode()
{
    Pnode p = newnode(T_STRCONST);
    p->value.sval = lexval.sval;
    p->sem_type = S_STRING;
    return(p);
}

Pnode boolconstnode()
{
  Pnode p = newnode(T_BOOLCONST);
  p->value.bval = lexval.bval;
  p->sem_type = S_BOOLEAN_;
  return(p);
}

Pnode newnode(Typenode tnode)
{
  Pnode p = malloc(sizeof(Node));
  p->type = tnode;
  p->is_gen = 0;
  p->child = p->brother = NULL;
  return(p);
}

int main(int argc, char **argv)
{
  symbol_table = init_symbol_table(SYMTAB_SIZE);
  temp_env = init_symbol_table(SYMTAB_SIZE);
  temp_descr = (struct bucket **)malloc(25 * sizeof(struct bucket *));
  current_env = symbol_table; 
  id_func = (char *)malloc(140);
  current_oid = &oid_g;
  sub_prog10 = (struct SCode *)malloc(sizeof(struct SCode));
  tot_prog = (struct SCode *)malloc(sizeof(struct SCode));
  current_prog = (struct SCode *)malloc(sizeof(struct SCode));
  int result;

  for (int i = 0; i < SYMTAB_SIZE; i++)
  {
    lista_id[i] = (char * )malloc(140);
  }

  if (argc >= 2) {
    if ((yyin = fopen(argv[1], "r")) == NULL){
       fprintf(stderr,"ERRORE SIMPLAC: FILE NON ESISTE!");
       // Program exits if the file pointer returns NULL.
       exit(-1);
   }
  }
  else {
      fprintf(stderr,"ERRORE SIMPLAC: INDICARE FILE DA COMPILARE");
       // Program exits if the file pointer returns NULL.
       exit(-1);
  }
    

  if ((result = yyparse()) == 0) {
    //Togliere commento sulla funzione treeprint per visualizzare l'albero sintattico astratto a video
    //treeprint(root, 0);

    //print_symbol_table(symbol_table);
    
    analizza(root, symbol_table);
    
    *sub_prog10 = endcode();
    generateCode(root, symbol_table, sub_prog10);
    int size;
    size = sub_prog10->num;

    *tot_prog = appcode(makecode1(SIZ,size), make_psh_pop(0, count_var(symbol_table), get_func_entry_point(sub_prog10,"smain")));
    *tot_prog = appcode(*tot_prog, makecode(STP));
    *tot_prog = appcode(*tot_prog,*sub_prog10);

    printf("---- Correct Code: -----\n");
    codeprint(tot_prog);

    char *s_filename = strcat(argv[1],".sim");
    save_to_file(tot_prog, s_filename);

    //Togliere commento sulla funzione codeprint per visualizzare il codice intermedio SCode a video

    printf("---- Test Code: -----\n");
    get_scode_from_file(s_filename);

    //executeSCode(*tot_prog);
  }
  
  return(result);
}

void yyerror(int argc)
{
  fprintf(stderr, "Line %d: syntax error on symbol \"%s\"\n",
          line, yytext);
  exit(-1);
}
