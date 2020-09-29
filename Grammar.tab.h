/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 148 "Grammar.y" /* yacc.c:1909  */

    struct Tree_Node* node;
    char* strval;

#line 124 "Grammar.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_GRAMMAR_TAB_H_INCLUDED  */
