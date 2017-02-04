%{

#include "heading.h"
using namespace std;
int yyerror(char *s);
int yylex(void);

%}

%union  {
    int             int_val;
    std::string*    op_val;
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
    statements
    | declarations statements
    ;

declarations:
    declarations VAR tIDEN COLON FLOAT ENDL  
    | declarations VAR tIDEN COLON INT ENDL   
    | declarations VAR tIDEN COLON STRING ENDL 
    | VAR tIDEN COLON FLOAT ENDL 
    | VAR tIDEN COLON INT ENDL 
    | VAR tIDEN COLON STRING ENDL
    ;

simpleStmts:
    PRINT expOp ENDL
    | READ tIDEN ENDL
    | tIDEN tASSIGN expOp ENDL
    ;

statements:
    statements WHILE expOp DO statements DONE
    | statements IF expOp THEN statements ELSE statements ENDIF
    | statements IF expOp THEN statements ENDIF 
    | statements simpleStmts
    | WHILE expOp DO statements DONE 
    | IF expOp THEN statements ELSE statements ENDIF
    | IF expOp THEN statements ENDIF 
    | simpleStmts
    | %empty
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
  extern int line_num;  // defined and maintained in lex.c
  extern char *yytext;  // defined and maintained in lex.c
  
  cout << "INVALID: at symbol \"" << yytext;
  cout << "\" on line " << (line_num) << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}
