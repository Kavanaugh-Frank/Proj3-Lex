/*Created by Kavanaugh Frank and Alec Martell for Project 2*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern FILE *yyout;

extern "C" int yywrap(void) {
    return 1;
}
%}

ALPHANUMERIC_LITERAL \"[a-zA-Z0-9_-]+\"
ALPHANUMERIC_VARIABLE [a-zA-Z0-9_-]+
NUMERIC [0-9]+

%{
#define BUILDNODE "buildnode"
#define NAME "name"
#define WEIGHT "weight"
#define ISACHILDOF "isachildof"
#define EQUALS "="
#define ALPHANUMERIC_LITERAL "ALPHANUMERIC_LITERAL"
#define ALPHANUMERIC_VARIABLE "ALPHANUMERIC_VARIABLE"
#define NUMERIC "NUMERIC_LITERAL"
#define FOR_LOOP "for"
#define IN "in"
#define PRINT "print"
#define SYMBOL "SYMBOL"

%}

%%
[ \t\n]+                    { /*Ignore*/ }
"buildnode"                 { fprintf(yyout, "< RESERVED WORD: %s >\n", BUILDNODE); }
"name"                      { fprintf(yyout, "< RESERVED WORD: %s >\n", NAME); }
"weight"                    { fprintf(yyout, "< RESERVED WORD: %s >\n", WEIGHT); }
"isachildof"                { fprintf(yyout, "< RESERVED WORD: %s >\n", ISACHILDOF); }
"for"                       { fprintf(yyout, "< RESERVED WORD: %s >\n", FOR_LOOP); }
"in"                        { fprintf(yyout, "< RESERVED WORD: %s >\n", IN); }
"print"                     { fprintf(yyout, "< RESERVED WORD: %s >\n", PRINT); }
{NUMERIC}                   { fprintf(yyout, "< %s: %s >\n", NUMERIC, yytext); }
{ALPHANUMERIC_VARIABLE}     { fprintf(yyout, "< %s: %s >\n", ALPHANUMERIC_VARIABLE, yytext); }
{ALPHANUMERIC_LITERAL}      { fprintf(yyout, "< %s: %s >\n", ALPHANUMERIC_LITERAL, yytext); }
    /*
        Everything below here will be passed to YACC verbatim in the next step
        For now we are "tokenizing" it by identifying it and then making the token
            the individual symbol.
    */
"="                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
"{"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
"}"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
"["                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
"]"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
"("                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
")"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
":"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
";"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
"+"                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
","                         { fprintf(yyout, "< %s: %s >\n", SYMBOL, yytext); }
.                           {/* Ignore the rest */}


%%

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        return EXIT_FAILURE;
    }

    yyin = file;
    yyout = stdout;  // Set yyout to stdout to output to the terminal
    yylex();
    fclose(file);

    return 0;
}
