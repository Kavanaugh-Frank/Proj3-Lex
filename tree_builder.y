/*Created by Kavanaugh Frank and Alec Martell for Project 2*/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "parse_tree.h"

// Symbol tables for variables
std::map<std::string, int> int_sym_tab;
std::map<std::string, std::string> str_sym_tab;
// Node table for tree nodes
std::map<std::string, TreeNode*> nodeTab;

// Forward declaration of yyerror and lexer
void yyerror(const char *s);
int yylex();
extern int yylineno;
extern FILE *yyin;
%}

%union {
    int intval;
    char* strval;
    integer_expression* int_expr;
    string_expression* str_expr;
    build_node* build_node_cmd;
    std::vector<build_node*>* build_node_list;
    std::vector<str_literal*>* str_literal_list;
}

%token <strval> ALPHANUMERIC_VARIABLE ALPHANUMERIC_LITERAL
%token <intval> NUMERIC
%token BUILDNODE NAME WEIGHT ISACHILDOF FOR_LOOP IN PRINT
%token SYMBOL_EQUALS SYMBOL_COLON SYMBOL_SEMICOLON SYMBOL_LBRACE SYMBOL_RBRACE SYMBOL_LPAREN SYMBOL_RPAREN
%token SYMBOL_LBRACKET SYMBOL_RBRACKET SYMBOL_PLUS

%type <int_expr>           int_expr
%type <str_expr>           str_expr
%type <build_node_cmd>     top_build_node_stmt loop_build_node_stmt build_node_body
%type <build_node_list>    build_node_list
%type <str_literal_list>   str_literal_list
%type <str_expr>           name_assignment ischildof_assignment
%type <int_expr>           weight_assignment

%%

program:
    statements
    ;

statements:
    statements statement
  | statement
  ;

statement:
    top_build_node_stmt
  | for_loop_stmt
  | for_each_loop_stmt
  | print_stmt
  ;

// since we have need to execute these immediately and the loop build nodes need to wait for the local tables 
// in their respective for loops we have to separate them out based on their level
top_build_node_stmt:
    BUILDNODE SYMBOL_LBRACE build_node_body SYMBOL_RBRACE SYMBOL_SEMICOLON
    {
        $$ = $3;
        $3->execute(nodeTab, int_sym_tab, str_sym_tab);
    }
    ;

// the only time this is called is when YACC is building the body for a for loop
// that means that only when YACC is reducing the inside of a for loop, does it try
// and build the build_node_list and in which case that pattern matching only points 
// to the loop node statement and does not immediately execute the statement
loop_build_node_stmt:
    BUILDNODE SYMBOL_LBRACE build_node_body SYMBOL_RBRACE SYMBOL_SEMICOLON
    {
        $$ = $3;
    }
    ;

build_node_body:
    name_assignment weight_assignment ischildof_assignment {
        $$ = new build_node($1, $2, $3);
    }
    ;

name_assignment:
    NAME SYMBOL_EQUALS str_expr SYMBOL_SEMICOLON {
        $$ = $3;
    }
    ;

weight_assignment:
    WEIGHT SYMBOL_EQUALS int_expr SYMBOL_SEMICOLON {
        $$ = $3;
    }
    ;

ischildof_assignment:
    ISACHILDOF SYMBOL_EQUALS str_expr SYMBOL_SEMICOLON {
        $$ = $3;
    }
  | /* empty */ {
        $$ = new str_literal("");
    }
    ;

for_loop_stmt:
    FOR_LOOP ALPHANUMERIC_VARIABLE IN SYMBOL_LBRACKET int_expr SYMBOL_COLON int_expr SYMBOL_RBRACKET
    SYMBOL_LBRACE build_node_list SYMBOL_RBRACE SYMBOL_SEMICOLON
    {
        str_literal* loop_var = new str_literal($2);
        int_literal* start = dynamic_cast<int_literal*>($5);
        int_literal* stop  = dynamic_cast<int_literal*>($7);
        if (!start || !stop) {
            yyerror("Start and stop must be integer literals.");
            YYABORT;
        }
        for_loop* loop = new for_loop(loop_var, start, stop, *$10);
        loop->execute(nodeTab);
        delete $10;
    }
    ;

for_each_loop_stmt:
    FOR_LOOP ALPHANUMERIC_VARIABLE IN SYMBOL_LBRACKET str_literal_list SYMBOL_RBRACKET
    SYMBOL_LBRACE build_node_list SYMBOL_RBRACE
    {
        str_literal* loop_var = new str_literal($2);
        for_each_loop* loop = new for_each_loop(loop_var, *$5, *$8);
        loop->execute(nodeTab);
        delete $5;
        delete $8;
    }
    ;

build_node_list:
    build_node_list loop_build_node_stmt {
        $1->push_back($2);
        $$ = $1;
    }
  | loop_build_node_stmt {
        $$ = new std::vector<build_node*>();
        $$->push_back($1);
    }
    ;

print_stmt:
    PRINT SYMBOL_LPAREN str_expr SYMBOL_RPAREN SYMBOL_SEMICOLON {
        print* print_cmd = new print(new str_literal($3->evaluate_expression(str_sym_tab)));
        print_cmd->execute(nodeTab);
        delete print_cmd;
    }
    ;

int_expr:
    NUMERIC               { $$ = new int_literal($1); }
  | ALPHANUMERIC_VARIABLE { $$ = new var_int_expr($1); }
  | int_expr SYMBOL_PLUS int_expr { $$ = new plus_expr($1, $3); }
    ;

str_expr:
    ALPHANUMERIC_LITERAL   { $$ = new str_literal($1); }
  | ALPHANUMERIC_VARIABLE  { $$ = new var_str_expr($1); }
  | str_expr SYMBOL_PLUS str_expr { $$ = new string_plus_expr($1, $3); }
    ;

str_literal_list:
    str_literal_list SYMBOL_PLUS ALPHANUMERIC_LITERAL {
        $1->push_back(new str_literal($3));
        $$ = $1;
    }
  | ALPHANUMERIC_LITERAL {
        $$ = new std::vector<str_literal*>();
        $$->push_back(new str_literal($1));
        // $$ = $1;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) { perror("Error opening file"); return EXIT_FAILURE; }
    yyin = file;
    yyparse();
    fclose(file);
    return 0;
}
