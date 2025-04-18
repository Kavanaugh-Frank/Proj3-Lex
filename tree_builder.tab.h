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
     ALPHANUMERIC_VARIABLE = 258,
     ALPHANUMERIC_LITERAL = 259,
     NUMERIC = 260,
     BUILDNODE = 261,
     NAME = 262,
     WEIGHT = 263,
     ISACHILDOF = 264,
     FOR_LOOP = 265,
     IN = 266,
     PRINT = 267,
     SYMBOL_EQUALS = 268,
     SYMBOL_COLON = 269,
     SYMBOL_SEMICOLON = 270,
     SYMBOL_LBRACE = 271,
     SYMBOL_RBRACE = 272,
     SYMBOL_LPAREN = 273,
     SYMBOL_RPAREN = 274,
     SYMBOL_LBRACKET = 275,
     SYMBOL_RBRACKET = 276,
     SYMBOL_PLUS = 277
   };
#endif
/* Tokens.  */
#define ALPHANUMERIC_VARIABLE 258
#define ALPHANUMERIC_LITERAL 259
#define NUMERIC 260
#define BUILDNODE 261
#define NAME 262
#define WEIGHT 263
#define ISACHILDOF 264
#define FOR_LOOP 265
#define IN 266
#define PRINT 267
#define SYMBOL_EQUALS 268
#define SYMBOL_COLON 269
#define SYMBOL_SEMICOLON 270
#define SYMBOL_LBRACE 271
#define SYMBOL_RBRACE 272
#define SYMBOL_LPAREN 273
#define SYMBOL_RPAREN 274
#define SYMBOL_LBRACKET 275
#define SYMBOL_RBRACKET 276
#define SYMBOL_PLUS 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 28 "tree_builder.y"
{
    int intval;
    char* strval;
    integer_expression* int_expr;
    string_expression* str_expr;
    build_node* build_node_cmd;
    std::vector<build_node*>* build_node_list;
    std::vector<str_literal*>* str_literal_list;
}
/* Line 1529 of yacc.c.  */
#line 103 "tree_builder.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

