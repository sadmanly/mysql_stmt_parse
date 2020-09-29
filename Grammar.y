%{
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
%}

%union
{
    struct Tree_Node* node;
    char* strval;
}

%left EQ AND OR IN NOT LIKE  
%left '*' '-' '/' '+' '.' 
  /*select_opt 的记号的声明和节点的类型声明*/
%token ALL DISTINCT DISTINCTROW STRAIGHT_JOIN SQL_NO_CHACHE SQL_CALC_FOUND_ROWS SQL_SMALL_RESULT SQL_BIG_RESULT SQL_BUFFER_RESULT 
%type<node> ALL DISTINCT DISTINCTROW STRAIGHT_JOIN SQL_NO_CHACHE SQL_CALC_FOUND_ROWS SQL_SMALL_RESULT SQL_BIG_RESULT SQL_BUFFER_RESULT 

  /*处理用户自定义变量 和 处理 @@ 系统变量的问题*/
%token SYSTEM_CALL_VARIABLE USER_CALL_VARIABLE
%type<strval> SYSTEM_CALL_VARIABLE USER_CALL_VARIABLE
 /*处理*/
%token LIKE


%token SELECT HIGH_PRIORITY  FROM PARTITION WHERE GROUP
%token BY HAVING WINDOW ORDER LIMIT FOR JOIN INNER CROSS ON USING LEFT RIGHT OUTER 
%token NATURAL AND OR NOT EXISTS UNION 
 /*声明token*/
%token INSERT UPDATE CREATE
%token ID SET 
%token VALUES EQ   
%token DATABASE 
%token AS NAME
%token ASC DESC INTO NUM WITH ROLLUP  
 /*函数关键字声明*/
%token CONCAT CASE THEN WHEN END ELSE FLOOR
 /*函数RHS声明*/
%type<node> case_when_fun when_then
%type<strval> NAME NUM EQ
%type<node> SQLS SQL update_exp create_exp select_exp select_expr_stmt insert_exp
%type<node> select_opts select_expr_list  
%type<node> select_expr opt_as_alias
%type<node> table_references table_reference 
%type<node> table_factor join_table 
%type<node> table_subquery opt_join_condition join_condition
%type<node> opt_left_or_right left_or_right opt_outer opt_inner_cross 
%type<node> index_hint opt_where where_condition val_list opt_group_by
%type<node> groupby_list opt_asc_desc opt_with_rollup opt_having opt_order_by end
%type<node> opt_limit opt_into_list column_list key_value_exp id_comma_exp value_key_exp id2_comma_exp
%start SQLS
%%

SQLS:SQL ';' 
    {
        $$ = $1;
        _Global.root = $$;
    }
    | SQLS  SQL ';' 
    {   
        $$ = $2;
        $1->R_child = $2;
    }
    ;

SQL: 
    {
        $$ = Create_new_node(0,"SELECT T 语句");
    }
    |   insert_exp 
    {
        $$ = Create_new_node(INSERT,"INSERT");
        $$->L_child = $1; 
    }
    |   update_exp  
    {
        printf("\tstat : update\n");
    }
    |   create_exp  
    {
        printf("\tstat : create\n");
    }
    |   select_exp  
    {
        $$ = Create_new_node(SELECT,"SELECT");
        $$->L_child = $1;
        Main_struct($1,"MAIN");
    }
    ;

select_exp:select_expr_stmt 
          {
                $$ = Create_new_node(0,"\nBEGIN");
                $$->L_child = $1;
                $1->Parent = $$; 
          }
          | select_exp UNION select_expr_stmt 
          {
                $$ = Create_new_node(0,"BEGIN 语句 union");
                $$->L_child = $1;
                $1->Parent = $$; 
                $1->R_child = $3;
                $3->Parent = $1;
          }
          | select_exp UNION ALL select_expr_stmt 
          {
                $$ = Create_new_node(0,"BEGIN 语句 union");
                $$->L_child = $1;
                $1->Parent = $$; 
                $1->R_child = $4;
                $4->Parent = $1;
          }
          ;
          
select_expr_stmt:SELECT select_opts select_expr_list end 
                {
                    char con[500];
                    sprintf(con,"SELECT %s %s",
                        $2->RHS,
                        $3->RHS     
                        );
                    $$ = Create_new_node(0,con);
                    $4->R_child = $2;
                    $2->Parent = $4;
                    $2->R_child = $3;
                    $3->Parent = $2;
                    $$->L_child = $4;
                    $4->Parent = $$;
                } 
          | SELECT select_opts select_expr_list FROM table_references opt_where opt_group_by opt_having opt_order_by opt_limit opt_into_list end
          {
                char con[500];
                sprintf(con,"SELECT %s %s FROM %s %s %s %s %s %s %s",
                    $2->RHS,
                    $3->RHS,
                    $5->RHS,
                    $6->RHS,
                    $7->RHS,
                    $8->RHS,
                    $9->RHS,
                    $10->RHS,
                    $11->RHS
                    );
                $$ = Create_new_node(0,con);
                $12->R_child = $2;
                $2->Parent = $12;

                $2->R_child = $3;
                $3->Parent = $2;
                $3->R_child = $5; 
                $5->Parent = $3;

                $5->R_child = $6; 
                $6->Parent = $5;

                $6->R_child = $7; 
                $7->Parent = $6;

                $7->R_child = $8; 
                $8->Parent = $7;

                $8->R_child = $9; 
                $9->Parent = $8;

                $9->R_child = $10; 
                ($10)->Parent = $9;

                $10->R_child = $11; 
                $11->Parent = $10;

                $$->L_child = $12;
                $12->Parent = $$;
          }
          ;

   /*-- 处理select语句的选项部分，这里没有限制先后和出现的次数 --*/
   /*-- select DISTINCTROW SQL_SAMLL_RESULT * from t1 --*/
   /* SELECT select_opts select_expr_list FROM table_references opt_where opt_group_by opt_having opt_order_by opt_limit opt_into_list {printf("规约成功");} */

end: 
   {
       $$ = Create_new_node(END,"SELECT BEGIN : ");
   }
   ;
select_opts:  {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
              } 
          | select_opts ALL 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts DISTINCT 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts DISTINCTROW 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts STRAIGHT_JOIN 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts SQL_SMALL_RESULT 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts SQL_BIG_RESULT 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt3");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts SQL_BUFFER_RESULT 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts SQL_NO_CHACHE 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          | select_opts SQL_CALC_FOUND_ROWS 
          {
                $$ = Create_new_node(SELECT_OPT_BEGIN,"select_opt");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
          }
          ;

  /*-- 处理字段信息的列表 以‘,’为分界，有可能为*的情况 --*/
  /*-- select * from t1 和 select a,b,c,d from t1 的情况  --*/

select_expr_list: select_expr 
                {
                    $$ = Create_new_node(FIELD_INFO_BEGIN,"field_info_begin");
                    $$->L_child = $1;
                    $1->Parent = $$;
                }
                | select_expr_list ',' select_expr 
                {
                    $$ = Create_new_node(FIELD_INFO_BEGIN,"field_info_begin");
                    $$->L_child = $1;
                    $1->Parent = $$;
                    $1->R_child = $3;
                    $3->Parent = $1;
                }
                | '*'
                {
                    $$ = Create_new_node(FIELD_NAME,"*");
                }
                ;
 /*-- 处理字段信息总可能含有别名的情况 --*/
 /*-- select a as liuyu,b as cui from t1 --*/ 
 /*-- 这个expr里面可能是嵌套子查询的 --*/
 /*-- 这里已经可以确定是字段info--*/
select_expr: where_condition opt_as_alias 
           {
              $$ = Create_new_node(FIELD_NODE,"field");
              $$->L_child = $1;
              $1->Parent = $$;
              $1->R_child = $2;
              $2->Parent = $1;
           }
           ;
 /*-- 字段取别名的方法主要是 AS NAME 或者 直接 NAME 这 2 种情况 --*/
 /*-- 给字段信息取别名的方法可以加AS 也可以不加AS 直接跟在名字后面--*/
 /*-- select a liuyu, b cui from t1 --*/ 

opt_as_alias: 
             AS NAME 
            {
                $$ = Create_new_node(ALIAS_NAME,$2); 
                free($2);
            }
            | NAME 
            {
                $$ = Create_new_node(ALIAS_NAME,$1); 
                free($1);
            }
            |
            {
                $$ = Create_new_node(ALIAS_NAME,"NULL"); 
            }
            ;

 /*-- 处理字段里面可能继续含有子查询的情况, 没有考虑子查询的限制，现在是粗略的认为子查询就是个信息select语句 --*/
 /* 处理case when 函数的问题 */

case_when_fun: when_then 
             {
                $$ = Create_new_node(2,$1->RHS); 
                $$->L_child = $1;
                $1->Parent = $$;
             }
             | case_when_fun when_then 
             {
                char* con=(char*)malloc(strlen($1->RHS)+strlen($2->RHS)+10);
                sprintf(con,"%s %s",$1->RHS,$2->RHS);
                $$ = Create_new_node(2,con); 
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
                free(con);
             }
             ;

when_then: WHEN where_condition THEN where_condition 
         {
                char* con=(char*)malloc(strlen($2->RHS)+strlen($4->RHS)+20);
                sprintf(con,"WHEN　%s THEN %s",$2->RHS,$4->RHS);
                $$ = Create_new_node(2,con); 
                $$->L_child = $2;
                $2->Parent = $$;
                $2->R_child = $4;
                $4->Parent = $2;
                free(con);
         }
         | ELSE where_condition
         {
                char* con=(char*)malloc(strlen($2->RHS)+10);
                sprintf(con,"ELSE %s",$2->RHS);
                $$ = Create_new_node(2,con); 
                $$->L_child = $2;
                $2->Parent = $$;
                free(con);
         }
         ;
 /*-- 处理CONCAT 函数的问题--*/


 /*-- 左递归处理单表和多表的情况--*/
 
table_references: table_reference 
                {
                   $$ = Create_new_node(TABLE_INFO,"表信息");
                   $$->L_child = $1;
                   $1->Parent = $$;
                }
                | table_references ',' table_reference
                {
                   $$ = Create_new_node(TABLE_INFO,"表信息");
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                } 
                ;
 /*
 * 处理连接查询的问题
 * >内连接 INNER JOIN (等值连接--包括重复列) (自然连接--等值连接除去重复列) (自连接,涉及到的表是同一个表的情况)
 *   内连接只返回满足连接条件的数据行，外连接不只列出与连接条件相匹配的行，而是列出左表（左外连接时）、右表（右外连接时）
 *   或两个表（全外连接时）中所有符合搜索条件的数据行。外连接分为左外连接、右外链接、全外连接三种。
 * >外连接 RIGHT [OUTER] JOIN | FULL [OUTER] JOIN | LEFT [OUTER] JOIN
 * >交叉连接 CROSS JOIN 两个表做笛卡尔积，得到的结果集的行数是两个表的行数的乘积
 */
 /*-- 单表情况的处理 分为join 和普通-*/
table_reference: table_factor {
                                $$ = Create_new_node(NORMAL_TABLE,"Normal table");
                                $$->L_child = $1;
                                $1->Parent = $$;
                              //  Enum_tree_node_deep($$);
                              //  printf("%s  %d\n",$$->RHS,$$->type);
                              }
               | join_table 
               {
                   $$ = Create_new_node(JOIN_TABLE,"JOIN表");
                   $$->L_child = $1;
                   $1->Parent = $$;
               }
               ;

 /*-- 处理普通不含Join的表 --*/
 /*-- select liuyu.a from l1 as liuyu 或者 select liuyu.a from liuyu.l1  刘宇是数据库名字 --*/
 /*-- 这里可以包括子查询,子查询查完后的结果开始--*/
 /*-- 这里甚至可以包括 前面的 table_references?????  不太理解 留坑--*/
 /*-- 这里的索引不太理解## 留坑--*/

table_factor: NAME opt_as_alias index_hint { 
                                             $$ = Create_new_node(TABLE_NAME,$1);
                                             free($1);
                                             $$->L_child = $2;
                                             $2->Parent = $$;
                                             $2->R_child = $3;
                                             $3->Parent = $2;
                                        //   printf("%s  %d\n",$$->RHS,$$->type);
                                            }
            | NAME '.' NAME opt_as_alias index_hint 
            {
                char con[200];
                sprintf(con,"%s.%s",$1,$3);
                free($1); free($3);
                $$ = Create_new_node(TABLE_NAME,con);
                $$->L_child = $4;
                $4->Parent = $$;
                $4->R_child = $5;
                $5->Parent = $4;
            } 
            | table_subquery opt_as_alias
            {
                $$ = Create_new_node(TABLE_SUB,"table_sub");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
            }
            | '(' table_references ')'
            {
                $$ = Create_new_node(TABLE_REFERENCE,"为(table_references)");
                $$->L_child = $2;
                $2->Parent = $$;
            }
            | '(' where_condition ')' opt_as_alias index_hint
            {
                $$ = Create_new_node(TABLE_REFERENCE,"为(table_references)");
                $$->L_child = $2;
                $2->Parent = $$;
                $2->R_child = $4;
                $4->Parent = $2;
                $4->R_child = $5;
                $5->Parent = $4;
            }
            ;


table_subquery: '(' select_exp ')' 
              {
                $$ = Create_new_node(SELECT_SELECT,"(子查询");
                $$->L_child = $2;
                $2->Parent = $$;
              }
              ;

 /*-- 处理含JOIN表的情况 --*/
 /*-- join 留坑--*/
 /*-- 为啥这里会有个递归呢?--*/
join_table: table_reference opt_inner_cross JOIN table_factor opt_join_condition 
          {
                $$ = Create_new_node(JOIN_TABLE_1,$5->RHS);
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
                $2->R_child = $4;
                $4->Parent = $2;
                $4->R_child = $5;
                $5->Parent = $4;
          }
          | table_reference STRAIGHT_JOIN table_factor 
          {
                $$ = Create_new_node(JOIN_TABLE_2,"Join表的选项 JION2");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $3;
                $3->Parent = $1;
          }
          | table_reference STRAIGHT_JOIN table_factor ON where_condition 
          {
                $$ = Create_new_node(JOIN_TABLE_3,"Join表的选项 STRIGHT_JOIN ON3");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $3;
                $3->Parent = $1;
                $3->R_child = $5;
                $5->Parent = $3;

          }
          | table_reference left_or_right opt_outer JOIN table_factor join_condition 
          {
                $$ = Create_new_node(JOIN_TABLE_4,$6->RHS);
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
                $2->R_child = $3;
                $3->Parent = $2;
                $3->R_child = $5;
                $5->Parent = $3;
                $5->R_child = $6;
                $6->Parent = $5;
          }
          | table_reference NATURAL opt_left_or_right JOIN table_factor 
          {
                $$ = Create_new_node(JOIN_TABLE_5,"Join表的选项 NATURAL5");
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $3;
                $3->Parent = $1;
                $3->R_child = $5;
                $5->Parent = $3;
          }
          ;

opt_left_or_right: LEFT opt_outer 
                 {
                    $$ = Create_new_node(LEFT,"LEFT");
                    $$->L_child = $2;
                    $2->Parent = $$;
                 }
                 | RIGHT opt_outer 
                 {
                    $$ = Create_new_node(RIGHT,"RIGHT");
                    $$->L_child = $2;
                    $2->Parent = $$;
                 }
                 |
                 {
                    $$ = Create_new_node(RIGHT,"NULL");
                 }
                 ;

left_or_right: LEFT 
             {
               $$ = Create_new_node(LEFT,"LEFT");
             }
             | RIGHT 
             {
               $$ = Create_new_node(RIGHT,"RIGHT");
             }
             ;

opt_outer: 
         {
            $$ = Create_new_node(1,"NULL");
         }
         | OUTER 
         {
            $$ = Create_new_node(1,"OUTER");
         }
         ;

opt_inner_cross: 
               {
                  $$ = Create_new_node(1,"NULL");
               }
               | INNER 
               {
                  $$ = Create_new_node(1,"INNER");
               }
               | CROSS 
               {
                  $$ = Create_new_node(1,"CROSS");
               } 
               ;

opt_join_condition: 
                  {
                    $$ = Create_new_node(1,"NULL");
                  }
                  | join_condition 
                  {
                    $$ = Create_new_node(JOIN_CONDITION,$1->RHS);
                    $$->L_child = $1;
                    $1->Parent = $$;
                  }
                  ;

join_condition: ON where_condition 
              {
                  char* con = (char*)malloc(strlen($2->RHS)+1);
                  sprintf(con,"ON %s",$2->RHS);
                  $$ = Create_new_node(JOIN_CONDITION,con);
                  $$->L_child = $2;
                  $2->Parent = $$;
                  free(con);
              }
              | USING 
              {
                  $$ = Create_new_node(JOIN_CONDITION,"USING");
              }
              ;


 /*-- 处理索引的问题 留坑 --*/

index_hint: 
          {
              $$ = Create_new_node(1,"index NULL");
          }
          ;

opt_where: 
         {
            $$ = Create_new_node(1,"NO WHERE");
         }
         | WHERE where_condition 
         {
            $$ = Create_new_node(OPT_WHERE,$2->RHS);
            $$->L_child = $2;
            $2->Parent = $$;
         }
         ;

 /*-- 条件表达式 --*/
where_condition:  where_condition EQ where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($2)+strlen($3->RHS)+10);
                   sprintf(con,"%s %s %s",$1->RHS,$2,$3->RHS);

                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition AND where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10);
                   sprintf(con,"%s AND %s",$1->RHS,$3->RHS);

                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }

                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition OR where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10);
                   sprintf(con,"%s OR %s",$1->RHS,$3->RHS);

                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }

                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition '-' where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10);
                   sprintf(con,"%s - %s",$1->RHS,$3->RHS);
                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition '+' where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10);
                   sprintf(con,"%s + %s",$1->RHS,$3->RHS);
                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition '*' where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10);
                   sprintf(con,"%s * %s",$1->RHS,$3->RHS);
                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition '/' where_condition 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10);
                   sprintf(con,"%s / %s",$1->RHS,$3->RHS);

                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $3;
                   $3->Parent = $1;
                   free(con);
               }
               | where_condition IN '(' select_exp ')' 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+20);
                   sprintf(con,"%s IN (子查询",$1->RHS);
                   $$ = Create_new_node(SELECT_SELECT,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $4;
                   $4->Parent = $1;
                   free(con);
               }
               | where_condition NOT IN '(' select_exp ')' 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+20);
                   sprintf(con,"%s NOT IN (子查询",$1->RHS);
                   $$ = Create_new_node(SELECT_SELECT,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $5;
                   $5->Parent = $1;
                   free(con);
               }
               | where_condition IN '(' val_list ')' 
               {
                   char* con = (char*)malloc(strlen($4->RHS)+strlen($1->RHS)+20);
                   sprintf(con,"%s IN (%s)",$1->RHS,$4->RHS);
                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $4->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $4;
                   $4->Parent = $1;
                   free(con);
               }
               | where_condition NOT IN '(' val_list ')' 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($5->RHS)+20);
                   sprintf(con,"%s NOT IN (%s)",$1->RHS,$5->RHS);
                   int tem_type=1;
                   if($1->type == SELECT_SELECT || $5->type == SELECT_SELECT)
                   {
                       tem_type = SELECT_SELECT;
                   }
                   $$ = Create_new_node(tem_type,con);
                   $$->L_child = $1;
                   $1->Parent = $$;
                   $1->R_child = $5;
                   $5->Parent = $1;
                   free(con);
               }
               | '(' where_condition ')' 
               {
                   char* con = (char*)malloc(strlen($2->RHS)+10);
                   sprintf(con,"( %s )",$2->RHS);
                   $$ = Create_new_node($2->type,con);
                   $$->L_child = $2;
                   $2->Parent = $$;
                   free(con);
               }
               | EXISTS '(' select_exp ')'
               {
                   $$ = Create_new_node(SELECT_SELECT,"EXISTS (子查询");
                   $$->L_child = $3;
                   $3->Parent = $$;
               }
               | NAME 
               {
                   $$ = Create_new_node(1,$1);
                   free($1);
               }
               | NAME '.' '*' 
               {
                   char con[200];
                   sprintf(con,"%s.*",$1);
                   $$ = Create_new_node(1,con);
                   free($1);
               }
               | NUM 
               {
                   $$ = Create_new_node(1,$1);
                   free($1);
               }
               | NAME '.' NAME 
               {
                   char con[200];
                   sprintf(con,"%s.%s",$1,$3);
                   $$ = Create_new_node(1,con);
               }
               | CASE case_when_fun END
               {
                   char* con = (char*)malloc(strlen($2->RHS)+10);
                   sprintf(con,"(CASE %s END)",$2->RHS);
                   $$ = Create_new_node(2,con); 
                   $$->L_child = $2;
                   $2->Parent = $$;
                   free(con);
               }
               | where_condition LIKE NAME 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($3)+10);
                   sprintf(con,"%s LIKE %s",$1->RHS,$3);
                   $$ = Create_new_node($1->type,con); 
                   $$->L_child = $1;
                   $1->Parent = $$;
                   free(con);
                   free($3);
               }
               | where_condition NOT LIKE NAME 
               {
                   char* con = (char*)malloc(strlen($1->RHS)+strlen($4)+10);
                   sprintf(con,"%s NOT LIKE %s",$1->RHS,$4);
                   $$ = Create_new_node($1->type,con); 
                   $$->L_child = $1;
                   $1->Parent = $$;
                   free(con);
                   free($4);
               }
               | '(' select_exp ')'
               {
                   $$ = Create_new_node(SELECT_SELECT,"(子查询"); 
                   $$->L_child = $2;
                   $2->Parent = $$;
               }
               ; 
 /*-- 处理系统变量的问题 --*/
where_condition: SYSTEM_CALL_VARIABLE 
               {
                   $$ = Create_new_node(SYSTEM_CALL_VARIABLE,$1); 
               }
               | USER_CALL_VARIABLE 
               {
                   $$ = Create_new_node(USER_CALL_VARIABLE,$1); 
               }
               ;

 /*-- 一般函数 --*/
where_condition: NAME '(' val_list ')' 
               {
                //    char con[10000];
                //   printf("%d ",strlen($1)+strlen($3->RHS)+30);
                   char* con = (char*)malloc(strlen($3->RHS)+strlen($1)+30); 
                   sprintf(con,"%s(%s)",$1,$3->RHS);
                   $$ = Create_new_node($3->type,con);
                   free($1);
                   free(con);
                   $$->L_child = $3;
                   $3->Parent = $$;
               }
               ; 

val_list: where_condition 
        {
            $$ = Create_new_node($1->type,$1->RHS);
            $$->L_child = $1;
            $1->Parent = $$;
        }
        | val_list ',' where_condition 
        {
            
            char* con = (char*)malloc(strlen($1->RHS)+strlen($3->RHS)+10); 
            sprintf(con,"%s , %s",$1->RHS,$3->RHS);
            int tem_type=1;
            if($1->type == SELECT_SELECT || $3->type == SELECT_SELECT)
            {
                tem_type = SELECT_SELECT;
            }
            $$ = Create_new_node(tem_type,con);
            $$->L_child = $1;
            $1->Parent = $$;
            $1->R_child = $3;
            $3->Parent = $1;
            free(con);
        }
        | '*'
        {
            $$ = Create_new_node(1,"*");
        }
        ;


 /* 这里简单的认为 groub_by 后面直接跟字段名字或者 子查询*/
opt_group_by: 
            {
                $$ = Create_new_node(0,"opt_group_by NULL");
            }
            | GROUP BY groupby_list opt_with_rollup 
            {
                char con[500];
                int c = ($4->type == 0)?0:1;
                if (c)
                {
                    sprintf(con,"%s %s",$3->RHS,$4->RHS);
                }
                else 
                {
                    sprintf(con,"%s",$3->RHS);                
                }
                $$ = Create_new_node(OPT_GROUP_BY,con);
                // printf("%s",con);
                $$->L_child = $3;
                $3->Parent = $$;
                $3->R_child = $4;
                $4->Parent = $3;
            }
            ;

groupby_list: where_condition opt_asc_desc 
            {
                char* con=(char*)malloc(strlen($1->RHS)+20);
                int c = $2->type;
                if(c)
                sprintf(con,"%s %s",$1->RHS,$2->RHS);
                else sprintf(con,"%s",$1->RHS);
                $$ = Create_new_node($1->type,con);
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $2;
                $2->Parent = $1;
                free(con);
            }
            | groupby_list ',' where_condition opt_asc_desc 
            {
                char* con=(char*)malloc(strlen($1->RHS)+20+strlen($3->RHS));
                int c = $4->type;
                if(c)
                {
                    sprintf(con,"%s , %s %s",$1->RHS,$3->RHS,$4->RHS);
                }
                else sprintf(con,"%s , %s",$1->RHS,$3->RHS);
                $$ = Create_new_node(1,con);
                $$->L_child = $1;
                $1->Parent = $$;
                $1->R_child = $3;
                $3->Parent = $1;
                $3->R_child = $4;
                $4->Parent = $3;
                free(con);
            }
            ;

opt_asc_desc: 
            {
               $$ = Create_new_node(0,"opt_asc_desc NULL");
            }
            | ASC 
            {
               $$ = Create_new_node(1,"ASC");
            }
            | DESC 
            {
               $$ = Create_new_node(1,"DESC");
            }
            ;

opt_with_rollup: 
              {
                $$ = Create_new_node(0,"opt_with_rollup NULL");
              }
              | WITH ROLLUP 
              {
                $$ = Create_new_node(1,"WHIT ROLLUP");
              }
              ;

opt_having:
          {
             $$ = Create_new_node(1,"opt_having NULL");
          }
          | HAVING where_condition 
          {
             $$ = Create_new_node(HAVING,$2->RHS);
             $$->L_child = $2;
             $2->Parent = $$;
          }
          ;

opt_order_by: 
            {
                $$ = Create_new_node(0,"opt_order_by NULL");
            }
            | ORDER BY groupby_list 
            {
                $$ = Create_new_node(ORDER,$3->RHS);
                $$->L_child = $3;
                $3->Parent = $$;
            }
            ;
 /*-- 这里简单认为 limit后面的是数字--*/
opt_limit: 
         {
             $$ = Create_new_node(1,"opt_limit NULL");
         }
         | LIMIT NUM 
         {
            char con[100];
            sprintf(con,"LIMIT %s",$2);
            free($2);
            $$ = Create_new_node(1,con);
         } 
         | LIMIT NUM ',' NUM 
         {
            char con[100];
            sprintf(con,"LIMIT %s.%s",$2,$4);
            free($2); free($4);
            $$ = Create_new_node(1,con);
         }
         ;

opt_into_list: 
             {
                $$ = Create_new_node(1,"opt_into_list NULL");
             }
             | INTO column_list 
             {
                $$ = Create_new_node(1,"INTO");
                $$->L_child = $2;
                $2->Parent = $$;
             }
             ;

column_list:NAME 
           {
                $$ = Create_new_node(1,$1);
                free($1);
           }
           | column_list ',' NAME 
           {
                $$ = Create_new_node(1,$3);
                free($3);
                $$->L_child = $1;
                $1->Parent = $$;
           }
           ;

create_exp: CREATE DATABASE NAME {}
          ;
update_exp: UPDATE NAME SET NAME EQ NAME WHERE NAME EQ NAME {}
          ;

insert_exp: INSERT INTO NAME '(' key_value_exp ')' VALUES '(' value_key_exp ')' 
            {
                $$ = Create_new_node(INSERT,"insert into name() valuse()");
            } 
            | INSERT INTO NAME VALUES '(' value_key_exp ')' 
            {
                $$ = Create_new_node(INSERT,"insert into name() valuse()");
            }
          ;

key_value_exp: NAME {}
             | id_comma_exp NAME {}
             ;

id_comma_exp: NAME ','  {}
            | id_comma_exp NAME ',' {}
            ;

value_key_exp: NAME {}
             | id2_comma_exp NAME {}
             ; 

id2_comma_exp: NAME ',' {}
             | id2_comma_exp NAME ',' {}
             ;


%%

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

