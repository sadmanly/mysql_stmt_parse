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
%}
%x NOTE_STAT 

num [0-9]*
name [a-zA-Z][a-zA-Z0-9_]*
string [a-zA-Z0-9]+

%%


begin {do_begin();}
AS {return AS;}
SELECT {return SELECT;}

ALL { yylval.node = Create_new_node(SELECT_OPT,"ALL"); return ALL; }
DISTINCT {yylval.node = Create_new_node(SELECT_OPT,"DISTINCT");return DISTINCT; }
DISTINCTROW {yylval.node = Create_new_node(SELECT_OPT,"DISTINCTROW");return DISTINCTROW;}
STRAIGHT_JOIN {yylval.node = Create_new_node(SELECT_OPT,"TRAIGHT_JOIN");return STRAIGHT_JOIN;}
SQL_SMALL_RESULT {yylval.node = Create_new_node(SELECT_OPT,"SQL_SMALL_RESULT");return SQL_SMALL_RESULT;}
SQL_BIG_RESULT {yylval.node = Create_new_node(SELECT_OPT,"SQL_BIG_RESULT");return SQL_BIG_RESULT; }
SQL_BUFFER_RESULT {yylval.node = Create_new_node(SELECT_OPT,"SQL_BUFFER_RESULT");return SQL_BUFFER_RESULT;}
SQL_NO_CHACHE {yylval.node = Create_new_node(SELECT_OPT,"SQL_NO_CACHE");return SQL_NO_CHACHE;}
SQL_CALC_FOUND_ROWS {yylval.node = Create_new_node(SELECT_OPT,"SQL_CALC_FOUND_ROWS");return SQL_CALC_FOUND_ROWS;}

HIGH_PRIORITY { return HIGH_PRIORITY; }
FROM {return FROM;}
PARTITION {return PARTITION;}
WHERE {return WHERE;}
GROUP {return GROUP;}
BY {return BY;}
HAVING {return HAVING;}
WINDOW {return WINDOW;}
ORDER {return ORDER;}
LIMIT {return LIMIT;}
INTO {return INTO;}
INSERT {return INSERT;}
UPDATE {return UPDATE; }
SET {return SET;}
CREATE {return CREATE;}
DATABASE {return DATABASE;}
JOIN {return JOIN;}
INNER {return INNER;}
CROSS {return CROSS;}
USING {return USING;}
LEFT {return LEFT;}
RIGHT {return RIGHT;}
OUTER {return OUTER;}
NATURAL {return NATURAL;}
ON {return ON;}
AND {return AND;}
OR {return OR;}
IN {return IN;}
NOT {return NOT;}
EXISTS {return EXISTS;}
UNION {return UNION;}
ASC {return ASC;}
DESC {return DESC;}
CASE {return CASE;}
THEN {return THEN;}
WHEN {return WHEN;}
END {return END;}
ELSE {return ELSE;}
LIKE {return LIKE;}
`{name}` {yylval.strval = strdup(yytext);return NAME;} 
 /*处理等于和不等于*/
\<=?\> {return EQ; } 
 /*处理系统变量 @@ 的情况*/

@@{name} {yylval.strval = strdup(yytext);return SYSTEM_CALL_VARIABLE;} 
@{name} {yylval.strval = strdup(yytext);return USER_CALL_VARIABLE;}

[0-9]+\.?[0-9]* {yylval.strval = strdup(yytext);return NUM;}
    /*处理函数*/
{name} {yylval.strval = strdup(yytext);return NAME;}
'[^/"']*' {yylval.strval = strdup(yytext);return NAME;}
{num} {yylval.strval = strdup(yytext);return NUM;}
"*" {  return yytext[0];}
[+-/&~|^%(),.;!] {return yytext[0]; }
    /*处理注释*/
"--"[\t ].* ;
"#".* ;
"/*" { old_stat = YY_START; BEGIN NOTE_STAT;}
<NOTE_STAT>\n|. ;
<NOTE_STAT>"*/" {BEGIN old_stat;}
 /*处理当读到文件结束也没有发现注释结束的符号*/
<NOTE_STAT><<EOF>> {BEGIN old_stat; yyerror("你的注释没有结束，文件以结束，检查文件\n");}
 /*处理比较的符号 返回 EQ */
">" {yylval.strval = strdup(yytext);return EQ;}
"<" {yylval.strval = strdup(yytext);return EQ;}
"=" {yylval.strval = strdup(yytext);return EQ;}
"!=" {yylval.strval = strdup(yytext);return EQ;}
">=" {yylval.strval = strdup(yytext);return EQ;}
"<=" {yylval.strval = strdup(yytext);return EQ;}

[ \t] {}  
\n {}  
.   { yyerror(" Mystery character=%s! ",yytext);}
%%

int do_begin()
{
    yyin = fopen("liuyu","r");
    return 1;
}
