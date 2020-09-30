%{
#include "Main_act.h"
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
extern struct Global _Global;
extern struct stmt _stmt;
%}

%union
{
    struct Tree_Node* node;
    char* strval;
    struct _String* str_val; 
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


 /*尝试加上偏移*/
%type<str_val> LIKE
%type<str_val> SELECT HIGH_PRIORITY  FROM PARTITION WHERE GROUP
%type<str_val> BY HAVING WINDOW ORDER LIMIT FOR JOIN INNER CROSS ON USING LEFT RIGHT OUTER 
%type<str_val> NATURAL AND OR NOT EXISTS UNION 
 /*声明token*/
%type<str_val> INSERT UPDATE CREATE
%type<str_val> ID SET 
%type<str_val> VALUES  
%type<str_val> DATABASE 
%type<str_val> AS 
%type<str_val> ASC DESC INTO WITH ROLLUP  
 /*函数关键字声明*/
%type<str_val> CONCAT CASE THEN WHEN END ELSE FLOOR


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
                // Show_string($1);
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
            ;

    /*
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
    */

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
                                        //全局使用变量的结构
    Init_stmt_vector();                 //初始化全局变量
    yyin  = parse_getopt(argc,argv);    //解析命令行的参数
    yyparse();                          //解析词法和建立语法树
    Main_mode();                        //具体动作
    Del_stmt_vector();                  //释放掉所有空间
    return 0;
}
