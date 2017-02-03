%{

#include "heading.h"
using namespace std;
int yyerror(char *s);
int yylex(void);

%}

%union  {
    int		        int_val;
    std::string*	op_val;
    std::string*    stringconst;
    float           f_val;
}



// define the keyword tokens:

// keywords
%token<stringconst>   VAR
%token<stringconst>   WHILE 
%token<stringconst>   DO
%token<stringconst>   DONE 
%token<stringconst>   IF 
%token<stringconst>   THEN
%token<stringconst>   ELSE 
%token<stringconst>   ENDIF
%token<stringconst>   PRINT
%token<stringconst>   READ


// types
%token<stringconst>   FLOAT 
%token<stringconst>   STRING 
%token<stringconst>   INT


// values
%token<stringconst>   tIDEN
%token<f_val>         tFLOAT 
%token<int_val>       tINT
%token<stringconst>   tSTRING_LITERAL


// numeric operators
%left '+' '-'
%left '*' '/'
%left NEG
%token '(' ')'


%token<op_val> tASSIGN

%token<op_val> ENDL
%left<op_val> COLON



%start input 


%%

input:
    declarations statements
    | statements
    ;

declarations:
    | declarations declaration
    | declaration
    ;

declaration:
    VAR tIDEN COLON FLOAT ENDL 
    | VAR tIDEN COLON INT ENDL 
    | VAR tIDEN COLON STRING ENDL
    ;

statements:
    statements statement
    | statement

statement:
    IF expOp THEN statement ELSE statement ENDIF
    | IF expOp THEN statement ENDIF 
    | WHILE expOp DO statement DONE 
    | simpleStmts
    | %empty
    ;

simpleStmts:
    PRINT expOp ENDL
    | READ tIDEN ENDL
    | tIDEN tASSIGN expOp ENDL
    ;



expOp:
    expOp '-' expOp
    | expOp '+' expOp
    | expOp '*' expOp
    | expOp '/' expOp
    | '(' expOp ')'
    | '-' expOp %prec NEG
    | tINT 
    | tFLOAT
    | tIDEN
    | tSTRING_LITERAL
    ;

%%


int yyerror(string s)
{
  extern int line_num;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cout << "INVALID: at symbol \"" << yytext;
  cout << "\" on line " << (line_num) << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}

