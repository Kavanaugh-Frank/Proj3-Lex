/*Created by Kavanaugh Frank and Alec Martell for Project 2*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <vector>
#include "tree_builder.tab.h" 

extern FILE *yyout;
%}

%option yylineno

ALPHANUMERIC_LITERAL \"[a-zA-Z0-9_-]+\"
ALPHANUMERIC_VARIABLE [a-zA-Z0-9_-]+
NUMERIC [0-9]+

%%

\n                          { /* Ignore newline*/ }
[ \t]+                      { /* Ignore whitespace */ }

"buildnode"                 { return BUILDNODE; }
"name"                      { return NAME; }
"weight"                    { return WEIGHT; }
"isachildof"                { return ISACHILDOF; }
"for"                       { return FOR_LOOP; }
"in"                        { return IN; }
"print"                     { return PRINT; }

{NUMERIC}                   { yylval.intval = atoi(yytext); return NUMERIC; }
{ALPHANUMERIC_VARIABLE}     { yylval.strval = strdup(yytext); return ALPHANUMERIC_VARIABLE; }
\"[^\"]*\"                  { yylval.strval = strdup(yytext + 1); yylval.strval[strlen(yylval.strval) - 1] = '\0'; return ALPHANUMERIC_LITERAL; }

"="                         { return SYMBOL_EQUALS; }
"{"                         { return SYMBOL_LBRACE; }
"}"                         { return SYMBOL_RBRACE; }
"["                         { return SYMBOL_LBRACKET; }
"]"                         { return SYMBOL_RBRACKET; }
"("                         { return SYMBOL_LPAREN; }
")"                         { return SYMBOL_RPAREN; }
":"                         { return SYMBOL_COLON; }
";"                         { return SYMBOL_SEMICOLON; }
"+"                         { return SYMBOL_PLUS; }

.                           { fprintf(stderr, "Unrecognized character: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    yyin = file;
    yyout = stdout;  // Set yyout to stdout to output to the terminal
    yylex();
    fclose(file);

    return 0;
}