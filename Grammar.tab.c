/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "Grammar.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include "vector.h"
#include "tree.h"
#include <getopt.h>
int yylex();
int yyerror();
int yydebug = 1;
int yylineno;
extern FILE* yyin;

typedef struct stmt
{
   int stmt_statment;
   c_vector* vector_stmt;
}stmt;

typedef struct Global
{
    int mode;
    char* field_name;
}Global;

enum
{
    ALL_MODE,
    GET_MODE
};

typedef struct select_info
{
    char name[30];
    c_vector* vector_field;     //field_info
    c_vector* vector_opt;      //Node*
    c_vector* vector_table;
    c_vector* vector_where;
    c_vector* vector_group_by;
    c_vector* vector_having;
    c_vector* vector_oder_by;
}select_info;


typedef struct obj_info
{
    int type;               //用来标记是否为子查询
    Tree_Node* obj_name;         //记录字段的名字
    Tree_Node* obj_alias;        //记录字段的别名
    Tree_Node* obj_condition;    //记录改字段的条件
    c_vector* obj_field;    //指向同一个SELECT下面可能对应的字段信息
    Tree_Node* select_select; //记录为子查询的节点
}obj_info;

typedef struct field_info
{
    int type;
    Tree_Node* field_name;
    Tree_Node* field_alias;
    c_vector* field_table;
    Tree_Node* select_select;
}field_info;

//全局变量的声明
int count;
stmt _stmt;
Global _Global;
int parse_getopt(int argc,char** argv);
void Init_stmt_vector();
void Init_select_info_vector(select_info* select_con);
void Del_stmt_vector();
void Del_select_info_vector();
void Main_struct(Tree_Node* enum_man,char* name);

void Get_select_info(Tree_Node* enum_man,select_info* select_con);
void Get_opt_info(Tree_Node* enum_man,select_info* select_con);
void Get_field_info(Tree_Node* enum_man,select_info* select_con);
void Get_field_info_child(Tree_Node* enum_man,select_info* select_con);
void Get_table_info(Tree_Node* enum_man,select_info* select_con);
void Get_table_info_child(Tree_Node* enum_man,select_info* select_con);
void Normal_get_info(Tree_Node* enum_man,select_info* select_con);
void Join_get_info(Tree_Node* enum_man,select_info* select_con);
void Enum_get_opt_where_condition(Tree_Node* enum_man,select_info* select_con);
void Enum_get_group_by(Tree_Node* enum_man,select_info* select_con);
void Enum_get_having(Tree_Node* enum_man,select_info* select_con);
void Enum_get_oder_by(Tree_Node* enum_man,select_info* select_con);
void Show_stmt_info();
void Show_the_filed_info(char* filed);

#line 155 "Grammar.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "Grammar.tab.h".  */
#ifndef YY_YY_GRAMMAR_TAB_H_INCLUDED
# define YY_YY_GRAMMAR_TAB_H_INCLUDED
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
    EQ = 258,
    AND = 259,
    OR = 260,
    IN = 261,
    NOT = 262,
    LIKE = 263,
    ALL = 264,
    DISTINCT = 265,
    DISTINCTROW = 266,
    STRAIGHT_JOIN = 267,
    SQL_NO_CHACHE = 268,
    SQL_CALC_FOUND_ROWS = 269,
    SQL_SMALL_RESULT = 270,
    SQL_BIG_RESULT = 271,
    SQL_BUFFER_RESULT = 272,
    SYSTEM_CALL_VARIABLE = 273,
    USER_CALL_VARIABLE = 274,
    SELECT = 275,
    HIGH_PRIORITY = 276,
    FROM = 277,
    PARTITION = 278,
    WHERE = 279,
    GROUP = 280,
    BY = 281,
    HAVING = 282,
    WINDOW = 283,
    ORDER = 284,
    LIMIT = 285,
    FOR = 286,
    JOIN = 287,
    INNER = 288,
    CROSS = 289,
    ON = 290,
    USING = 291,
    LEFT = 292,
    RIGHT = 293,
    OUTER = 294,
    NATURAL = 295,
    EXISTS = 296,
    UNION = 297,
    INSERT_OBJ = 298,
    INSERT = 299,
    UPDATE = 300,
    CREATE = 301,
    ID = 302,
    SET = 303,
    EOL = 304,
    LF_bracket = 305,
    RF_bracket = 306,
    VALUES = 307,
    COMMA = 308,
    DATABASE = 309,
    AS = 310,
    NAME = 311,
    ASC = 312,
    DESC = 313,
    INTO = 314,
    NUM = 315,
    WITH = 316,
    ROLLUP = 317,
    CONCAT = 318,
    CASE = 319,
    THEN = 320,
    WHEN = 321,
    END = 322,
    ELSE = 323,
    FLOOR = 324
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 91 "Grammar.y" /* yacc.c:355  */

    struct Tree_Node* node;
    char* strval;

#line 270 "Grammar.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 287 "Grammar.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   357

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  239

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      77,    78,     9,    12,    76,    10,    13,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    75,
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
       5,     6,     7,     8,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   143,   152,   155,   156,   157,   158,   179,
     185,   193,   203,   218,   269,   273,   276,   284,   292,   300,
     308,   316,   324,   332,   340,   353,   359,   367,   376,   390,
     395,   401,   409,   415,   428,   439,   454,   460,   478,   485,
     499,   508,   519,   527,   533,   546,   557,   569,   577,   588,
     602,   614,   620,   627,   632,   636,   643,   646,   653,   656,
     660,   667,   670,   678,   687,   697,   703,   706,   715,   732,
     750,   768,   784,   800,   816,   833,   844,   855,   871,   887,
     896,   902,   907,   914,   919,   925,   934,   944,   954,   962,
     966,   973,   987,   993,  1010,  1019,  1022,  1043,  1057,  1078,
    1081,  1085,  1092,  1095,  1102,  1105,  1114,  1117,  1126,  1129,
    1136,  1146,  1149,  1157,  1162,  1171,  1173,  1176,  1177,  1180,
    1181,  1184,  1185,  1188,  1189,  1192,  1193
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQ", "AND", "OR", "IN", "NOT", "LIKE",
  "'*'", "'-'", "'/'", "'+'", "'.'", "ALL", "DISTINCT", "DISTINCTROW",
  "STRAIGHT_JOIN", "SQL_NO_CHACHE", "SQL_CALC_FOUND_ROWS",
  "SQL_SMALL_RESULT", "SQL_BIG_RESULT", "SQL_BUFFER_RESULT",
  "SYSTEM_CALL_VARIABLE", "USER_CALL_VARIABLE", "SELECT", "HIGH_PRIORITY",
  "FROM", "PARTITION", "WHERE", "GROUP", "BY", "HAVING", "WINDOW", "ORDER",
  "LIMIT", "FOR", "JOIN", "INNER", "CROSS", "ON", "USING", "LEFT", "RIGHT",
  "OUTER", "NATURAL", "EXISTS", "UNION", "INSERT_OBJ", "INSERT", "UPDATE",
  "CREATE", "ID", "SET", "EOL", "LF_bracket", "RF_bracket", "VALUES",
  "COMMA", "DATABASE", "AS", "NAME", "ASC", "DESC", "INTO", "NUM", "WITH",
  "ROLLUP", "CONCAT", "CASE", "THEN", "WHEN", "END", "ELSE", "FLOOR",
  "';'", "','", "'('", "')'", "$accept", "SQLS", "SQL", "select_exp",
  "select_expr_stmt", "end", "select_opts", "select_expr_list",
  "select_expr", "opt_as_alias", "case_when_fun", "when_then",
  "table_references", "table_reference", "table_factor", "table_subquery",
  "join_table", "opt_left_or_right", "left_or_right", "opt_outer",
  "opt_inner_cross", "opt_join_condition", "join_condition", "index_hint",
  "opt_where", "where_condition", "val_list", "opt_group_by",
  "groupby_list", "opt_asc_desc", "opt_with_rollup", "opt_having",
  "opt_order_by", "opt_limit", "opt_into_list", "column_list",
  "create_exp", "update_exp", "insert_exp", "key_value_exp",
  "id_comma_exp", "value_key_exp", "id2_comma_exp", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,    42,
      45,    47,    43,    46,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,    59,    44,    40,    41
};
# endif

#define YYPACT_NINF -166

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-166)))

#define YYTABLE_NINF -89

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     131,  -166,   -35,   -17,   -20,   149,   -30,    18,  -166,  -166,
    -166,  -166,   107,    17,    19,    23,  -166,    42,  -166,    95,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,  -166,    73,    -9,  -166,    37,   114,   -25,  -166,   285,
      88,    82,  -166,  -166,   129,  -166,   129,    -2,    90,   252,
     252,   130,  -166,   -38,    22,    71,   252,  -166,   252,   252,
     252,    85,   155,   104,   252,   252,   252,   252,   105,  -166,
    -166,   117,   122,   186,  -166,   -28,  -166,  -166,  -166,   327,
     161,   204,   327,  -166,  -166,  -166,  -166,    10,   238,   -15,
     263,  -166,   -43,  -166,  -166,   176,   176,   176,    -3,   101,
     134,  -166,  -166,  -166,  -166,  -166,  -166,   132,   136,   144,
     153,   168,  -166,   252,  -166,   252,   160,  -166,   180,   238,
      -5,   175,    74,   252,    71,   196,    71,  -166,  -166,  -166,
    -166,    98,   194,   205,  -166,    40,   188,    -3,  -166,  -166,
     190,   185,   197,   192,   202,   230,   327,   327,   -43,  -166,
      -1,    55,    86,  -166,  -166,   -43,   327,   263,   229,   233,
     232,   194,   194,   236,  -166,   240,    71,  -166,  -166,    57,
     193,   215,  -166,  -166,  -166,   220,   227,  -166,   207,   344,
     207,  -166,   252,   252,   247,   252,  -166,  -166,    71,    71,
     106,  -166,  -166,   153,  -166,   279,  -166,  -166,   224,    39,
     327,   273,   274,   327,  -166,   106,   252,  -166,  -166,  -166,
     254,   259,  -166,  -166,  -166,   245,   252,  -166,   252,   249,
     255,  -166,   327,  -166,  -166,  -166,   224,   242,   244,   261,
    -166,  -166,   251,  -166,   248,  -166,  -166,   262,  -166
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    15,     0,     0,     0,     4,     0,     8,     9,     7,
       6,     5,     0,     0,     0,     0,     1,     0,     2,     0,
      27,    16,    17,    18,    19,    23,    24,    20,    21,    22,
      89,    90,     0,    81,    83,     0,     0,    14,    25,    31,
       0,     0,   115,     3,     0,    10,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,     0,    12,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    30,
      28,     0,     0,     0,    11,     0,    82,    84,    94,    92,
       0,     0,    35,    85,    33,    88,    79,    31,     0,    66,
      36,    38,    31,    39,    26,    68,    69,    70,     0,     0,
       0,    86,    73,    71,    74,    72,    29,   119,     0,     0,
       0,     0,    80,     0,    91,     0,     0,    65,    81,     0,
       0,     0,     0,     0,     0,    95,     0,    59,    60,    54,
      55,    53,    56,     0,    42,     0,     0,     0,    87,   121,
       0,   120,   123,     0,     0,     0,    93,    34,    31,    40,
       0,     0,     0,    45,    43,    31,    67,    37,     0,   104,
      47,    56,    56,     0,    57,     0,     0,    75,    77,     0,
       0,     0,   122,   125,   118,   124,     0,    65,    84,    45,
      79,    65,     0,     0,   106,     0,    51,    52,     0,     0,
      61,    76,    78,     0,   126,     0,    41,    44,    99,   102,
     105,     0,   108,    48,    50,     0,     0,    64,    46,    62,
       0,     0,   100,   101,    97,     0,     0,    96,     0,     0,
     111,    49,    63,   117,   116,   103,    99,   107,   109,     0,
      14,    98,     0,   113,   112,    13,   110,     0,   114
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -166,  -166,   320,   -31,    -8,    96,  -166,  -166,   271,   -36,
    -166,   277,   286,   216,  -125,  -166,  -166,  -166,  -166,    -4,
    -166,  -166,   137,  -165,  -166,   -12,   -88,  -166,   125,   118,
    -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,  -166,
    -166,   164,  -166
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    57,    12,    37,    38,   117,
      51,    52,   121,    90,    91,    92,    93,   163,   132,   165,
     133,   208,   209,   149,   125,    79,    80,   159,   199,   214,
     217,   184,   202,   220,   230,   234,     9,    10,    11,   108,
     109,   143,   144
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   160,    55,    70,    47,    53,    78,    76,    76,    19,
     136,    45,   196,    13,   123,    75,   197,    68,    69,    19,
      30,    31,     1,   116,    54,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    14,    74,    81,    82,    15,
      85,   190,    19,    32,    39,    18,    95,    96,    97,   170,
     112,    56,   102,   103,   104,   105,   134,   120,    33,    77,
     178,   124,    34,   204,   205,    19,    35,   135,    48,    40,
      68,    69,    41,   153,    36,    42,   122,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    19,   151,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    78,
      86,   146,    19,   147,    19,   215,   169,   152,    49,    44,
      50,   156,   177,    30,    31,   216,    20,    43,   167,   181,
       1,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    87,   179,    73,   191,    32,    30,    31,     1,
     161,   162,   177,    71,   181,    72,   206,   207,    88,    16,
      46,    33,   155,    32,     1,    34,     1,   186,   187,    35,
      32,    99,    98,   100,   180,   101,   106,    36,    33,   107,
     198,   200,    34,   203,     1,    33,    35,   110,   137,    34,
       2,     3,     4,    35,    36,    64,    65,    66,    67,   111,
     139,    36,   140,   150,   222,   138,   141,   -31,     2,     3,
       4,    49,    83,    50,   226,   142,   198,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   -31,   -31,   -31,
     145,   148,   -31,   -31,   -31,   -31,   158,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   113,   164,   114,
      68,    69,   166,   172,   -31,   -31,   -31,   171,   174,   -31,
     -31,   124,   -31,   154,   175,   173,   -31,    48,   -31,   176,
     182,    30,    31,     1,   113,   183,   168,    68,    69,   113,
     193,   192,   185,   188,   115,    30,    31,   189,   194,   195,
     126,   201,   211,   -31,    32,   -31,   212,   213,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    32,   118,
     -58,   127,   128,    34,   218,   129,   130,    35,   131,   219,
     223,   224,   225,    33,   228,   119,   236,    34,   216,   229,
     232,    35,   233,   238,   237,    17,   235,    94,    84,    36,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
     157,    89,   221,   227,   231,    68,    69,   -88,   -88,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,   -88,   210
};

static const yytype_uint8 yycheck[] =
{
      12,   126,    27,    39,    13,    36,     9,     9,     9,    47,
      98,    19,   177,    48,    29,    46,   181,    60,    61,    47,
      23,    24,    25,    13,    36,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    52,    44,    49,    50,    59,
      78,   166,    47,    46,    56,    75,    58,    59,    60,   137,
      78,    76,    64,    65,    66,    67,    92,    88,    61,    61,
      61,    76,    65,   188,   189,    47,    69,    98,    77,    52,
      60,    61,    53,    78,    77,    52,    88,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    47,   119,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,     9,
      78,   113,    47,   115,    47,    66,   137,   119,    71,    14,
      73,   123,   148,    23,    24,    76,     9,    75,    78,   155,
      25,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    61,    78,    52,    78,    46,    23,    24,    25,
      42,    43,   178,    55,   180,    57,    40,    41,    77,     0,
      77,    61,    78,    46,    25,    65,    25,   161,   162,    69,
      46,     6,    77,     8,    78,    61,    61,    77,    61,    52,
     182,   183,    65,   185,    25,    61,    69,    55,    77,    65,
      49,    50,    51,    69,    77,     9,    10,    11,    12,     3,
      58,    77,    56,    13,   206,    61,    52,    17,    49,    50,
      51,    71,    72,    73,   216,    52,   218,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    37,    38,    39,
      52,    61,    42,    43,    17,    45,    30,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    76,    44,    78,
      60,    61,    37,    58,    37,    38,    39,    57,    56,    42,
      43,    76,    45,    78,    52,    58,    76,    77,    78,    29,
      31,    23,    24,    25,    76,    32,    78,    60,    61,    76,
      55,    78,    40,    37,    70,    23,    24,    37,    58,    52,
      17,    34,     3,    76,    46,    78,    62,    63,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    46,    61,
      37,    38,    39,    65,    31,    42,    43,    69,    45,    35,
      56,    52,    67,    61,    65,    77,    65,    65,    76,    64,
      76,    69,    61,    61,    76,     5,   230,    56,    51,    77,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
     124,    55,   205,   218,   226,    60,    61,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,   193
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    49,    50,    51,    80,    81,    82,    83,   115,
     116,   117,    85,    48,    52,    59,     0,    81,    75,    47,
       9,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    46,    61,    65,    69,    77,    86,    87,   104,
      52,    53,    52,    75,    14,    83,    77,    13,    77,    71,
      73,    89,    90,    82,   104,    27,    76,    84,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    60,    61,
      88,    55,    57,    52,    83,    82,     9,    61,     9,   104,
     105,   104,   104,    72,    90,    78,    78,    61,    77,    91,
      92,    93,    94,    95,    87,   104,   104,   104,    77,     6,
       8,    61,   104,   104,   104,   104,    61,    52,   118,   119,
      55,     3,    78,    76,    78,    70,    13,    88,    61,    77,
      82,    91,   104,    29,    76,   103,    17,    38,    39,    42,
      43,    45,    97,    99,    88,    82,   105,    77,    61,    58,
      56,    52,    52,   120,   121,    52,   104,   104,    61,   102,
      13,    82,   104,    78,    78,    78,   104,    92,    30,   106,
      93,    42,    43,    96,    44,    98,    37,    78,    78,    82,
     105,    57,    58,    58,    56,    52,    29,    88,    61,    78,
      78,    88,    31,    32,   110,    40,    98,    98,    37,    37,
      93,    78,    78,    55,    58,    52,   102,   102,   104,   107,
     104,    34,   111,   104,    93,    93,    40,    41,   100,   101,
     120,     3,    62,    63,   108,    66,    76,   109,    31,    35,
     112,   101,   104,    56,    52,    67,   104,   107,    65,    64,
     113,   108,    76,    61,   114,    84,    65,    76,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    79,    80,    80,    81,    81,    81,    81,    81,    82,
      82,    82,    83,    83,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    86,    86,    86,    87,    88,
      88,    88,    89,    89,    90,    90,    91,    91,    92,    92,
      93,    93,    93,    93,    93,    94,    95,    95,    95,    95,
      95,    96,    96,    96,    97,    97,    98,    98,    99,    99,
      99,   100,   100,   101,   101,   102,   103,   103,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   105,   105,   105,   106,   106,   107,   107,   108,
     108,   108,   109,   109,   110,   110,   111,   111,   112,   112,
     112,   113,   113,   114,   114,   115,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     0,     1,     1,     1,     1,     1,
       3,     4,     4,    12,     0,     0,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     1,     3,     1,     2,     2,
       1,     0,     1,     2,     4,     2,     1,     3,     1,     1,
       3,     5,     2,     3,     5,     3,     5,     3,     5,     6,
       5,     2,     2,     0,     1,     1,     0,     1,     0,     1,
       1,     0,     1,     2,     1,     0,     0,     2,     3,     3,
       3,     3,     3,     3,     3,     5,     6,     5,     6,     3,
       4,     1,     3,     1,     3,     3,     3,     4,     3,     1,
       1,     4,     1,     3,     1,     0,     4,     2,     4,     0,
       1,     1,     0,     2,     0,     2,     0,     3,     0,     2,
       4,     0,     2,     1,     3,     3,    10,    10,     7,     1,
       2,     2,     3,     1,     2,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 139 "Grammar.y" /* yacc.c:1646  */
    {
        // Delete_tree($1);
        // Del_select_info_vector();
    }
#line 1572 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 144 "Grammar.y" /* yacc.c:1646  */
    {
        // Delete_tree($2);
        // Del_select_info_vector();
        // printf("归约成功!\n");
    }
#line 1582 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 152 "Grammar.y" /* yacc.c:1646  */
    {
          (yyval.node) = Create_new_node(0,"SELECT T 语句");
   }
#line 1590 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 155 "Grammar.y" /* yacc.c:1646  */
    {printf("\tstat : insert\n");}
#line 1596 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 156 "Grammar.y" /* yacc.c:1646  */
    {printf("\tstat : update\n");}
#line 1602 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 157 "Grammar.y" /* yacc.c:1646  */
    {printf("\tstat : create\n");}
#line 1608 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 159 "Grammar.y" /* yacc.c:1646  */
    {
                    Main_struct((yyvsp[0].node),"MAIN");

                    if(_Global.mode == GET_MODE)
                    {
                        Show_the_filed_info(_Global.field_name);
                    }
                    else if(_Global.mode == ALL_MODE)
                    {
                        Show_stmt_info();
                    }
                   
                    Delete_tree((yyvsp[0].node));
                    Del_select_info_vector();
                    Del_stmt_vector();
                    Init_stmt_vector();
                    printf("|-----------------------------------------------------------------|\n");
                }
#line 1631 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 180 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"\nBEGIN");
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node); 
          }
#line 1641 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 186 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"BEGIN 语句 union");
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node); 
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
          }
#line 1653 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 194 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"BEGIN 语句 union");
                (yyval.node)->L_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyval.node); 
                (yyvsp[-3].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-3].node);
          }
#line 1665 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 204 "Grammar.y" /* yacc.c:1646  */
    {
                    char con[500];
                    sprintf(con,"SELECT %s %s",
                        (yyvsp[-2].node)->RHS,
                        (yyvsp[-1].node)->RHS     
                        );
                    (yyval.node) = Create_new_node(0,con);
                    (yyvsp[0].node)->R_child = (yyvsp[-2].node);
                    (yyvsp[-2].node)->Parent = (yyvsp[0].node);
                    (yyvsp[-2].node)->R_child = (yyvsp[-1].node);
                    (yyvsp[-1].node)->Parent = (yyvsp[-2].node);
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                }
#line 1684 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 219 "Grammar.y" /* yacc.c:1646  */
    {
                char con[500];
                sprintf(con,"SELECT %s %s FROM %s %s %s %s %s %s %s",
                    (yyvsp[-10].node)->RHS,
                    (yyvsp[-9].node)->RHS,
                    (yyvsp[-7].node)->RHS,
                    (yyvsp[-6].node)->RHS,
                    (yyvsp[-5].node)->RHS,
                    (yyvsp[-4].node)->RHS,
                    (yyvsp[-3].node)->RHS,
                    (yyvsp[-2].node)->RHS,
                    (yyvsp[-1].node)->RHS
                    );
                (yyval.node) = Create_new_node(0,con);
                (yyvsp[0].node)->R_child = (yyvsp[-10].node);
                (yyvsp[-10].node)->Parent = (yyvsp[0].node);

                (yyvsp[-10].node)->R_child = (yyvsp[-9].node);
                (yyvsp[-9].node)->Parent = (yyvsp[-10].node);
                (yyvsp[-9].node)->R_child = (yyvsp[-7].node); 
                (yyvsp[-7].node)->Parent = (yyvsp[-9].node);

                (yyvsp[-7].node)->R_child = (yyvsp[-6].node); 
                (yyvsp[-6].node)->Parent = (yyvsp[-7].node);

                (yyvsp[-6].node)->R_child = (yyvsp[-5].node); 
                (yyvsp[-5].node)->Parent = (yyvsp[-6].node);

                (yyvsp[-5].node)->R_child = (yyvsp[-4].node); 
                (yyvsp[-4].node)->Parent = (yyvsp[-5].node);

                (yyvsp[-4].node)->R_child = (yyvsp[-3].node); 
                (yyvsp[-3].node)->Parent = (yyvsp[-4].node);

                (yyvsp[-3].node)->R_child = (yyvsp[-2].node); 
                ((yyvsp[-2].node))->Parent = (yyvsp[-3].node);

                (yyvsp[-2].node)->R_child = (yyvsp[-1].node); 
                (yyvsp[-1].node)->Parent = (yyvsp[-2].node);

                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
          }
#line 1732 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 269 "Grammar.y" /* yacc.c:1646  */
    {
       (yyval.node) = Create_new_node(END,"SELECT BEGIN : ");
   }
#line 1740 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 273 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
              }
#line 1748 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 277 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1760 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 285 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1772 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 293 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1784 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 301 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1796 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 309 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1808 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 317 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt3");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1820 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 325 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1832 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 333 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1844 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 341 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1856 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 354 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(FIELD_INFO_BEGIN,"field_info_begin");
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                }
#line 1866 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 360 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(FIELD_INFO_BEGIN,"field_info_begin");
                    (yyval.node)->L_child = (yyvsp[-2].node);
                    (yyvsp[-2].node)->Parent = (yyval.node);
                    (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                }
#line 1878 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 368 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(FIELD_NAME,"*");
                }
#line 1886 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 377 "Grammar.y" /* yacc.c:1646  */
    {
              (yyval.node) = Create_new_node(FIELD_NODE,"field");
              (yyval.node)->L_child = (yyvsp[-1].node);
              (yyvsp[-1].node)->Parent = (yyval.node);
              (yyvsp[-1].node)->R_child = (yyvsp[0].node);
              (yyvsp[0].node)->Parent = (yyvsp[-1].node);
           }
#line 1898 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 391 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ALIAS_NAME,(yyvsp[0].strval)); 
                free((yyvsp[0].strval));
            }
#line 1907 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 396 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ALIAS_NAME,(yyvsp[0].strval)); 
                free((yyvsp[0].strval));
            }
#line 1916 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 401 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ALIAS_NAME,"NULL"); 
            }
#line 1924 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 410 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(2,(yyvsp[0].node)->RHS); 
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
             }
#line 1934 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 416 "Grammar.y" /* yacc.c:1646  */
    {
                char* con=(char*)malloc(strlen((yyvsp[-1].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                sprintf(con,"%s %s",(yyvsp[-1].node)->RHS,(yyvsp[0].node)->RHS);
                (yyval.node) = Create_new_node(2,con); 
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
                free(con);
             }
#line 1949 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 429 "Grammar.y" /* yacc.c:1646  */
    {
                char* con=(char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+20);
                sprintf(con,"WHEN　%s THEN %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);
                (yyval.node) = Create_new_node(2,con); 
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                free(con);
         }
#line 1964 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 440 "Grammar.y" /* yacc.c:1646  */
    {
                char* con=(char*)malloc(strlen((yyvsp[0].node)->RHS)+10);
                sprintf(con,"ELSE %s",(yyvsp[0].node)->RHS);
                (yyval.node) = Create_new_node(2,con); 
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
                free(con);
         }
#line 1977 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 455 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(TABLE_INFO,"表信息");
                   (yyval.node)->L_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyval.node);
                }
#line 1987 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 461 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(TABLE_INFO,"表信息");
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                }
#line 1999 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 478 "Grammar.y" /* yacc.c:1646  */
    {
                                (yyval.node) = Create_new_node(NORMAL_TABLE,"Normal table");
                                (yyval.node)->L_child = (yyvsp[0].node);
                                (yyvsp[0].node)->Parent = (yyval.node);
                              //  Enum_tree_node_deep($$);
                              //  printf("%s  %d\n",$$->RHS,$$->type);
                              }
#line 2011 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 486 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(JOIN_TABLE,"JOIN表");
                   (yyval.node)->L_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyval.node);
               }
#line 2021 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 499 "Grammar.y" /* yacc.c:1646  */
    { 
                                             (yyval.node) = Create_new_node(TABLE_NAME,(yyvsp[-2].strval));
                                             free((yyvsp[-2].strval));
                                             (yyval.node)->L_child = (yyvsp[-1].node);
                                             (yyvsp[-1].node)->Parent = (yyval.node);
                                             (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                                             (yyvsp[0].node)->Parent = (yyvsp[-1].node);
                                        //   printf("%s  %d\n",$$->RHS,$$->type);
                                            }
#line 2035 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 509 "Grammar.y" /* yacc.c:1646  */
    {
                char con[200];
                sprintf(con,"%s.%s",(yyvsp[-4].strval),(yyvsp[-2].strval));
                free((yyvsp[-4].strval)); free((yyvsp[-2].strval));
                (yyval.node) = Create_new_node(TABLE_NAME,con);
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
            }
#line 2050 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 520 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(TABLE_SUB,"table_sub");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
            }
#line 2062 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 528 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(TABLE_REFERENCE,"为(table_references)");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
            }
#line 2072 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 534 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(TABLE_REFERENCE,"为(table_references)");
                (yyval.node)->L_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyval.node);
                (yyvsp[-3].node)->R_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyvsp[-3].node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
            }
#line 2086 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 547 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_SELECT,"(子查询");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
              }
#line 2096 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 558 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_1,(yyvsp[0].node)->RHS);
                (yyval.node)->L_child = (yyvsp[-4].node);
                (yyvsp[-4].node)->Parent = (yyval.node);
                (yyvsp[-4].node)->R_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyvsp[-4].node);
                (yyvsp[-3].node)->R_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyvsp[-3].node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 2112 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 570 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_2,"Join表的选项 JION2");
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
          }
#line 2124 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 578 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_3,"Join表的选项 STRIGHT_JOIN ON3");
                (yyval.node)->L_child = (yyvsp[-4].node);
                (yyvsp[-4].node)->Parent = (yyval.node);
                (yyvsp[-4].node)->R_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyvsp[-4].node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);

          }
#line 2139 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 589 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_4,(yyvsp[0].node)->RHS);
                (yyval.node)->L_child = (yyvsp[-5].node);
                (yyvsp[-5].node)->Parent = (yyval.node);
                (yyvsp[-5].node)->R_child = (yyvsp[-4].node);
                (yyvsp[-4].node)->Parent = (yyvsp[-5].node);
                (yyvsp[-4].node)->R_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyvsp[-4].node);
                (yyvsp[-3].node)->R_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyvsp[-3].node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 2157 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 603 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_5,"Join表的选项 NATURAL5");
                (yyval.node)->L_child = (yyvsp[-4].node);
                (yyvsp[-4].node)->Parent = (yyval.node);
                (yyvsp[-4].node)->R_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyvsp[-4].node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
          }
#line 2171 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 615 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(LEFT,"LEFT");
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                 }
#line 2181 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 621 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(RIGHT,"RIGHT");
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                 }
#line 2191 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 627 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(RIGHT,"NULL");
                 }
#line 2199 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 633 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(LEFT,"LEFT");
             }
#line 2207 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 637 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(RIGHT,"RIGHT");
             }
#line 2215 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 643 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"NULL");
         }
#line 2223 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 647 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"OUTER");
         }
#line 2231 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 653 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(1,"NULL");
               }
#line 2239 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 657 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(1,"INNER");
               }
#line 2247 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 661 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(1,"CROSS");
               }
#line 2255 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 667 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(1,"NULL");
                  }
#line 2263 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 671 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(JOIN_CONDITION,(yyvsp[0].node)->RHS);
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                  }
#line 2273 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 679 "Grammar.y" /* yacc.c:1646  */
    {
                  char* con = (char*)malloc(strlen((yyvsp[0].node)->RHS)+1);
                  sprintf(con,"ON %s",(yyvsp[0].node)->RHS);
                  (yyval.node) = Create_new_node(JOIN_CONDITION,con);
                  (yyval.node)->L_child = (yyvsp[0].node);
                  (yyvsp[0].node)->Parent = (yyval.node);
                  free(con);
              }
#line 2286 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 688 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(JOIN_CONDITION,"USING");
              }
#line 2294 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 697 "Grammar.y" /* yacc.c:1646  */
    {
              (yyval.node) = Create_new_node(1,"index NULL");
          }
#line 2302 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 703 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"NO WHERE");
         }
#line 2310 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 707 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(OPT_WHERE,(yyvsp[0].node)->RHS);
            (yyval.node)->L_child = (yyvsp[0].node);
            (yyvsp[0].node)->Parent = (yyval.node);
         }
#line 2320 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 716 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[-1].strval))+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s %s %s",(yyvsp[-2].node)->RHS,(yyvsp[-1].strval),(yyvsp[0].node)->RHS);

                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2341 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 733 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s AND %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);

                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }

                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2363 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 751 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s OR %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);

                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }

                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2385 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 769 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s - %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);
                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2405 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 785 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s + %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);
                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2425 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 801 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s * %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);
                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2445 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 817 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10);
                   sprintf(con,"%s / %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);

                   int tem_type=1;
                   if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                   free(con);
               }
#line 2466 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 834 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-4].node)->RHS)+20);
                   sprintf(con,"%s IN (子查询",(yyvsp[-4].node)->RHS);
                   (yyval.node) = Create_new_node(SELECT_SELECT,con);
                   (yyval.node)->L_child = (yyvsp[-4].node);
                   (yyvsp[-4].node)->Parent = (yyval.node);
                   (yyvsp[-4].node)->R_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyvsp[-4].node);
                   free(con);
               }
#line 2481 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 845 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-5].node)->RHS)+20);
                   sprintf(con,"%s NOT IN (子查询",(yyvsp[-5].node)->RHS);
                   (yyval.node) = Create_new_node(SELECT_SELECT,con);
                   (yyval.node)->L_child = (yyvsp[-5].node);
                   (yyvsp[-5].node)->Parent = (yyval.node);
                   (yyvsp[-5].node)->R_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyvsp[-5].node);
                   free(con);
               }
#line 2496 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 856 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+strlen((yyvsp[-4].node)->RHS)+20);
                   sprintf(con,"%s IN (%s)",(yyvsp[-4].node)->RHS,(yyvsp[-1].node)->RHS);
                   int tem_type=1;
                   if((yyvsp[-4].node)->type == SELECT_SELECT || (yyvsp[-1].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-4].node);
                   (yyvsp[-4].node)->Parent = (yyval.node);
                   (yyvsp[-4].node)->R_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyvsp[-4].node);
                   free(con);
               }
#line 2516 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 872 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-5].node)->RHS)+strlen((yyvsp[-1].node)->RHS)+20);
                   sprintf(con,"%s NOT IN (%s)",(yyvsp[-5].node)->RHS,(yyvsp[-1].node)->RHS);
                   int tem_type=1;
                   if((yyvsp[-5].node)->type == SELECT_SELECT || (yyvsp[-1].node)->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   (yyval.node) = Create_new_node(tem_type,con);
                   (yyval.node)->L_child = (yyvsp[-5].node);
                   (yyvsp[-5].node)->Parent = (yyval.node);
                   (yyvsp[-5].node)->R_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyvsp[-5].node);
                   free(con);
               }
#line 2536 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 888 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+10);
                   sprintf(con,"( %s )",(yyvsp[-1].node)->RHS);
                   (yyval.node) = Create_new_node((yyvsp[-1].node)->type,con);
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
                   free(con);
               }
#line 2549 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 897 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(SELECT_SELECT,"EXISTS (子查询");
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
               }
#line 2559 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 903 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                   free((yyvsp[0].strval));
               }
#line 2568 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 908 "Grammar.y" /* yacc.c:1646  */
    {
                   char con[200];
                   sprintf(con,"%s.*",(yyvsp[-2].strval));
                   (yyval.node) = Create_new_node(1,con);
                   free((yyvsp[-2].strval));
               }
#line 2579 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 915 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                   free((yyvsp[0].strval));
               }
#line 2588 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 920 "Grammar.y" /* yacc.c:1646  */
    {
                   char con[200];
                   sprintf(con,"%s.%s",(yyvsp[-2].strval),(yyvsp[0].strval));
                   (yyval.node) = Create_new_node(1,con);
               }
#line 2598 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 926 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+10);
                   sprintf(con,"(CASE %s END)",(yyvsp[-1].node)->RHS);
                   (yyval.node) = Create_new_node(2,con); 
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
                   free(con);
               }
#line 2611 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 935 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].strval))+10);
                   sprintf(con,"%s LIKE %s",(yyvsp[-2].node)->RHS,(yyvsp[0].strval));
                   (yyval.node) = Create_new_node((yyvsp[-2].node)->type,con); 
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   free(con);
                   free((yyvsp[0].strval));
               }
#line 2625 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 945 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-3].node)->RHS)+strlen((yyvsp[0].strval))+10);
                   sprintf(con,"%s NOT LIKE %s",(yyvsp[-3].node)->RHS,(yyvsp[0].strval));
                   (yyval.node) = Create_new_node((yyvsp[-3].node)->type,con); 
                   (yyval.node)->L_child = (yyvsp[-3].node);
                   (yyvsp[-3].node)->Parent = (yyval.node);
                   free(con);
                   free((yyvsp[0].strval));
               }
#line 2639 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 955 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(SELECT_SELECT,"(子查询"); 
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
               }
#line 2649 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 963 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(SYSTEM_CALL_VARIABLE,(yyvsp[0].strval)); 
               }
#line 2657 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 967 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(USER_CALL_VARIABLE,(yyvsp[0].strval)); 
               }
#line 2665 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 974 "Grammar.y" /* yacc.c:1646  */
    {
                //    char con[10000];
                //   printf("%d ",strlen($1)+strlen($3->RHS)+30);
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+strlen((yyvsp[-3].strval))+30); 
                   sprintf(con,"函数 %s(%s)",(yyvsp[-3].strval),(yyvsp[-1].node)->RHS);
                   (yyval.node) = Create_new_node((yyvsp[-1].node)->type,con);
                   free((yyvsp[-3].strval));
                   free(con);
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
               }
#line 2681 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 988 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node((yyvsp[0].node)->type,(yyvsp[0].node)->RHS);
            (yyval.node)->L_child = (yyvsp[0].node);
            (yyvsp[0].node)->Parent = (yyval.node);
        }
#line 2691 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 994 "Grammar.y" /* yacc.c:1646  */
    {
            
            char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].node)->RHS)+10); 
            sprintf(con,"%s , %s",(yyvsp[-2].node)->RHS,(yyvsp[0].node)->RHS);
            int tem_type=1;
            if((yyvsp[-2].node)->type == SELECT_SELECT || (yyvsp[0].node)->type == SELECT_SELECT)
            {
                tem_type = SELECT_SELECT;
            }
            (yyval.node) = Create_new_node(tem_type,con);
            (yyval.node)->L_child = (yyvsp[-2].node);
            (yyvsp[-2].node)->Parent = (yyval.node);
            (yyvsp[-2].node)->R_child = (yyvsp[0].node);
            (yyvsp[0].node)->Parent = (yyvsp[-2].node);
            free(con);
        }
#line 2712 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1011 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"*");
        }
#line 2720 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1019 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"opt_group_by NULL");
            }
#line 2728 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1023 "Grammar.y" /* yacc.c:1646  */
    {
                char con[500];
                int c = ((yyvsp[0].node)->type == 0)?0:1;
                if (c)
                {
                    sprintf(con,"%s %s",(yyvsp[-1].node)->RHS,(yyvsp[0].node)->RHS);
                }
                else 
                {
                    sprintf(con,"%s",(yyvsp[-1].node)->RHS);                
                }
                (yyval.node) = Create_new_node(OPT_GROUP_BY,con);
                // printf("%s",con);
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
            }
#line 2751 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1044 "Grammar.y" /* yacc.c:1646  */
    {
                char* con=(char*)malloc(strlen((yyvsp[-1].node)->RHS)+20);
                int c = (yyvsp[0].node)->type;
                if(c)
                sprintf(con,"%s %s",(yyvsp[-1].node)->RHS,(yyvsp[0].node)->RHS);
                else sprintf(con,"%s",(yyvsp[-1].node)->RHS);
                (yyval.node) = Create_new_node((yyvsp[-1].node)->type,con);
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
                free(con);
            }
#line 2769 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1058 "Grammar.y" /* yacc.c:1646  */
    {
                char* con=(char*)malloc(strlen((yyvsp[-3].node)->RHS)+20+strlen((yyvsp[-1].node)->RHS));
                int c = (yyvsp[0].node)->type;
                if(c)
                {
                    sprintf(con,"%s , %s %s",(yyvsp[-3].node)->RHS,(yyvsp[-1].node)->RHS,(yyvsp[0].node)->RHS);
                }
                else sprintf(con,"%s , %s",(yyvsp[-3].node)->RHS,(yyvsp[-1].node)->RHS);
                (yyval.node) = Create_new_node(1,con);
                (yyval.node)->L_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyval.node);
                (yyvsp[-3].node)->R_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyvsp[-3].node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
                free(con);
            }
#line 2791 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1078 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(0,"opt_asc_desc NULL");
            }
#line 2799 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1082 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(1,"ASC");
            }
#line 2807 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1086 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(1,"DESC");
            }
#line 2815 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1092 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"opt_with_rollup NULL");
              }
#line 2823 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1096 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,"WHIT ROLLUP");
              }
#line 2831 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1102 "Grammar.y" /* yacc.c:1646  */
    {
             (yyval.node) = Create_new_node(1,"opt_having NULL");
          }
#line 2839 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1106 "Grammar.y" /* yacc.c:1646  */
    {
             (yyval.node) = Create_new_node(HAVING,(yyvsp[0].node)->RHS);
             (yyval.node)->L_child = (yyvsp[0].node);
             (yyvsp[0].node)->Parent = (yyval.node);
          }
#line 2849 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1114 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"opt_order_by NULL");
            }
#line 2857 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1118 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ORDER,(yyvsp[0].node)->RHS);
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
            }
#line 2867 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1126 "Grammar.y" /* yacc.c:1646  */
    {
             (yyval.node) = Create_new_node(1,"opt_limit NULL");
         }
#line 2875 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1130 "Grammar.y" /* yacc.c:1646  */
    {
            char con[100];
            sprintf(con,"LIMIT %s",(yyvsp[0].strval));
            free((yyvsp[0].strval));
            (yyval.node) = Create_new_node(1,con);
         }
#line 2886 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1137 "Grammar.y" /* yacc.c:1646  */
    {
            char con[100];
            sprintf(con,"LIMIT %s.%s",(yyvsp[-2].strval),(yyvsp[0].strval));
            free((yyvsp[-2].strval)); free((yyvsp[0].strval));
            (yyval.node) = Create_new_node(1,con);
         }
#line 2897 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1146 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,"opt_into_list NULL");
             }
#line 2905 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1150 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,"INTO");
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
             }
#line 2915 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1158 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                free((yyvsp[0].strval));
           }
#line 2924 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1163 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                free((yyvsp[0].strval));
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node);
           }
#line 2935 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1171 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2941 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1173 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2947 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1176 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2953 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1177 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2959 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1180 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2965 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1181 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2971 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1184 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2977 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1185 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2983 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1188 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2989 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1189 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2995 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1192 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3001 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1193 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3007 "Grammar.tab.c" /* yacc.c:1646  */
    break;


#line 3011 "Grammar.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 1197 "Grammar.y" /* yacc.c:1906  */


int yyerror(char* a , int state)
{
   fprintf(stderr, "\n\terror: %s", a);
   if(state != -1)
   {
       fprintf(stderr, "\n\tline %d: ", yylineno);
    }
    return 0;
}

int main(int argc, char ** argv)
{  
    Init_stmt_vector();
    parse_getopt(argc,argv);
    yyparse();
    Del_stmt_vector();
    return 0;
}
 
void Init_stmt_vector()
{
    _stmt.vector_stmt = Init_vector(10);
    count=0;
}

void Init_select_info_vector(select_info* select_con)
{
    //  select_con->vector_test = Init_vector(10);
     select_con->vector_where = Init_vector(20); 
     select_con->vector_field = Init_vector(10);  
     select_con->vector_table = Init_vector(10); 
     select_con->vector_group_by = Init_vector(10);
     select_con->vector_opt = Init_vector(10);
     select_con->vector_having = Init_vector(10);
     select_con->vector_oder_by = Init_vector(10);;
}

void Del_stmt_vector()
{
    Del_vector(_stmt.vector_stmt);
    _stmt.vector_stmt = NULL;
}

void Del_select_info_vector()
{
    int i;
    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* select_con = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        Del_vector(select_con->vector_field);
        select_con->vector_field = NULL;
        Del_vector(select_con->vector_table);
        select_con->vector_table = NULL;
        Del_vector(select_con->vector_where);
        select_con->vector_where = NULL;
        Del_vector(select_con->vector_group_by);
        select_con->vector_group_by = NULL;
        Del_vector(select_con->vector_opt);
        select_con->vector_opt = NULL;
        Del_vector(select_con->vector_having);
        select_con->vector_having = NULL;
        Del_vector(select_con->vector_oder_by);
        select_con->vector_oder_by = NULL;
    }
}

void Main_struct(Tree_Node* enum_man,char* name)
{
    if(enum_man == NULL) return;
    if(enum_man->type == END)
    {
        select_info* select_con= (select_info*)malloc(sizeof(select_info));
        memset(select_con,0,sizeof(select_info));
        memcpy(select_con->name,name,strlen(name)+1);
        Init_select_info_vector(select_con);
        Get_select_info(enum_man,select_con);
        Vector_push_back(_stmt.vector_stmt,select_con);
        return;
    }
    Main_struct(enum_man->L_child,name);
    Main_struct(enum_man->R_child,name);
}

void Get_select_info(Tree_Node* enum_man,select_info* select_con)
{
    
    Get_opt_info(enum_man->R_child->L_child,select_con); //得到选项信息
    Tree_Node* tem = enum_man->R_child->R_child;
    // printf("%s" ,tem->RHS);
    if(tem->L_child == NULL)      //处理是*的字段信息
    {
        field_info* tem_struct = (field_info*)malloc(sizeof(field_info));
        if(tem_struct == NULL)
        {
            printf("malloc NULL");
            exit(0);
        }
        tem_struct->type = 0;
        tem_struct->field_name = tem;
        Vector_push_back(select_con->vector_field,tem_struct);
    }
    Get_field_info(tem->L_child,select_con);   //处理普通字段信息
    /*按照特定的规则遍历得到表的信息*/
    tem = tem->R_child;  
    if(tem == NULL)
    {
        return;
    }
    Get_table_info(tem->L_child,select_con);  //处理表信息
    tem = tem->R_child;
    Enum_get_opt_where_condition(tem,select_con);
    tem = tem->R_child;
    Enum_get_group_by(tem,select_con);
    tem = tem->R_child;
    Enum_get_having(tem,select_con);
    tem = tem->R_child;
    Enum_get_oder_by(tem,select_con);
}

void Get_opt_info(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man == NULL)
    {
        return;
    }
    Get_opt_info(enum_man->R_child,select_con);
    if(enum_man->type == SELECT_OPT)
    {
        Vector_push_back(select_con->vector_opt,enum_man);
    }
    Get_opt_info(enum_man->L_child,select_con);
}

void Get_field_info(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man == NULL) return;
    if(enum_man->type == FIELD_INFO_BEGIN && enum_man->L_child->type != FIELD_INFO_BEGIN)
    {
        Get_field_info_child(enum_man->R_child,select_con);  
        Get_field_info_child(enum_man->L_child,select_con);    
        return;
    }
    else if(enum_man->type == FIELD_INFO_BEGIN && enum_man->L_child->type == FIELD_INFO_BEGIN)
    {
        Get_field_info_child(enum_man->R_child,select_con);    
    }
    else
    {
        Get_field_info_child(enum_man,select_con);    
        return;
    }
    Get_field_info(enum_man->L_child,select_con);
}

void Get_field_info_child(Tree_Node* enum_man,select_info* select_con)
{
    Tree_Node* tem = enum_man->L_child;
    field_info* tem_struct = (field_info*)malloc(sizeof(field_info)); 
    memset(tem_struct,0,sizeof(field_info));

    if(tem->type == SELECT_SELECT)
    {
        tem->RHS = (char *)realloc(tem->RHS,strlen(tem->RHS)+30);
        sprintf(tem->RHS,"%s%d)",tem->RHS,count);
        tem_struct->field_name = tem;
        count++;
        Main_struct(tem,tem->RHS);
    }
    else
    {
        tem_struct->field_name = tem;
    }
    tem = enum_man->L_child->R_child;
    tem_struct->field_alias = tem;
    Vector_push_back(select_con->vector_field,tem_struct);
}

void Get_table_info(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man == NULL) return;
    
    if(enum_man->type == TABLE_INFO && enum_man->L_child->type != TABLE_INFO )
    {
       
        Get_table_info_child(enum_man->R_child,select_con);    
        Get_table_info_child(enum_man->L_child,select_con);    
        return;
    }
    else if(enum_man->type == TABLE_INFO && enum_man->L_child->type == TABLE_INFO )
    {
        Get_table_info_child(enum_man->R_child,select_con);    
    }
    else 
    {
        Get_table_info_child(enum_man,select_con);
        return;
    }
    Get_table_info(enum_man->L_child,select_con);
}


void Get_table_info_child(Tree_Node* enum_man,select_info* select_con)
{
   if(enum_man->type == NORMAL_TABLE)
   {
        Normal_get_info(enum_man->L_child,select_con);
   }
   else if(enum_man->type == JOIN_TABLE)
   {
        Join_get_info(enum_man->L_child,select_con);
   }
}

void Normal_get_info(Tree_Node* enum_man,select_info* select_con)
{
    Tree_Node* tem = enum_man;
    obj_info* tem_struct = (obj_info*)malloc(sizeof(obj_info));
    memset(tem_struct,0,sizeof(obj_info));

    if(tem->R_child != NULL && tem->R_child->type == JOIN_CONDITION)
    {
        tem_struct->obj_condition = tem->R_child;
    }

    if(tem->type == TABLE_SUB || tem->type == TABLE_REFERENCE)
    {
        tem = tem->L_child;
    }

    if(tem->type == SELECT_SELECT)
    {
        tem->RHS = (char *)realloc(tem->RHS,strlen(tem->RHS)+30);
        sprintf(tem->RHS,"%s%d)",tem->RHS,count);
        tem_struct->obj_name = tem;
        count++;
        Main_struct(tem,tem->RHS);
    }
    else
    {
        tem_struct->obj_name = tem;
    }

    if(enum_man->type == TABLE_SUB || enum_man->type == TABLE_REFERENCE)
    {
        tem =tem->R_child;
    }
    else tem = tem->L_child;
    tem_struct->obj_alias = tem;
    Vector_push_back(select_con->vector_table,tem_struct);
}

void Join_get_info(Tree_Node* enum_man,select_info* select_con)
{
    //处理 table_reference 这个点
    Tree_Node* tem = enum_man->L_child;
  
    Get_table_info(tem,select_con);
    if(enum_man->type == JOIN_TABLE_1)
    {
        tem = tem->R_child->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_2)
    {
        tem = tem->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_3)
    {
        tem = tem->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_4)
    {
        tem = tem->R_child->R_child->R_child;
    }
    else if(enum_man->type == JOIN_TABLE_5)
    {
        tem = tem->R_child->R_child;
    }
    Normal_get_info(tem,select_con);
}

 void Enum_get_opt_where_condition(Tree_Node* enum_man,select_info* select_con)
 {

     if(enum_man->type == OPT_WHERE)
     {

        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,count);
            count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_where,enum_man->L_child);
     }
 }

void  Enum_get_group_by(Tree_Node* enum_man,select_info* select_con)
{

    if(enum_man->type == OPT_GROUP_BY)
    {
        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,count);
            count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_group_by,enum_man);
    }
}

void Enum_get_having(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man->type == HAVING)
    {
        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,count);
            count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_having,enum_man);
    }
}

void Enum_get_oder_by(Tree_Node* enum_man,select_info* select_con)
{
    if(enum_man->type == ORDER)
    {
        if(enum_man->L_child != NULL &&  enum_man->L_child->type == SELECT_SELECT)
        {
            enum_man->L_child->RHS = (char*)realloc(enum_man->L_child->RHS,strlen(enum_man->L_child->RHS)+10);
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,count);
            count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_oder_by,enum_man);
    }
}


void Show_stmt_info()
{
    int i;
    int j;
    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        printf("%s \n",tem_stmt->name);
        // printf("%d",tem_stmt->vector_table->curr_size);
        if(tem_stmt->vector_table->curr_size !=0 ) printf("TABLE : ");
        for(j=0;j<tem_stmt->vector_table->curr_size;j++)
        {
            int c = 0;
            obj_info* tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,j);
            if(tem_obj->obj_alias == NULL) c=1; 
            printf("%s ALIAS %s \t",tem_obj->obj_name->RHS,c?"NULL":tem_obj->obj_alias->RHS);
            if ((Tree_Node*)tem_obj->obj_condition != NULL)
            {
                printf("---->条件 :  %s",((Tree_Node*)tem_obj->obj_condition)->RHS);
            }
        }
        if(tem_stmt->vector_table->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_field->curr_size !=0 ) printf("FIELD : ");
        for(j=0;j<tem_stmt->vector_field->curr_size;j++)
        {
            int c = 0;
            field_info* tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
            if(tem_field->field_alias == NULL) c=1; 
            printf("%s ALIAS %s \t",(tem_field->field_name)->RHS,c?"NULL":tem_field->field_alias->RHS);
        }
        if(tem_stmt->vector_field->curr_size !=0 ) printf("\n");
       
        if(tem_stmt->vector_where->curr_size != 0 ) printf("条件 : ");
        for(j=0;j<tem_stmt->vector_where->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_where,j))->RHS);
        }
        if(tem_stmt->vector_where->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_group_by->curr_size != 0 ) printf("GROUP_BY : ");
        for(j=0;j<tem_stmt->vector_group_by->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_group_by,j))->RHS);
        }
        if(tem_stmt->vector_group_by->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_having->curr_size != 0 ) printf("HAVING : ");
        for(j=0;j<tem_stmt->vector_having->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_having,j))->RHS);
        }
        if(tem_stmt->vector_having->curr_size !=0 ) printf("\n");

        if(tem_stmt->vector_oder_by->curr_size != 0 ) printf("ORDER_BY : ");
        for(j=0;j<tem_stmt->vector_oder_by->curr_size;j++)
        {
            printf("%s ",((Tree_Node*)Vetor_get(tem_stmt->vector_oder_by,j))->RHS);
        }
        if(tem_stmt->vector_oder_by->curr_size !=0 ) printf("\n");

        printf("\n\n");
    }

}



void Show_the_filed_info(char* filed)
{
    if(filed == NULL ) return;
    int Flag = 0;
    int i;
    int j;
    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        // if(tem_stmt->vector_field->curr_size !=0 ) printf("FIELD : ");
        for(j=0;j<tem_stmt->vector_field->curr_size;j++)
        {
            int c = 0;
            field_info* tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
            if(tem_field->field_alias == NULL) c=1; 
           // printf("%s ALIAS %s \t",(tem_field->field_name)->RHS,c?"NULL":tem_field->field_alias->RHS);
            // char* tem = strchar((tem_field->field_name)->RHS,".");
            // if(tem==NULL) continue;
            if(strcmp(filed,(tem_field->field_name)->RHS)==0 ||  (c==0 && strcmp(filed,tem_field->field_alias->RHS)==0))
            {
                Flag=1;
            }

        }


        // printf("%d",tem_stmt->vector_table->curr_size);
        if(Flag)
        {
            printf("%s \n",tem_stmt->name);
            if(tem_stmt->vector_table->curr_size !=0 ) printf("TABLE : ");
            for(j=0;j<tem_stmt->vector_table->curr_size;j++)
            {
                int c = 0;
                obj_info* tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,j);
                if(tem_obj->obj_alias == NULL) c=1; 
                printf("%s ALIAS %s \t",tem_obj->obj_name->RHS,c?"NULL":tem_obj->obj_alias->RHS);
                if ((Tree_Node*)tem_obj->obj_condition != NULL)
                {
                    printf("---->条件 :  %s",((Tree_Node*)tem_obj->obj_condition)->RHS);
                }
            }
            if(tem_stmt->vector_table->curr_size !=0 ) printf("\n");
            Flag=0;
            printf("\n\n");
        }
       
    }

}


int parse_getopt(int argc,char** argv)
{
    int opt;

    yyin = fopen(argv[argc-1],"r");
    struct option opt_choose[] =
            {
                    {"getField",1,NULL,'g'},
                    {"all",0,NULL,'a'},
            };
    while ((opt = getopt_long(argc,argv,"g:",opt_choose,NULL))!=-1)
    {
        switch (opt)
        {
            case 'g':
                _Global.mode = GET_MODE;
                _Global.field_name = optarg;
                break;
            case 'a':
                _Global.mode = ALL_MODE;
                break;
            default:
                _Global.mode = ALL_MODE;
                //usage(optarg);
                break;
        }
    }
    return;
}
