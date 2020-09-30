%option noyywrap case-insensitive yylineno nodefault
%{
#include "Grammar.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"
#include "Main_act.h"
extern int yyerror();
extern _String* Insert_str();
int do_begin();
int old_stat;
extern struct Global _Global;
%}
%x NOTE_STAT 
   //test
num [0-9]*
name [a-zA-Z][a-zA-Z0-9_]*
string [a-zA-Z0-9]+

%%
begin {do_begin();}
AS {
        yylval.str_val = Insert_str(yytext);
        return AS;
    }
SELECT {yylval.str_val = Insert_str(yytext);return SELECT;}

ALL { yylval.node = Create_new_node(SELECT_OPT,"ALL"); return ALL; }
DISTINCT {yylval.node = Create_new_node(SELECT_OPT,"DISTINCT");return DISTINCT; }
DISTINCTROW {yylval.node = Create_new_node(SELECT_OPT,"DISTINCTROW");return DISTINCTROW;}
STRAIGHT_JOIN {yylval.node = Create_new_node(SELECT_OPT,"TRAIGHT_JOIN");return STRAIGHT_JOIN;}
SQL_SMALL_RESULT {yylval.node = Create_new_node(SELECT_OPT,"SQL_SMALL_RESULT");return SQL_SMALL_RESULT;}
SQL_BIG_RESULT {yylval.node = Create_new_node(SELECT_OPT,"SQL_BIG_RESULT");return SQL_BIG_RESULT; }
SQL_BUFFER_RESULT {yylval.node = Create_new_node(SELECT_OPT,"SQL_BUFFER_RESULT");return SQL_BUFFER_RESULT;}
SQL_NO_CHACHE {yylval.node = Create_new_node(SELECT_OPT,"SQL_NO_CACHE");return SQL_NO_CHACHE;}
SQL_CALC_FOUND_ROWS {yylval.node = Create_new_node(SELECT_OPT,"SQL_CALC_FOUND_ROWS");return SQL_CALC_FOUND_ROWS;}

HIGH_PRIORITY {yylval.str_val = Insert_str(yytext);return HIGH_PRIORITY; }
FROM {yylval.str_val = Insert_str(yytext);return FROM;}
PARTITION {yylval.str_val = Insert_str(yytext);return PARTITION;}
WHERE {yylval.str_val = Insert_str(yytext);return WHERE;}
GROUP {yylval.str_val = Insert_str(yytext);return GROUP;}
BY {yylval.str_val = Insert_str(yytext);return BY;}
HAVING {yylval.str_val = Insert_str(yytext);return HAVING;}
WINDOW {yylval.str_val = Insert_str(yytext);return WINDOW;}
ORDER {yylval.str_val = Insert_str(yytext);return ORDER;}
LIMIT {yylval.str_val = Insert_str(yytext);return LIMIT;}
INTO {yylval.str_val = Insert_str(yytext);return INTO;}
INSERT {yylval.str_val = Insert_str(yytext);return INSERT;}
UPDATE {yylval.str_val = Insert_str(yytext);return UPDATE; }
SET {yylval.str_val = Insert_str(yytext);return SET;}
CREATE {yylval.str_val = Insert_str(yytext);return CREATE;}
DATABASE {yylval.str_val = Insert_str(yytext);return DATABASE;}
JOIN {yylval.str_val = Insert_str(yytext);return JOIN;}
INNER {yylval.str_val = Insert_str(yytext);return INNER;}
CROSS {yylval.str_val = Insert_str(yytext);return CROSS;}
USING {yylval.str_val = Insert_str(yytext);return USING;}
LEFT {yylval.str_val = Insert_str(yytext);return LEFT;}
RIGHT {yylval.str_val = Insert_str(yytext);return RIGHT;}
OUTER {yylval.str_val = Insert_str(yytext);return OUTER;}
NATURAL {yylval.str_val = Insert_str(yytext);return NATURAL;}
ON {yylval.str_val = Insert_str(yytext);return ON;}
AND {yylval.str_val = Insert_str(yytext);return AND;}
OR {yylval.str_val = Insert_str(yytext);return OR;}
IN {yylval.str_val = Insert_str(yytext);return IN;}
NOT {yylval.str_val = Insert_str(yytext);return NOT;}
EXISTS {yylval.str_val = Insert_str(yytext);return EXISTS;}
UNION {yylval.str_val = Insert_str(yytext);return UNION;}
ASC {yylval.str_val = Insert_str(yytext);return ASC;}
DESC {yylval.str_val = Insert_str(yytext);return DESC;}
CASE {yylval.str_val = Insert_str(yytext);return CASE;}
THEN {yylval.str_val = Insert_str(yytext);return THEN;}
WHEN {yylval.str_val = Insert_str(yytext);return WHEN;}
END {yylval.str_val = Insert_str(yytext);return END;}
ELSE {yylval.str_val = Insert_str(yytext);return ELSE;}
LIKE {yylval.str_val = Insert_str(yytext);return LIKE;}


 /*处理insert 语句的问题*/
VALUES {yylval.str_val = Insert_str(yytext);return VALUES;}
`{name}` {Insert_str(yytext);yylval.strval = strdup(yytext);return NAME;} 
 /*处理等于和不等于*/
\<=?\> {yylval.str_val = Insert_str(yytext);return EQ; } 
 /*处理系统变量 @@ 的情况*/

@@{name} {Insert_str(yytext);yylval.strval = strdup(yytext);return SYSTEM_CALL_VARIABLE;} 
@{name} {Insert_str(yytext);yylval.strval = strdup(yytext);return USER_CALL_VARIABLE;}

[0-9]+\.?[0-9]* {Insert_str(yytext);yylval.strval = strdup(yytext);return NUM;}
    /*处理函数*/
{name} {Insert_str(yytext);yylval.strval = strdup(yytext);return NAME;}
'[^/"']*' {Insert_str(yytext);yylval.strval = strdup(yytext);return NAME;}
{num} {Insert_str(yytext);yylval.strval = strdup(yytext);return NUM;}
"*" {yylval.str_val = Insert_str(yytext);  return yytext[0];}
[+-/&~|^%(),.;!] {yylval.str_val = Insert_str(yytext);return yytext[0]; }
    /*处理注释*/
"--"[\t ].* {Insert_str(yytext);};
"#".* {Insert_str(yytext);};
"/*" {Insert_str(yytext); old_stat = YY_START; BEGIN NOTE_STAT;}
<NOTE_STAT>\n|. {Insert_str(yytext);};
<NOTE_STAT>"*/" {Insert_str(yytext);BEGIN old_stat;}
 /*处理当读到文件结束也没有发现注释结束的符号*/
<NOTE_STAT><<EOF>> {BEGIN old_stat; printf("你的注释没有结束，文件以结束，检查文件\n");}
 /*处理比较的符号 返回 EQ */
">" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"<" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"!=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
">=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"<=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}

[ \t\r] {Insert_str(yytext);}  
\n {Insert_str(yytext);}  
.   { printf(" Mystery character=%s!",yytext);}
%%

int do_begin()
{
    yyin = fopen("liuyu","r");
    return 1;
}
