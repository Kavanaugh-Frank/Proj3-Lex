/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_TREE_BUILDER_TAB_H_INCLUDED
# define YY_YY_TREE_BUILDER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ALPHANUMERIC_VARIABLE = 258,   /* ALPHANUMERIC_VARIABLE  */
    ALPHANUMERIC_LITERAL = 259,    /* ALPHANUMERIC_LITERAL  */
    NUMERIC = 260,                 /* NUMERIC  */
    BUILDNODE = 261,               /* BUILDNODE  */
    NAME = 262,                    /* NAME  */
    WEIGHT = 263,                  /* WEIGHT  */
    ISACHILDOF = 264,              /* ISACHILDOF  */
    FOR_LOOP = 265,                /* FOR_LOOP  */
    IN = 266,                      /* IN  */
    PRINT = 267,                   /* PRINT  */
    SYMBOL_EQUALS = 268,           /* SYMBOL_EQUALS  */
    SYMBOL_COLON = 269,            /* SYMBOL_COLON  */
    SYMBOL_SEMICOLON = 270,        /* SYMBOL_SEMICOLON  */
    SYMBOL_LBRACE = 271,           /* SYMBOL_LBRACE  */
    SYMBOL_RBRACE = 272,           /* SYMBOL_RBRACE  */
    SYMBOL_LPAREN = 273,           /* SYMBOL_LPAREN  */
    SYMBOL_RPAREN = 274,           /* SYMBOL_RPAREN  */
    SYMBOL_LBRACKET = 275,         /* SYMBOL_LBRACKET  */
    SYMBOL_RBRACKET = 276,         /* SYMBOL_RBRACKET  */
    SYMBOL_PLUS = 277              /* SYMBOL_PLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "tree_builder.y"

    int intval;
    char* strval;
    integer_expression* int_expr;
    string_expression* str_expr;
    build_node* build_node_cmd;
    std::vector<build_node*>* build_node_list;
    std::vector<str_literal*>* str_literal_list;

#line 96 "tree_builder.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TREE_BUILDER_TAB_H_INCLUDED  */
