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

#define STMT_MAX 1024*1024

typedef struct stmt
{
   int stmt_statment;
   c_vector* vector_stmt;
}stmt;

typedef struct chache_stmt
{
    u_int64_t   now_offset;
    u_int64_t   size;   
    char* chache;
}chache_stmt;


typedef struct Global
{
    int mode;
    char* field_name;
    char* table_alias_name;
    char* database_name;
    char* real_field_name;
    char* file_name;
    
    int count;
    Tree_Node* root;                //语句序列的ROOT节点
    chache_stmt* ptr_chache;
}Global;

enum
{
    ALL_MODE,
    GET_MODE,
    PHYSICAL_MODE,
    TEST_MODE,
    BACK_STMT
};

typedef struct select_info
{
    char name[30];
    c_vector* vector_field;         //field_info
    c_vector* vector_opt;           //Node*
    c_vector* vector_table;
    c_vector* vector_where;
    c_vector* vector_group_by;
    c_vector* vector_having;
    c_vector* vector_oder_by;
}select_info;


typedef struct obj_info
{
    int type;                       //用来标记是否为子查询
    Tree_Node* obj_name;            //记录字段的名字
    Tree_Node* obj_alias;           //记录字段的别名
    Tree_Node* obj_condition;       //记录改字段的条件
    c_vector* obj_field;            //指向同一个SELECT下面可能对应的字段信息
    Tree_Node* select_select;       //记录为子查询的节点（no use）
}obj_info;

typedef struct field_info
{
    int type;
    Tree_Node* field_name;
    Tree_Node* field_alias;
    c_vector* field_table;
    Tree_Node* field_table_info;
    c_vector* field_physical_info;
    Tree_Node* select_select;
}field_info;

typedef struct _String
{
    u_int64_t   string_size;
    char*       string_ptr;
}_String;

stmt _stmt;                                             //一条语句的所有信息
Global _Global;                                         //全局使用变量的结构体
void usage();                                           //提示怎么输入的提示函数
int parse_getopt(int argc,char** argv);                 //命令行解析函数和
void Init_stmt_vector();
void Init_select_info_vector(select_info* select_con);
void Del_stmt_vector();
void Del_select_info_vector();

void Main_mode();

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
void Show_the_filed_info();
void Show_all_physical_table();

int Single_search_stmt(char* search);
void All_table(select_info* tem_stmt);
int Search_select_info_table(select_info* tem_stmt);
/*
*   将每一层抽象里面的表和字段的vector对应起来
*/
int Connect_field_table(select_info* tem_stmt);
void Connect_enum_main();
int Connect_field_table_child(select_info* tem_stmt,field_info* tem_field);

void Subquery_get_info(char* search,char* real_field_name,field_info* save_field);

//将字段信息切割 为 database table filed 的格式
int Str_cut_for_real_alias(char* field_name,char** database_name,char** table_alias_name,char** real_field_name);
void All_table_this_floor(select_info* tem_stmt,char* real_field_name,field_info* save_field);

void Get_back_stmt(stmt* back_stmt);
void Find_main(stmt* back_stmt,c_vector* main_select_info);
int Show_select_info(select_info* main_select,c_vector* union_stmt,stmt* back_stmt);
char* Get_subquery_stmt(char* search,stmt* back_stmt);
void Find_sub(stmt* back_stmt,c_vector* main_select_info,char* search);
void Init_chache_stmt();
int Insert_str(char* str);
void Expend_chache();

#line 212 "Grammar.tab.c" /* yacc.c:339  */

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
    INSERT = 298,
    UPDATE = 299,
    CREATE = 300,
    ID = 301,
    SET = 302,
    VALUES = 303,
    DATABASE = 304,
    AS = 305,
    NAME = 306,
    ASC = 307,
    DESC = 308,
    INTO = 309,
    NUM = 310,
    WITH = 311,
    ROLLUP = 312,
    CONCAT = 313,
    CASE = 314,
    THEN = 315,
    WHEN = 316,
    END = 317,
    ELSE = 318,
    FLOOR = 319
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 148 "Grammar.y" /* yacc.c:355  */

    struct Tree_Node* node;
    char* strval;

#line 322 "Grammar.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 339 "Grammar.tab.c" /* yacc.c:358  */

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
#define YYLAST   360

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  239

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

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
      72,    73,     9,    12,    71,    10,    13,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    70,
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
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   194,   194,   199,   207,   210,   215,   219,   223,   231,
     237,   245,   255,   270,   321,   325,   328,   336,   344,   352,
     360,   368,   376,   384,   392,   405,   411,   419,   428,   442,
     447,   453,   461,   467,   480,   491,   506,   512,   530,   537,
     551,   560,   571,   579,   585,   598,   609,   621,   629,   640,
     654,   666,   672,   679,   684,   688,   695,   698,   705,   708,
     712,   719,   722,   730,   739,   749,   755,   758,   767,   784,
     802,   820,   836,   852,   868,   885,   896,   907,   923,   939,
     948,   954,   959,   966,   971,   977,   986,   996,  1006,  1014,
    1018,  1025,  1039,  1045,  1062,  1071,  1074,  1095,  1109,  1130,
    1133,  1137,  1144,  1147,  1154,  1157,  1166,  1169,  1178,  1181,
    1188,  1198,  1201,  1209,  1214,  1223,  1225,  1228,  1232,  1238,
    1239,  1242,  1243,  1246,  1247,  1250,  1251
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
  "OUTER", "NATURAL", "EXISTS", "UNION", "INSERT", "UPDATE", "CREATE",
  "ID", "SET", "VALUES", "DATABASE", "AS", "NAME", "ASC", "DESC", "INTO",
  "NUM", "WITH", "ROLLUP", "CONCAT", "CASE", "THEN", "WHEN", "END", "ELSE",
  "FLOOR", "';'", "','", "'('", "')'", "$accept", "SQLS", "SQL",
  "select_exp", "select_expr_stmt", "end", "select_opts",
  "select_expr_list", "select_expr", "opt_as_alias", "case_when_fun",
  "when_then", "table_references", "table_reference", "table_factor",
  "table_subquery", "join_table", "opt_left_or_right", "left_or_right",
  "opt_outer", "opt_inner_cross", "opt_join_condition", "join_condition",
  "index_hint", "opt_where", "where_condition", "val_list", "opt_group_by",
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
      59,    44,    40,    41
};
# endif

#define YYPACT_NINF -170

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-170)))

#define YYTABLE_NINF -89

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      49,  -170,   -50,   -40,    12,    10,    -1,   -26,  -170,  -170,
    -170,  -170,   136,   -14,    35,    37,  -170,    43,  -170,    -3,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,  -170,    33,   -11,  -170,    75,   267,   -21,  -170,   274,
      18,    90,  -170,  -170,   124,  -170,   124,    -5,   156,   278,
     278,   100,  -170,   -34,    22,   -49,   278,  -170,   278,   278,
     278,    58,    96,   113,   278,   278,   278,   278,   135,  -170,
    -170,    89,   142,   181,  -170,   -33,  -170,  -170,  -170,   300,
     101,   128,   300,  -170,  -170,  -170,  -170,    36,   272,    -9,
     208,  -170,    17,  -170,  -170,   106,   106,   106,   139,   133,
     151,  -170,  -170,  -170,  -170,  -170,  -170,   153,   143,   140,
     159,   161,  -170,   278,  -170,   278,   162,  -170,   184,   272,
     -30,   104,    74,   278,   -49,   189,   -49,  -170,  -170,  -170,
    -170,    66,   180,   196,  -170,   -28,   105,   139,  -170,   163,
     164,   185,  -170,   190,   171,   215,   300,   300,    17,  -170,
       9,    21,   117,  -170,  -170,    17,   300,   208,   221,   222,
     218,   180,   180,   223,  -170,   224,   -49,  -170,  -170,    23,
     110,  -170,  -170,   188,   191,  -170,   206,  -170,   193,   348,
     193,  -170,   278,   278,   231,   278,  -170,  -170,   -49,   -49,
     146,  -170,  -170,  -170,   153,   284,  -170,  -170,   264,    39,
     300,   257,   254,   300,  -170,   146,   278,  -170,  -170,  -170,
     220,   238,  -170,  -170,  -170,   236,   278,  -170,   278,   239,
     241,  -170,   300,  -170,  -170,  -170,   264,   243,   244,   260,
    -170,  -170,   259,  -170,   246,  -170,  -170,   269,  -170
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
       0,    86,    73,    71,    74,    72,    29,     0,   119,     0,
       0,     0,    80,     0,    91,     0,     0,    65,    81,     0,
       0,     0,     0,     0,     0,    95,     0,    59,    60,    54,
      55,    53,    56,     0,    42,     0,     0,     0,    87,   123,
       0,     0,   121,     0,   120,     0,    93,    34,    31,    40,
       0,     0,     0,    45,    43,    31,    67,    37,     0,   104,
      47,    56,    56,     0,    57,     0,     0,    75,    77,     0,
       0,   125,   118,   124,     0,   122,     0,    65,    84,    45,
      79,    65,     0,     0,   106,     0,    51,    52,     0,     0,
      61,    76,    78,   126,     0,     0,    41,    44,    99,   102,
     105,     0,   108,    48,    50,     0,     0,    64,    46,    62,
       0,     0,   100,   101,    97,     0,     0,    96,     0,     0,
     111,    49,    63,   117,   116,   103,    99,   107,   109,     0,
      14,    98,     0,   113,   112,    13,   110,     0,   114
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -170,  -170,   315,   -31,    70,   103,  -170,  -170,   270,   -36,
    -170,   286,   280,   216,  -125,  -170,  -170,  -170,  -170,    27,
    -170,  -170,   138,  -169,  -170,   -12,   -62,  -170,   123,   119,
    -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,  -170,
    -170,   152,  -170
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    57,    12,    37,    38,   117,
      51,    52,   121,    90,    91,    92,    93,   163,   132,   165,
     133,   208,   209,   149,   125,    79,    80,   159,   199,   214,
     217,   184,   202,   220,   230,   234,     9,    10,    11,   109,
     110,   140,   141
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   160,    47,    70,    76,    53,    55,    87,   196,    13,
      16,    44,   197,    19,    19,    75,    14,    19,    76,    19,
     123,    19,     1,    88,    54,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,     1,   136,    81,    82,    85,
     112,   190,    40,   153,    39,   167,    95,    96,    97,   116,
      56,    77,   102,   103,   104,   105,   134,   120,     2,     3,
       4,    48,   124,   204,   205,   178,    15,   135,    19,    18,
      19,    71,    68,    69,     1,   170,   122,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    41,   151,    45,
      72,    68,    69,    42,   179,    86,   191,     2,     3,     4,
     215,   146,    99,   147,   100,    46,   169,   152,   161,   162,
     216,   156,   177,    43,    74,    64,    65,    66,    67,   181,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      98,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    49,   177,    50,   181,    20,    73,   155,    78,     1,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,   107,    30,    31,     1,    78,    49,    83,    50,   101,
     198,   200,   113,   203,   114,   124,   113,   154,   168,    30,
      31,   113,    32,   192,   111,    32,   206,   207,   186,   187,
     180,   106,    33,   115,   222,    33,    34,   150,   108,    34,
      35,   -31,    32,    35,   226,   137,   198,   138,    36,   139,
     -31,    36,    33,   143,   142,   144,    34,   145,   148,   158,
      35,   -31,   -31,   -31,   164,   126,   -31,   -31,    36,   -31,
     -31,   -31,   -31,   166,   171,   -31,   -31,   172,   -31,    68,
      69,   173,   175,   174,   176,   -58,   127,   128,    68,    69,
     129,   130,   182,   131,   183,   -31,    48,   -31,   185,   193,
     188,   189,   195,   194,   -31,   201,   -31,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   211,   218,   219,
      30,    31,     1,   223,   224,    30,    31,     1,   225,   228,
     229,    30,    31,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    32,   216,   232,   233,   237,    32,   236,
      17,   212,   213,    33,    32,   238,    94,    34,   118,    68,
      69,    35,    34,   235,    33,    89,    35,    84,    34,    36,
     157,   227,    35,   221,   119,   231,   210,     0,     0,     0,
      36,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,   -88,
     -88
};

static const yytype_int16 yycheck[] =
{
      12,   126,    13,    39,     9,    36,    27,    56,   177,    59,
       0,    14,   181,    47,    47,    46,    56,    47,     9,    47,
      29,    47,    25,    72,    36,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    25,    98,    49,    50,    73,
      73,   166,    56,    73,    56,    73,    58,    59,    60,    13,
      71,    56,    64,    65,    66,    67,    92,    88,    48,    49,
      50,    72,    71,   188,   189,    56,    54,    98,    47,    70,
      47,    53,    55,    56,    25,   137,    88,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    52,   119,    19,
      72,    55,    56,    56,    73,    73,    73,    48,    49,    50,
      61,   113,     6,   115,     8,    72,   137,   119,    42,    43,
      71,   123,   148,    70,    44,     9,    10,    11,    12,   155,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      72,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    66,   178,    68,   180,     9,    56,    73,     9,    25,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    72,    23,    24,    25,     9,    66,    67,    68,    56,
     182,   183,    71,   185,    73,    71,    71,    73,    73,    23,
      24,    71,    46,    73,     3,    46,    40,    41,   161,   162,
      73,    56,    56,    65,   206,    56,    60,    13,    56,    60,
      64,    17,    46,    64,   216,    72,   218,    56,    72,    56,
      17,    72,    56,    73,    71,    56,    60,    56,    56,    30,
      64,    37,    38,    39,    44,    17,    42,    43,    72,    45,
      37,    38,    39,    37,    71,    42,    43,    73,    45,    55,
      56,    56,    71,    53,    29,    37,    38,    39,    55,    56,
      42,    43,    31,    45,    32,    71,    72,    73,    40,    71,
      37,    37,    56,    72,    71,    34,    73,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,     3,    31,    35,
      23,    24,    25,    73,    56,    23,    24,    25,    62,    60,
      59,    23,    24,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    46,    71,    71,    56,    71,    46,    60,
       5,    57,    58,    56,    46,    56,    56,    60,    56,    55,
      56,    64,    60,   230,    56,    55,    64,    51,    60,    72,
     124,   218,    64,   205,    72,   226,   194,    -1,    -1,    -1,
      72,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    48,    49,    50,    75,    76,    77,    78,   110,
     111,   112,    80,    59,    56,    54,     0,    76,    70,    47,
       9,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    46,    56,    60,    64,    72,    81,    82,    99,
      56,    52,    56,    70,    14,    78,    72,    13,    72,    66,
      68,    84,    85,    77,    99,    27,    71,    79,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    55,    56,
      83,    53,    72,    56,    78,    77,     9,    56,     9,    99,
     100,    99,    99,    67,    85,    73,    73,    56,    72,    86,
      87,    88,    89,    90,    82,    99,    99,    99,    72,     6,
       8,    56,    99,    99,    99,    99,    56,    72,    56,   113,
     114,     3,    73,    71,    73,    65,    13,    83,    56,    72,
      77,    86,    99,    29,    71,    98,    17,    38,    39,    42,
      43,    45,    92,    94,    83,    77,   100,    72,    56,    56,
     115,   116,    71,    73,    56,    56,    99,    99,    56,    97,
      13,    77,    99,    73,    73,    73,    99,    87,    30,   101,
      88,    42,    43,    91,    44,    93,    37,    73,    73,    77,
     100,    71,    73,    56,    53,    71,    29,    83,    56,    73,
      73,    83,    31,    32,   105,    40,    93,    93,    37,    37,
      88,    73,    73,    71,    72,    56,    97,    97,    99,   102,
      99,    34,   106,    99,    88,    88,    40,    41,    95,    96,
     115,     3,    57,    58,   103,    61,    71,   104,    31,    35,
     107,    96,    99,    73,    56,    62,    99,   102,    60,    59,
     108,   103,    71,    56,   109,    79,    60,    71,    56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    75,    76,    76,    76,    76,    76,    77,
      77,    77,    78,    78,    79,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    81,    81,    81,    82,    83,
      83,    83,    84,    84,    85,    85,    86,    86,    87,    87,
      88,    88,    88,    88,    88,    89,    90,    90,    90,    90,
      90,    91,    91,    91,    92,    92,    93,    93,    94,    94,
      94,    95,    95,    96,    96,    97,    98,    98,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   100,   101,   101,   102,   102,   103,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     107,   108,   108,   109,   109,   110,   111,   112,   112,   113,
     113,   114,   114,   115,   115,   116,   116
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
#line 195 "Grammar.y" /* yacc.c:1646  */
    {
        (yyval.node) = (yyvsp[-1].node);
        _Global.root = (yyval.node);
    }
#line 1624 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 200 "Grammar.y" /* yacc.c:1646  */
    {   
        (yyval.node) = (yyvsp[-1].node);
        (yyvsp[-2].node)->R_child = (yyvsp[-1].node);
    }
#line 1633 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 207 "Grammar.y" /* yacc.c:1646  */
    {
        (yyval.node) = Create_new_node(0,"SELECT T 语句");
    }
#line 1641 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 211 "Grammar.y" /* yacc.c:1646  */
    {
        (yyval.node) = Create_new_node(INSERT,"INSERT");
        (yyval.node)->L_child = (yyvsp[0].node); 
    }
#line 1650 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 216 "Grammar.y" /* yacc.c:1646  */
    {
        printf("\tstat : update\n");
    }
#line 1658 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 220 "Grammar.y" /* yacc.c:1646  */
    {
        printf("\tstat : create\n");
    }
#line 1666 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 224 "Grammar.y" /* yacc.c:1646  */
    {
        (yyval.node) = Create_new_node(SELECT,"SELECT");
        (yyval.node)->L_child = (yyvsp[0].node);
        Main_struct((yyvsp[0].node),"MAIN");
    }
#line 1676 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 232 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"\nBEGIN");
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node); 
          }
#line 1686 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 238 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"BEGIN 语句 union");
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node); 
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
          }
#line 1698 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 246 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"BEGIN 语句 union");
                (yyval.node)->L_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyval.node); 
                (yyvsp[-3].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-3].node);
          }
#line 1710 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 256 "Grammar.y" /* yacc.c:1646  */
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
#line 1729 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 271 "Grammar.y" /* yacc.c:1646  */
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
#line 1777 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 321 "Grammar.y" /* yacc.c:1646  */
    {
       (yyval.node) = Create_new_node(END,"SELECT BEGIN : ");
   }
#line 1785 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 325 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
              }
#line 1793 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 329 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1805 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 337 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1817 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 345 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1829 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 353 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1841 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 361 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1853 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 369 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt3");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1865 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 377 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1877 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 385 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1889 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 393 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
          }
#line 1901 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 406 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(FIELD_INFO_BEGIN,"field_info_begin");
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                }
#line 1911 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 412 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(FIELD_INFO_BEGIN,"field_info_begin");
                    (yyval.node)->L_child = (yyvsp[-2].node);
                    (yyvsp[-2].node)->Parent = (yyval.node);
                    (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                }
#line 1923 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 420 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(FIELD_NAME,"*");
                }
#line 1931 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 429 "Grammar.y" /* yacc.c:1646  */
    {
              (yyval.node) = Create_new_node(FIELD_NODE,"field");
              (yyval.node)->L_child = (yyvsp[-1].node);
              (yyvsp[-1].node)->Parent = (yyval.node);
              (yyvsp[-1].node)->R_child = (yyvsp[0].node);
              (yyvsp[0].node)->Parent = (yyvsp[-1].node);
           }
#line 1943 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 443 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ALIAS_NAME,(yyvsp[0].strval)); 
                free((yyvsp[0].strval));
            }
#line 1952 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 448 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ALIAS_NAME,(yyvsp[0].strval)); 
                free((yyvsp[0].strval));
            }
#line 1961 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 453 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ALIAS_NAME,"NULL"); 
            }
#line 1969 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 462 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(2,(yyvsp[0].node)->RHS); 
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
             }
#line 1979 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 468 "Grammar.y" /* yacc.c:1646  */
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
#line 1994 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 481 "Grammar.y" /* yacc.c:1646  */
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
#line 2009 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 492 "Grammar.y" /* yacc.c:1646  */
    {
                char* con=(char*)malloc(strlen((yyvsp[0].node)->RHS)+10);
                sprintf(con,"ELSE %s",(yyvsp[0].node)->RHS);
                (yyval.node) = Create_new_node(2,con); 
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
                free(con);
         }
#line 2022 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 507 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(TABLE_INFO,"表信息");
                   (yyval.node)->L_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyval.node);
                }
#line 2032 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 513 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(TABLE_INFO,"表信息");
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyvsp[-2].node);
                }
#line 2044 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 530 "Grammar.y" /* yacc.c:1646  */
    {
                                (yyval.node) = Create_new_node(NORMAL_TABLE,"Normal table");
                                (yyval.node)->L_child = (yyvsp[0].node);
                                (yyvsp[0].node)->Parent = (yyval.node);
                              //  Enum_tree_node_deep($$);
                              //  printf("%s  %d\n",$$->RHS,$$->type);
                              }
#line 2056 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 538 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(JOIN_TABLE,"JOIN表");
                   (yyval.node)->L_child = (yyvsp[0].node);
                   (yyvsp[0].node)->Parent = (yyval.node);
               }
#line 2066 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 551 "Grammar.y" /* yacc.c:1646  */
    { 
                                             (yyval.node) = Create_new_node(TABLE_NAME,(yyvsp[-2].strval));
                                             free((yyvsp[-2].strval));
                                             (yyval.node)->L_child = (yyvsp[-1].node);
                                             (yyvsp[-1].node)->Parent = (yyval.node);
                                             (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                                             (yyvsp[0].node)->Parent = (yyvsp[-1].node);
                                        //   printf("%s  %d\n",$$->RHS,$$->type);
                                            }
#line 2080 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 561 "Grammar.y" /* yacc.c:1646  */
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
#line 2095 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 572 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(TABLE_SUB,"table_sub");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
            }
#line 2107 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 580 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(TABLE_REFERENCE,"为(table_references)");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
            }
#line 2117 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 586 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(TABLE_REFERENCE,"为(table_references)");
                (yyval.node)->L_child = (yyvsp[-3].node);
                (yyvsp[-3].node)->Parent = (yyval.node);
                (yyvsp[-3].node)->R_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyvsp[-3].node);
                (yyvsp[-1].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-1].node);
            }
#line 2131 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 599 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(SELECT_SELECT,"(子查询");
                (yyval.node)->L_child = (yyvsp[-1].node);
                (yyvsp[-1].node)->Parent = (yyval.node);
              }
#line 2141 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 610 "Grammar.y" /* yacc.c:1646  */
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
#line 2157 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 622 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_2,"Join表的选项 JION2");
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
          }
#line 2169 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 630 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_3,"Join表的选项 STRIGHT_JOIN ON3");
                (yyval.node)->L_child = (yyvsp[-4].node);
                (yyvsp[-4].node)->Parent = (yyval.node);
                (yyvsp[-4].node)->R_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyvsp[-4].node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);

          }
#line 2184 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 641 "Grammar.y" /* yacc.c:1646  */
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
#line 2202 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 655 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(JOIN_TABLE_5,"Join表的选项 NATURAL5");
                (yyval.node)->L_child = (yyvsp[-4].node);
                (yyvsp[-4].node)->Parent = (yyval.node);
                (yyvsp[-4].node)->R_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyvsp[-4].node);
                (yyvsp[-2].node)->R_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyvsp[-2].node);
          }
#line 2216 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 667 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(LEFT,"LEFT");
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                 }
#line 2226 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 673 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(RIGHT,"RIGHT");
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                 }
#line 2236 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 679 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(RIGHT,"NULL");
                 }
#line 2244 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 685 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(LEFT,"LEFT");
             }
#line 2252 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 689 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(RIGHT,"RIGHT");
             }
#line 2260 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 695 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"NULL");
         }
#line 2268 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 699 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"OUTER");
         }
#line 2276 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 705 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(1,"NULL");
               }
#line 2284 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 709 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(1,"INNER");
               }
#line 2292 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 713 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(1,"CROSS");
               }
#line 2300 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 719 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(1,"NULL");
                  }
#line 2308 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 723 "Grammar.y" /* yacc.c:1646  */
    {
                    (yyval.node) = Create_new_node(JOIN_CONDITION,(yyvsp[0].node)->RHS);
                    (yyval.node)->L_child = (yyvsp[0].node);
                    (yyvsp[0].node)->Parent = (yyval.node);
                  }
#line 2318 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 731 "Grammar.y" /* yacc.c:1646  */
    {
                  char* con = (char*)malloc(strlen((yyvsp[0].node)->RHS)+1);
                  sprintf(con,"ON %s",(yyvsp[0].node)->RHS);
                  (yyval.node) = Create_new_node(JOIN_CONDITION,con);
                  (yyval.node)->L_child = (yyvsp[0].node);
                  (yyvsp[0].node)->Parent = (yyval.node);
                  free(con);
              }
#line 2331 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 740 "Grammar.y" /* yacc.c:1646  */
    {
                  (yyval.node) = Create_new_node(JOIN_CONDITION,"USING");
              }
#line 2339 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 749 "Grammar.y" /* yacc.c:1646  */
    {
              (yyval.node) = Create_new_node(1,"index NULL");
          }
#line 2347 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 755 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"NO WHERE");
         }
#line 2355 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 759 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(OPT_WHERE,(yyvsp[0].node)->RHS);
            (yyval.node)->L_child = (yyvsp[0].node);
            (yyvsp[0].node)->Parent = (yyval.node);
         }
#line 2365 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 768 "Grammar.y" /* yacc.c:1646  */
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
#line 2386 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 785 "Grammar.y" /* yacc.c:1646  */
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
#line 2408 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 803 "Grammar.y" /* yacc.c:1646  */
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
#line 2430 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 821 "Grammar.y" /* yacc.c:1646  */
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
#line 2450 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 837 "Grammar.y" /* yacc.c:1646  */
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
#line 2470 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 853 "Grammar.y" /* yacc.c:1646  */
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
#line 2490 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 869 "Grammar.y" /* yacc.c:1646  */
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
#line 2511 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 886 "Grammar.y" /* yacc.c:1646  */
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
#line 2526 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 897 "Grammar.y" /* yacc.c:1646  */
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
#line 2541 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 908 "Grammar.y" /* yacc.c:1646  */
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
#line 2561 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 924 "Grammar.y" /* yacc.c:1646  */
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
#line 2581 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 940 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+10);
                   sprintf(con,"( %s )",(yyvsp[-1].node)->RHS);
                   (yyval.node) = Create_new_node((yyvsp[-1].node)->type,con);
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
                   free(con);
               }
#line 2594 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 949 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(SELECT_SELECT,"EXISTS (子查询");
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
               }
#line 2604 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 955 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                   free((yyvsp[0].strval));
               }
#line 2613 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 960 "Grammar.y" /* yacc.c:1646  */
    {
                   char con[200];
                   sprintf(con,"%s.*",(yyvsp[-2].strval));
                   (yyval.node) = Create_new_node(1,con);
                   free((yyvsp[-2].strval));
               }
#line 2624 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 967 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                   free((yyvsp[0].strval));
               }
#line 2633 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 972 "Grammar.y" /* yacc.c:1646  */
    {
                   char con[200];
                   sprintf(con,"%s.%s",(yyvsp[-2].strval),(yyvsp[0].strval));
                   (yyval.node) = Create_new_node(1,con);
               }
#line 2643 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 978 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+10);
                   sprintf(con,"(CASE %s END)",(yyvsp[-1].node)->RHS);
                   (yyval.node) = Create_new_node(2,con); 
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
                   free(con);
               }
#line 2656 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 987 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-2].node)->RHS)+strlen((yyvsp[0].strval))+10);
                   sprintf(con,"%s LIKE %s",(yyvsp[-2].node)->RHS,(yyvsp[0].strval));
                   (yyval.node) = Create_new_node((yyvsp[-2].node)->type,con); 
                   (yyval.node)->L_child = (yyvsp[-2].node);
                   (yyvsp[-2].node)->Parent = (yyval.node);
                   free(con);
                   free((yyvsp[0].strval));
               }
#line 2670 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 997 "Grammar.y" /* yacc.c:1646  */
    {
                   char* con = (char*)malloc(strlen((yyvsp[-3].node)->RHS)+strlen((yyvsp[0].strval))+10);
                   sprintf(con,"%s NOT LIKE %s",(yyvsp[-3].node)->RHS,(yyvsp[0].strval));
                   (yyval.node) = Create_new_node((yyvsp[-3].node)->type,con); 
                   (yyval.node)->L_child = (yyvsp[-3].node);
                   (yyvsp[-3].node)->Parent = (yyval.node);
                   free(con);
                   free((yyvsp[0].strval));
               }
#line 2684 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1007 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(SELECT_SELECT,"(子查询"); 
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
               }
#line 2694 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1015 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(SYSTEM_CALL_VARIABLE,(yyvsp[0].strval)); 
               }
#line 2702 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1019 "Grammar.y" /* yacc.c:1646  */
    {
                   (yyval.node) = Create_new_node(USER_CALL_VARIABLE,(yyvsp[0].strval)); 
               }
#line 2710 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1026 "Grammar.y" /* yacc.c:1646  */
    {
                //    char con[10000];
                //   printf("%d ",strlen($1)+strlen($3->RHS)+30);
                   char* con = (char*)malloc(strlen((yyvsp[-1].node)->RHS)+strlen((yyvsp[-3].strval))+30); 
                   sprintf(con,"%s(%s)",(yyvsp[-3].strval),(yyvsp[-1].node)->RHS);
                   (yyval.node) = Create_new_node((yyvsp[-1].node)->type,con);
                   free((yyvsp[-3].strval));
                   free(con);
                   (yyval.node)->L_child = (yyvsp[-1].node);
                   (yyvsp[-1].node)->Parent = (yyval.node);
               }
#line 2726 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1040 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node((yyvsp[0].node)->type,(yyvsp[0].node)->RHS);
            (yyval.node)->L_child = (yyvsp[0].node);
            (yyvsp[0].node)->Parent = (yyval.node);
        }
#line 2736 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1046 "Grammar.y" /* yacc.c:1646  */
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
#line 2757 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1063 "Grammar.y" /* yacc.c:1646  */
    {
            (yyval.node) = Create_new_node(1,"*");
        }
#line 2765 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1071 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"opt_group_by NULL");
            }
#line 2773 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1075 "Grammar.y" /* yacc.c:1646  */
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
#line 2796 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1096 "Grammar.y" /* yacc.c:1646  */
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
#line 2814 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1110 "Grammar.y" /* yacc.c:1646  */
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
#line 2836 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1130 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(0,"opt_asc_desc NULL");
            }
#line 2844 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1134 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(1,"ASC");
            }
#line 2852 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1138 "Grammar.y" /* yacc.c:1646  */
    {
               (yyval.node) = Create_new_node(1,"DESC");
            }
#line 2860 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1144 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"opt_with_rollup NULL");
              }
#line 2868 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1148 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,"WHIT ROLLUP");
              }
#line 2876 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1154 "Grammar.y" /* yacc.c:1646  */
    {
             (yyval.node) = Create_new_node(1,"opt_having NULL");
          }
#line 2884 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1158 "Grammar.y" /* yacc.c:1646  */
    {
             (yyval.node) = Create_new_node(HAVING,(yyvsp[0].node)->RHS);
             (yyval.node)->L_child = (yyvsp[0].node);
             (yyvsp[0].node)->Parent = (yyval.node);
          }
#line 2894 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1166 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(0,"opt_order_by NULL");
            }
#line 2902 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1170 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(ORDER,(yyvsp[0].node)->RHS);
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
            }
#line 2912 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1178 "Grammar.y" /* yacc.c:1646  */
    {
             (yyval.node) = Create_new_node(1,"opt_limit NULL");
         }
#line 2920 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1182 "Grammar.y" /* yacc.c:1646  */
    {
            char con[100];
            sprintf(con,"LIMIT %s",(yyvsp[0].strval));
            free((yyvsp[0].strval));
            (yyval.node) = Create_new_node(1,con);
         }
#line 2931 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1189 "Grammar.y" /* yacc.c:1646  */
    {
            char con[100];
            sprintf(con,"LIMIT %s.%s",(yyvsp[-2].strval),(yyvsp[0].strval));
            free((yyvsp[-2].strval)); free((yyvsp[0].strval));
            (yyval.node) = Create_new_node(1,con);
         }
#line 2942 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1198 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,"opt_into_list NULL");
             }
#line 2950 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1202 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,"INTO");
                (yyval.node)->L_child = (yyvsp[0].node);
                (yyvsp[0].node)->Parent = (yyval.node);
             }
#line 2960 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1210 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                free((yyvsp[0].strval));
           }
#line 2969 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1215 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(1,(yyvsp[0].strval));
                free((yyvsp[0].strval));
                (yyval.node)->L_child = (yyvsp[-2].node);
                (yyvsp[-2].node)->Parent = (yyval.node);
           }
#line 2980 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1223 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2986 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1225 "Grammar.y" /* yacc.c:1646  */
    {}
#line 2992 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1229 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(INSERT,"insert into name() valuse()");
            }
#line 3000 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1233 "Grammar.y" /* yacc.c:1646  */
    {
                (yyval.node) = Create_new_node(INSERT,"insert into name() valuse()");
            }
#line 3008 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1238 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3014 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1239 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3020 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1242 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3026 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1243 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3032 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1246 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3038 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1247 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3044 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1250 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3050 "Grammar.tab.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1251 "Grammar.y" /* yacc.c:1646  */
    {}
#line 3056 "Grammar.tab.c" /* yacc.c:1646  */
    break;


#line 3060 "Grammar.tab.c" /* yacc.c:1646  */
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
#line 1255 "Grammar.y" /* yacc.c:1906  */


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
    Init_stmt_vector();         //初始化全局变量
    parse_getopt(argc,argv);    //解析命令行的参数
    yyparse();                  //解析词法和建立语法树
    Main_mode();                //具体动作
    Del_stmt_vector();          //释放掉所有空间
    return 0;
}
 

void Main_mode()
{
    if(_Global.mode == GET_MODE)
    {
        Str_cut_for_real_alias(_Global.field_name,&_Global.database_name,&_Global.table_alias_name,&_Global.real_field_name);
        Connect_enum_main();
        Show_the_filed_info(_Global.field_name);
    }
    else if(_Global.mode == ALL_MODE)
    {
        Connect_enum_main();
        Show_stmt_info();
    }
    else if(_Global.mode == PHYSICAL_MODE)
    {
        Connect_enum_main();
        Show_all_physical_table();
    }
    else if(_Global.mode == TEST_MODE)
    {
        printf("%s",_Global.ptr_chache->chache);
    }
    else if(_Global.mode == BACK_STMT)
    {
        Connect_enum_main();
        Get_back_stmt(&_stmt);
    }

}


void Init_stmt_vector()
{
    _stmt.vector_stmt = Init_vector(10);
    _Global.count=0;
    _Global.ptr_chache = (chache_stmt*)calloc(sizeof(chache_stmt),1);
    Init_chache_stmt();
}

void Init_chache_stmt()
{
    _Global.ptr_chache->size = STMT_MAX;
    _Global.ptr_chache->now_offset = 0;
    _Global.ptr_chache->chache = (char*)calloc(_Global.ptr_chache->size,1);   
    if(_Global.ptr_chache->chache == NULL)
    {
        exit(0);
    }
}

int Insert_str(char* str)
{
    if( _Global.ptr_chache->now_offset + strlen(str) >= _Global.ptr_chache->size)
    {
        Expend_chache();    
    }
    memcpy(_Global.ptr_chache->chache + _Global.ptr_chache->now_offset,str,strlen(str));
    _Global.ptr_chache->now_offset += strlen(str);
    return _Global.ptr_chache->now_offset;
}

void Expend_chache()
{
    _Global.ptr_chache->chache = (char*)realloc(_Global.ptr_chache->chache,_Global.ptr_chache->size*2);
    if(_Global.ptr_chache->chache == NULL)
    {
        exit(0);
    }
}

void Show_string(_String* string)
{
    int         i;

    for(i = 0;i<string->string_size;i++)
    {
        printf("%c",string->string_ptr[i]);
    }
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
        sprintf(tem->RHS,"%s%d)",tem->RHS,_Global.count);
        tem_struct->field_name = tem;
        _Global.count++;
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
        sprintf(tem->RHS,"%s%d)",tem->RHS,_Global.count);
        tem_struct->obj_name = tem;
        _Global.count++;
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
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
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
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
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
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
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
            sprintf(enum_man->L_child->RHS,"%s%d)",enum_man->L_child->RHS,_Global.count);
            _Global.count++;
            char* tem_name = strchr(enum_man->L_child->RHS,'(');
            Main_struct(enum_man->L_child,tem_name);
        }
        Vector_push_back(select_con->vector_oder_by,enum_man);
    }
}

/*-------------------------打印每一层的所有存储的信息----------------------*/
void Show_stmt_info()
{
    int            i,j,k;
    Tree_Node*     field_physical_info_tem;

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
            

            for(k = 0;k<tem_field->field_physical_info->curr_size;k++)
            {
                field_physical_info_tem = Vetor_get(tem_field->field_physical_info,k);
                printf("实际联系的物理表测试  ： %s  ",field_physical_info_tem->RHS);
            }


            printf("\n");
            // if(tem_field->field_table_info == NULL)
            // {
                
            //     printf("属于该层所有表\t");
            // }
            // else
            // {
            //     printf("属于 : %s \t ",tem_field->field_table_info->RHS);
            // }
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

void Show_all_physical_table()
{
    int            i,j,k;
    Tree_Node*     field_physical_info_tem;

    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        select_info* tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        printf("%s \n",tem_stmt->name);
        for(j=0;j<tem_stmt->vector_field->curr_size;j++)
        {
            field_info* tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
            printf("实际表字段  ：  %20s     实际的物理表  ： ",(tem_field->field_name)->RHS);
            for(k = 0;k<tem_field->field_physical_info->curr_size;k++)
            {
                field_physical_info_tem = Vetor_get(tem_field->field_physical_info,k);
                printf("%30s ",field_physical_info_tem->RHS);
            }
            printf("\n");
        }
        printf("\n\n");
    }

}
/*----------------------------------------------------------------------*/

/*--------------------------查询一个字段实际的物理表----------------------------*/
void Show_the_filed_info()
{
    int             i,j,mode_tem,mode = 0,flag_null = 0,Flag = 0;
    select_info*    tem_stmt;                       //语句的存储结构 
    field_info*     tem_field;                      //字段信息的存储结构
    obj_info*       tem_obj;                        //表信息的存储结构 
    char*           database_name_tem = NULL;       //将拿出来的字段进行拆分之后的存储位置          ##这里没有释放
    char*           table_alias_name_tem = NULL; 
    char*           real_field_name_tem = NULL;

    for(i=0;i<_stmt.vector_stmt->curr_size;i++)
    {
        tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        /*这里会默认从主函数开始匹配你输入的字段*/
        if(strcmp(tem_stmt->name,"MAIN") == 0)                     
        {
            for(j=0;j<tem_stmt->vector_field->curr_size;j++)
            {
                tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,j);
                mode_tem = Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name_tem,&table_alias_name_tem,&real_field_name_tem);
                if(strcmp(real_field_name_tem,_Global.real_field_name) == 0 || strcmp(real_field_name_tem,"*") == 0)
                {
                    if(tem_field->field_table_info == NULL)   //对应全部表
                    {
                        All_table(tem_stmt);
                    }
                    else     //对应该节点的表
                    {
                        if(tem_field->field_table_info->type == SELECT_SELECT)
                        {
                            Single_search_stmt(tem_field->field_table_info->RHS);
                        }
                        else
                            printf("最终物理表 : %s \t",tem_field->field_table_info->RHS);
                    }

                }

            }
        }
    }
}

/*
* 查询 stmt 层的信息，语句层信息
*/
int Single_search_stmt(char* search)    //遇到select_select会调用该函数
{
    int             i;
    select_info*    tem_stmt;
    int             num_of_stmt = _stmt.vector_stmt->curr_size;    //这个是总的select数量

    for(i=0;i<num_of_stmt;i++)
    {
        tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        if( 0 == strcmp(tem_stmt->name,search))
        {
            //找到子查询的所有信息，找到对应的表
            Search_select_info_table(tem_stmt);   //找到这个表之后继续找对应的字段
        }
    }
    return -1;
}

/*
*  查询 select_info 层表信息    //通过全局变量里面的字段存储了所有信息，得到
*/

int Search_select_info_table(select_info* tem_stmt)
{
    int             i,Flag,mode_tem,flag_null = 0;
    obj_info*       tem_obj;
    field_info*     tem_field;  //找到字段对应的表，这里应该 _Global.field_name 里面存储了 字段信息
    char*           database_name_tem = NULL;
    char*           table_alias_name_tem = NULL;
    char*           real_field_name_tem = NULL;  //存储输入的信息
    
    //找到该字段 或者 *  之后拿到 字段的别名的表  如果没有就把这一层所有的表输出

    for(i=0;i<tem_stmt->vector_field->curr_size;i++)
    {
        tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,i);
        mode_tem = Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name_tem,&table_alias_name_tem,&real_field_name_tem);
        if(strcmp(real_field_name_tem,_Global.real_field_name) == 0 || strcmp(real_field_name_tem,"*") == 0)
        {
            if(tem_field->field_table_info == NULL)   //对应全部表
            {
                All_table(tem_stmt);
            }
            else     //对应该节点的表
            {
                if(tem_field->field_table_info->type == SELECT_SELECT)
                {
                    Single_search_stmt(tem_field->field_table_info->RHS);
                }
                else
                    printf("最终物理表 : %s \t",tem_field->field_table_info->RHS);
            }
        }
    }

}

void All_table(select_info* tem_stmt)
{
    int             i,Flag,mode_tem,flag_null = 0;
    obj_info*       tem_obj;
    field_info*     tem_field;  //找到字段对应的表，这里应该 _Global.field_name 里面存储了 字段信息

    //找到该字段 或者 *  之后拿到 字段的别名的表  如果没有就把这一层所有的表输出

    for(i=0;i<tem_stmt->vector_table->curr_size;i++)
    {
        tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,i);               
        if(tem_obj->obj_name->type == SELECT_SELECT)
        {
            Single_search_stmt(tem_obj->obj_name->RHS);
        }
        else
            printf("最终物理表 : %s \t",tem_obj->obj_name->RHS);
    }
}

/*----------------------------------------------------------------------*/
/*将同一层的表 的 字段信息指向他们对应的表  ，这里默认* 会指向所有表*/

void Connect_enum_main()
{   
    int             i=0;
    select_info*    tem_stmt;

    for(i = 0;i < _stmt.vector_stmt->curr_size; i++)
    {
        tem_stmt = Vetor_get(_stmt.vector_stmt,i);
        Connect_field_table(tem_stmt);
    }
}

int Connect_field_table(select_info* tem_stmt)
{
    int             i,size;
    obj_info*       tem_obj;
    field_info*     tem_field;

    size = tem_stmt->vector_field->curr_size;
    for(i = 0;i < size ; i++)
    {
        tem_field = (field_info*)Vetor_get(tem_stmt->vector_field,i);
        tem_field->field_physical_info = Init_vector(10);
        tem_field -> field_table = tem_stmt->vector_table;
        Connect_field_table_child(tem_stmt,tem_field);
    }
    size = tem_stmt->vector_table->curr_size;
    for(i = 0;i < size ; i++)
    {
        tem_obj = (obj_info*)Vetor_get(tem_stmt->vector_table,i);
        tem_obj -> obj_field = tem_stmt->vector_field;
    }
    return 1;
}

int Connect_field_table_child(select_info* tem_stmt,field_info* tem_field)
{
    char*       database_name = NULL;
    char*       table_alias_name = NULL;
    char*       real_field_name = NULL;
    char*       is_l_fun = NULL;
    char*       is_r_fun = NULL;
    int         mode,i = 0;
    obj_info*   tem_obj;

    mode = Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name,&table_alias_name,&real_field_name);

    //如果是函数，就默认用他的别名取查找
    is_l_fun = strchr(tem_field->field_name->RHS,'(');
    is_r_fun = strchr(tem_field->field_name->RHS,')');

    if(
        (tem_field->field_alias != NULL && is_r_fun && is_l_fun && tem_field->field_name->RHS[0]!='(') ||
        (tem_field->field_alias != NULL && is_r_fun && is_l_fun && tem_field->field_name->RHS[1] =='C')     ) 
    {
        free(real_field_name);
        real_field_name = NULL;
        real_field_name = tem_field->field_alias->RHS;
    }

    if(mode == 1)
    {
        tem_field->field_table_info = NULL;
    }
    else
    {
        for(i = 0; i<tem_stmt->vector_table->curr_size ;i++)
        {
            tem_obj = Vetor_get(tem_stmt->vector_table,i);
            if(strcmp(tem_obj -> obj_alias ->RHS,table_alias_name) == 0)
            {
                tem_field->field_table_info = tem_obj->obj_name;
                if(tem_obj->obj_name->type == SELECT_SELECT)
                {
                    Subquery_get_info(tem_obj->obj_name->RHS,real_field_name,tem_field);   //找到该名字的子查询
                }
                else
                {
                    Vector_push_back(tem_field->field_physical_info,tem_obj->obj_name);                   
                }
            }
        }
    }

    if(tem_field->field_table_info == NULL)
    {
        All_table_this_floor(tem_stmt,real_field_name,tem_field);
    }
}


void Subquery_get_info(char* search,char* real_field_name,field_info* save_field)
{
    int             i = 0,j = 0,k = 0,mode = 0,mode_tem = 0,alias_flag = 0;
    int             Flag = 0;
    select_info*    tem_stmt;
    int             num_of_stmt = _stmt.vector_stmt->curr_size;    //这个是总的select数量
    obj_info*       tem_obj;
    field_info*     tem_field;
    char*           database_name_tem = NULL;
    char*           table_alias_name_tem = NULL;
    char*           real_field_name_tem = NULL;  //存储输入的信息        

    //得到原始的字段信息

    for(i=0;i<num_of_stmt;i++)
    {
        tem_stmt = (select_info*)Vetor_get(_stmt.vector_stmt,i);
        if( 0 == strcmp(tem_stmt->name,search))
        {
            //这个为子查询对应的层数
            //匹配该字段
            for(j=0;j<tem_stmt->vector_field->curr_size;j++)
            {
                tem_field = Vetor_get(tem_stmt->vector_field,j);
                mode_tem = Str_cut_for_real_alias(tem_field->field_name->RHS,&database_name_tem,&table_alias_name_tem,&real_field_name_tem);

                if(tem_field->field_alias != NULL && strcmp(tem_field->field_alias->RHS,"NULL") != 0) 
                {
                    free(real_field_name_tem);
                    real_field_name_tem = NULL;
                    real_field_name_tem = tem_field->field_alias->RHS;
                }

                //拿到每一个字段信息的真实名字，和穿进来的比较如果满足和源字段 就匹配相应的表
                
                if(strcmp(real_field_name,real_field_name_tem) == 0 || strcmp("*",real_field_name_tem) == 0)     //如果匹配到相应的表就
                {

                    if(mode_tem == 1)
                    {
                        Flag = 0;
                    }
                    else
                    {
                        
                         for(k=0;k<tem_stmt->vector_table->curr_size;k++)
                         {
                            tem_obj = Vetor_get(tem_stmt->vector_table,k);
                            if( tem_obj->obj_alias != NULL && strcmp(table_alias_name_tem,tem_obj->obj_alias->RHS)==0)
                            {
                                Flag = 1;
                                if(tem_obj->obj_name->type == SELECT_SELECT)
                                {
                                    Subquery_get_info(tem_obj->obj_name->RHS,real_field_name,save_field);   //找到该名字的子查询
                                }
                                else
                                {
                                    Vector_push_back(save_field->field_physical_info,tem_obj->obj_name);                   
                                }
                            }

                         }

                    }

                    if(Flag == 0)
                    {
                        All_table_this_floor(tem_stmt,real_field_name,save_field); 
                    }
                    Flag = 0;
                }
              
            }
        }
    }
}

//匹配所有的表
void All_table_this_floor(select_info* tem_stmt,char* real_field_name,field_info* save_field)
{
    int         k=0;
    obj_info*   tem_obj;

    for(k=0;k<tem_stmt->vector_table->curr_size;k++)
    {
        tem_obj = Vetor_get(tem_stmt->vector_table,k);
        if(tem_obj->obj_name->type == SELECT_SELECT)
        {
            Subquery_get_info(tem_obj->obj_name->RHS,real_field_name,save_field);   //找到该名字的子查询
        }
        else
        {
            Vector_push_back(save_field->field_physical_info,tem_obj->obj_name);                   
        }
    }

}


/*----------------------------------------------------------------------*/
/*field_name 必须有空间  其他不要空间 传出参数 只需要传入一个指针 ，记得最后释放*/
//返回的为 装的个数， a 返回 1  t.a  返回2  liuyu.t.c 返回3
int Str_cut_for_real_alias(char* field_name,char** database_name_cpy,char** table_alias_name_cpy,char** real_field_name_cpy)
{
    char*       tem_ptr = NULL;
    char*       tem_ptr_ptr = NULL;
    char*       table_alias_name = NULL;
    char*       database_name = NULL;
    char*       real_field_name = NULL;


    tem_ptr = strchr(field_name,'.');
    if(tem_ptr != NULL)
        tem_ptr_ptr = strchr(tem_ptr+1,'.');
    if(tem_ptr == NULL)  //处理 a
    {
        real_field_name = (char*)calloc(strlen(field_name)+1,1);
        memcpy(real_field_name,field_name,strlen(field_name)+1);
        database_name = NULL;
        table_alias_name = NULL;

        *database_name_cpy = database_name;
        *table_alias_name_cpy = table_alias_name;
        *real_field_name_cpy = real_field_name;
        return 1;
    }
    else if(tem_ptr != NULL && tem_ptr_ptr == NULL)  //处理 t.a
    {
        table_alias_name = (char*)malloc(tem_ptr-field_name+1);
        memset(table_alias_name ,0,tem_ptr-field_name+1);
        memcpy(table_alias_name,field_name,tem_ptr-field_name);
        
        database_name = NULL;

        real_field_name = (char*)calloc(1,strlen(tem_ptr+1)+1);
        memcpy(real_field_name,tem_ptr+1,strlen(tem_ptr+1));

        *database_name_cpy = database_name;
        *table_alias_name_cpy = table_alias_name;
        *real_field_name_cpy = real_field_name;
        return 2;
    }
    else if(tem_ptr != NULL && tem_ptr_ptr != NULL)  //处理 liuyu.t.a
    {
        database_name = (char*)calloc(tem_ptr-field_name+1,1);
        memcpy(database_name,field_name,tem_ptr-field_name);

        table_alias_name = (char*)calloc(tem_ptr_ptr - tem_ptr,1);
        memcpy(table_alias_name,tem_ptr+1,tem_ptr_ptr - tem_ptr - 1);

        real_field_name = (char*)calloc(strlen(tem_ptr_ptr+1)+1,1);
        memcpy(real_field_name,tem_ptr_ptr + 1,strlen(tem_ptr_ptr + 1));

        *database_name_cpy = database_name;
        *table_alias_name_cpy = table_alias_name;
        *real_field_name_cpy = real_field_name;
        return 3;
    }
    // if(table_alias_name)
    //     printf("Table : %s ",table_alias_name);
    // if(database_name)
    //     printf("Database : %s ",database_name);
    // if(real_field_name)
    //     printf("Field ： %s ",real_field_name);
}

/*----------------------------------------------------------------------*/
int parse_getopt(int argc,char** argv)
{
    int opt = 0;

    if(argc<2)
    {
        usage();
        exit(0);
    }

    struct option opt_choose[] =
            {
                    {"getinfo",1,NULL,'g'},
                    {"all",0,NULL,'a'},
                    {"physical_mode",0,NULL,'p'},
                    {"file",1,NULL,'f'},
                    {"test",0,NULL,'t'},
                    {"back",0,NULL,'b'},
            };

    while ((opt = getopt_long(argc,argv,"g:apf:bt",opt_choose,NULL))!=-1)
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
            case 'p':
                _Global.mode = PHYSICAL_MODE;
                break;
            case 'f':
                _Global.mode = ALL_MODE;
                _Global.file_name = optarg;
                break;
            case 't':
                _Global.mode = TEST_MODE;
                break;
            case 'b':
                _Global.mode = BACK_STMT;
                break;
            default:
                usage();
                exit(0);
                break;
        }
    }

    if(_Global.file_name == NULL)
    {
        usage();
        exit(0);
    }
    else
    {
        yyin = fopen(_Global.file_name,"r");
    }

    return;
}

void usage()
{
    printf("-f  <FILE>              --file       <FILE>                指定读入sql的文件名称\n");
    printf("-p                      --physical                         查看所有的字段和其对应的物理表\n");
    printf("-a                      --all                              将所有的语句分层显示，对应关系显示\n");
    printf("-g  <FIELD>             --getinfo    <FIELD>               查找输入字段对应的物理表\n");
}

/*-------------------------还原语句---------------------------------*/

void Get_back_stmt(stmt* back_stmt)
{
    c_vector*           main_select_info = Init_vector(10);
    c_vector*           union_stmt = Init_vector(10);
    select_info*        main_select = NULL;
    int                 i = 0;
    u_int64_t           stmt_size = 0;
    char*               stmt_stmt = NULL;
    char**               tem_stmt = NULL;

    //拿到每一个mian的函数开始
    Find_main(back_stmt,main_select_info);
    for(i = 0;i<main_select_info->curr_size;i++)
    {
        main_select = Vetor_get(main_select_info,i);
        stmt_size += Show_select_info(main_select,union_stmt,back_stmt);    //让这个函数返回这个语句的大小
    }

    if(union_stmt->curr_size < 1)   //容错
    {
        return;
    }

    stmt_stmt = (char*)malloc(stmt_size+7*(union_stmt->curr_size-1)+10);
    tem_stmt = Vetor_get(union_stmt,0);
    sprintf(stmt_stmt,"%s",*tem_stmt);
    for(i = 1;i<union_stmt->curr_size;i++)
    {
        tem_stmt = (char**)Vetor_get(union_stmt,i);
        sprintf(stmt_stmt,"%s UNION %s",stmt_stmt,*tem_stmt);
    }

    printf("原来的语句 ： %s\n",stmt_stmt);
}


void Find_main(stmt* back_stmt,c_vector* main_select_info)
{
    int             i = 0;
    select_info*    tem_stmt;

    for(i=0;i<back_stmt->vector_stmt->curr_size;i++)
    {
        tem_stmt = Vetor_get(back_stmt->vector_stmt,i);
        if(strcmp(tem_stmt->name,"MAIN") == 0)
        {
            Vector_push_back(main_select_info,tem_stmt);
        }
    }
}


int Show_select_info(select_info* main_select,c_vector* union_stmt,stmt* back_stmt)
{
    u_int64_t       stmt_size = 0;
    int             i = 0;
    char*           field = NULL;
    char*           opt = NULL;
    char*           table = NULL;
    char*           where = NULL;
    char*           group = NULL;
    char*           having = NULL;
    char*           order = NULL;
    char*           stmt = (char*)calloc(1,STMT_MAX);  //默认一条语句最大1M
    field_info*     tem_field = NULL;
    obj_info*       tem_obj = NULL;
    Tree_Node*      tem_node;
    u_int64_t       tem_size = 0;

    sprintf(stmt,"SELECT");
    for(i = 0 ;i<main_select->vector_opt->curr_size;i++)
    {        
        tem_node = Vetor_get(main_select->vector_opt,i);
        sprintf(stmt,"%s %s",stmt,tem_node->RHS);
    }

    if(main_select->vector_field->curr_size>=1)
    {
        tem_field = Vetor_get(main_select->vector_field,0);
     
        if(tem_field->field_name->type == SELECT_SELECT)
        {
            sprintf(stmt,"%s (%s)",stmt,Get_subquery_stmt(tem_field->field_name->RHS,back_stmt));
        }
        else
        {
            sprintf(stmt,"%s %s",stmt,tem_field->field_name->RHS);
        }

        if(tem_field->field_alias != NULL && strcmp(tem_field->field_alias->RHS,"NULL") != 0)
        {
            sprintf(stmt,"%s %s",stmt,tem_field->field_alias->RHS);
        }
    }
    for(i = 1 ;i<main_select->vector_field->curr_size;i++)
    {
        tem_field = Vetor_get(main_select->vector_field,i);

        if(tem_field->field_name->type == SELECT_SELECT)
        {
            sprintf(stmt,"%s , (%s)",stmt,Get_subquery_stmt(tem_field->field_name->RHS,back_stmt));
        }
        else
        {
            sprintf(stmt,"%s , %s",stmt,tem_field->field_name->RHS);
        }
     
        if(tem_field->field_alias != NULL && strcmp(tem_field->field_alias->RHS,"NULL") != 0)
        {
            sprintf(stmt,"%s %s",stmt,tem_field->field_alias->RHS);
        }
    }

    sprintf(stmt,"%s FROM",stmt);

    if(main_select->vector_table->curr_size>=1)
    {
        tem_obj = Vetor_get(main_select->vector_table,0);


        if(tem_obj->obj_condition != NULL && strcmp(tem_obj->obj_condition->RHS,"NULL") != 0)
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s LEFT JOIN (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s LEFT JOIN %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }

            sprintf(stmt,"%s %s",stmt,tem_obj->obj_condition->RHS);
        }

        else
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }
        }
        
    }
    for(i = 1 ;i<main_select->vector_table->curr_size;i++)
    {
        tem_obj = Vetor_get(main_select->vector_table,i);

        if(tem_obj->obj_condition != NULL && strcmp(tem_obj->obj_condition->RHS,"NULL") != 0)
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s LEFT JOIN (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s LEFT JOIN %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }

            sprintf(stmt,"%s %s",stmt,tem_obj->obj_condition->RHS);
        }

        else
        {
            if(tem_obj->obj_name->type == SELECT_SELECT)
            {
                sprintf(stmt,"%s (%s)",stmt,Get_subquery_stmt(tem_obj->obj_name->RHS,back_stmt));
            }
            else
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_name->RHS);
            }

            if(tem_obj->obj_alias != NULL && strcmp(tem_obj->obj_alias->RHS,"NULL") != 0)
            {
                sprintf(stmt,"%s %s",stmt,tem_obj->obj_alias->RHS);
            }
        }
    }

    for(i = 0 ;i<main_select->vector_where->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_where,i);
         sprintf(stmt,"%s WHERE %s",stmt,tem_node->RHS);
    }

    for(i = 0 ;i<main_select->vector_group_by->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_group_by,i);
         sprintf(stmt,"%s GROUP BY %s",stmt,tem_node->RHS);
    }

    for(i = 0 ;i<main_select->vector_having->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_having,i);
         sprintf(stmt,"%s HAVING %s",stmt,tem_node->RHS);
    }
    for(i = 0 ;i<main_select->vector_oder_by->curr_size;i++)
    {
         tem_node = Vetor_get(main_select->vector_oder_by,i);
         sprintf(stmt,"%s ODER　BY %s",stmt,tem_node->RHS);
    }


    Vector_push_back(union_stmt,&stmt);
    return strlen(stmt);
}


char* Get_subquery_stmt(char* search,stmt* back_stmt)
{
    c_vector*           main_select_info = Init_vector(10);
    c_vector*           union_stmt = Init_vector(10);
    select_info*        main_select = NULL;
    int                 i = 0;
    u_int64_t           stmt_size = 0;
    char*               stmt_stmt = NULL;
    char**               tem_stmt = NULL;

    //拿到每一个mian的函数开始
    Find_sub(back_stmt,main_select_info,search);
    for(i = 0;i<main_select_info->curr_size;i++)
    {
        main_select = Vetor_get(main_select_info,i);
        stmt_size += Show_select_info(main_select,union_stmt,back_stmt);    //让这个函数返回这个语句的大小
    }

    if(union_stmt->curr_size < 1)   //容错
    {
        return;
    }

    stmt_stmt = (char*)malloc(stmt_size+7*(union_stmt->curr_size-1)+10);
    tem_stmt = Vetor_get(union_stmt,0);
    sprintf(stmt_stmt,"%s",*tem_stmt);
    for(i = 1;i<union_stmt->curr_size;i++)
    {
        tem_stmt = (char**)Vetor_get(union_stmt,i);
        sprintf(stmt_stmt,"%s UNION %s",stmt_stmt,*tem_stmt);
    }

    return stmt_stmt;
}


void Find_sub(stmt* back_stmt,c_vector* main_select_info,char* search)
{
    int             i = 0;
    select_info*    tem_stmt;

    for(i=0;i<back_stmt->vector_stmt->curr_size;i++)
    {
        tem_stmt = Vetor_get(back_stmt->vector_stmt,i);
        if(strcmp(tem_stmt->name,search) == 0)
        {
            Vector_push_back(main_select_info,tem_stmt);
        }
    }
}

