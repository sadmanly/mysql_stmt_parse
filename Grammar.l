%option noyywrap case-insensitive yylineno nodefault
%{
#include "Grammar.tab.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"
extern int yyerror();
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
AS {Insert_str(yytext);return AS;}
SELECT {Insert_str(yytext);return SELECT;}

ALL { Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"ALL"); return ALL; }
DISTINCT {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"DISTINCT");return DISTINCT; }
DISTINCTROW {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"DISTINCTROW");return DISTINCTROW;}
STRAIGHT_JOIN {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"TRAIGHT_JOIN");return STRAIGHT_JOIN;}
SQL_SMALL_RESULT {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"SQL_SMALL_RESULT");return SQL_SMALL_RESULT;}
SQL_BIG_RESULT {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"SQL_BIG_RESULT");return SQL_BIG_RESULT; }
SQL_BUFFER_RESULT {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"SQL_BUFFER_RESULT");return SQL_BUFFER_RESULT;}
SQL_NO_CHACHE {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"SQL_NO_CACHE");return SQL_NO_CHACHE;}
SQL_CALC_FOUND_ROWS {Insert_str(yytext);yylval.node = Create_new_node(SELECT_OPT,"SQL_CALC_FOUND_ROWS");return SQL_CALC_FOUND_ROWS;}

HIGH_PRIORITY { Insert_str(yytext);return HIGH_PRIORITY; }
FROM {Insert_str(yytext);return FROM;}
PARTITION {Insert_str(yytext);return PARTITION;}
WHERE {Insert_str(yytext);return WHERE;}
GROUP {Insert_str(yytext);return GROUP;}
BY {Insert_str(yytext);return BY;}
HAVING {Insert_str(yytext);return HAVING;}
WINDOW {Insert_str(yytext);return WINDOW;}
ORDER {Insert_str(yytext);return ORDER;}
LIMIT {Insert_str(yytext);return LIMIT;}
INTO {Insert_str(yytext);return INTO;}
INSERT {Insert_str(yytext);return INSERT;}
UPDATE {Insert_str(yytext);return UPDATE; }
SET {Insert_str(yytext);return SET;}
CREATE {Insert_str(yytext);return CREATE;}
DATABASE {Insert_str(yytext);return DATABASE;}
JOIN {Insert_str(yytext);return JOIN;}
INNER {Insert_str(yytext);return INNER;}
CROSS {Insert_str(yytext);return CROSS;}
USING {Insert_str(yytext);return USING;}
LEFT {Insert_str(yytext);return LEFT;}
RIGHT {Insert_str(yytext);return RIGHT;}
OUTER {Insert_str(yytext);return OUTER;}
NATURAL {Insert_str(yytext);return NATURAL;}
ON {Insert_str(yytext);return ON;}
AND {Insert_str(yytext);return AND;}
OR {Insert_str(yytext);return OR;}
IN {Insert_str(yytext);return IN;}
NOT {Insert_str(yytext);return NOT;}
EXISTS {Insert_str(yytext);return EXISTS;}
UNION {Insert_str(yytext);return UNION;}
ASC {Insert_str(yytext);return ASC;}
DESC {Insert_str(yytext);return DESC;}
CASE {Insert_str(yytext);return CASE;}
THEN {Insert_str(yytext);return THEN;}
WHEN {Insert_str(yytext);return WHEN;}
END {Insert_str(yytext);return END;}
ELSE {Insert_str(yytext);return ELSE;}
LIKE {Insert_str(yytext);return LIKE;}


 /*处理insert 语句的问题*/
VALUES {Insert_str(yytext);return VALUES;}
`{name}` {Insert_str(yytext);yylval.strval = strdup(yytext);return NAME;} 
 /*处理等于和不等于*/
\<=?\> {return EQ; } 
 /*处理系统变量 @@ 的情况*/

@@{name} {Insert_str(yytext);yylval.strval = strdup(yytext);return SYSTEM_CALL_VARIABLE;} 
@{name} {Insert_str(yytext);yylval.strval = strdup(yytext);return USER_CALL_VARIABLE;}

[0-9]+\.?[0-9]* {Insert_str(yytext);yylval.strval = strdup(yytext);return NUM;}
    /*处理函数*/
{name} {Insert_str(yytext);yylval.strval = strdup(yytext);return NAME;}
'[^/"']*' {Insert_str(yytext);yylval.strval = strdup(yytext);return NAME;}
{num} {Insert_str(yytext);yylval.strval = strdup(yytext);return NUM;}
"*" {Insert_str(yytext);  return yytext[0];}
[+-/&~|^%(),.;!] {Insert_str(yytext);return yytext[0]; }
    /*处理注释*/
"--"[\t ].* {Insert_str(yytext);};
"#".* {Insert_str(yytext);};
"/*" {Insert_str(yytext); old_stat = YY_START; BEGIN NOTE_STAT;}
<NOTE_STAT>\n|. {Insert_str(yytext);};
<NOTE_STAT>"*/" {Insert_str(yytext);BEGIN old_stat;}
 /*处理当读到文件结束也没有发现注释结束的符号*/
<NOTE_STAT><<EOF>> {BEGIN old_stat; yyerror("你的注释没有结束，文件以结束，检查文件\n");}
 /*处理比较的符号 返回 EQ */
">" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"<" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"!=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
">=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}
"<=" {Insert_str(yytext);yylval.strval = strdup(yytext);return EQ;}

[ \t\r] {Insert_str(yytext);}  
\n {Insert_str(yytext);}  
.   { yyerror(" Mystery character=%s! ",yytext);}
%%

int do_begin()
{
    yyin = fopen("liuyu","r");
    return 1;
}
