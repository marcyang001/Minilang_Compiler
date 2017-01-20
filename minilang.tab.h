/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VAR = 258,
     WHILE = 259,
     DO = 260,
     DONE = 261,
     IF = 262,
     THEN = 263,
     ELSE = 264,
     ENDIF = 265,
     PRINT = 266,
     READ = 267,
     FLOAT = 268,
     STRING = 269,
     INT = 270,
     tIDEN = 271,
     tFLOAT = 272,
     tINT = 273,
     tSTRING_LITERAL = 274,
     NEG = 275,
     LEQUAL = 276,
     GEQUAL = 277,
     EQUAL = 278,
     tASSIGN = 279,
     COMMENT = 280,
     ENDL = 281,
     COLON = 282
   };
#endif
/* Tokens.  */
#define VAR 258
#define WHILE 259
#define DO 260
#define DONE 261
#define IF 262
#define THEN 263
#define ELSE 264
#define ENDIF 265
#define PRINT 266
#define READ 267
#define FLOAT 268
#define STRING 269
#define INT 270
#define tIDEN 271
#define tFLOAT 272
#define tINT 273
#define tSTRING_LITERAL 274
#define NEG 275
#define LEQUAL 276
#define GEQUAL 277
#define EQUAL 278
#define tASSIGN 279
#define COMMENT 280
#define ENDL 281
#define COLON 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 10 "minilang.y"
{
    int		        int_val;
    std::string*	op_val;
    char*         stringconst;
    float         f_val;
}
/* Line 1529 of yacc.c.  */
#line 110 "minilang.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

