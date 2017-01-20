%{

#include "heading.h"
using namespace std;
int yyerror(char *s);
int yylex(void);

%}

%union  {
    int		        int_val;
    std::string*	op_val;
    char*         stringconst;
    float         f_val;
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

// boolean
%token '<' '>'
%token LEQUAL GEQUAL
%token<op_val> EQUAL

%token<op_val> tASSIGN
%token<op_val> COMMENT

%token<op_val> ENDL
%left<op_val> COLON



%start input 


%%

input:		/* empty */ 
    whileLoop
    ;

declarations:
    declarations VAR tIDEN COLON FLOAT ENDL  
    | declarations VAR tIDEN COLON INT ENDL   
    | declarations VAR tIDEN COLON STRING ENDL 
    | VAR tIDEN COLON FLOAT ENDL 
    | VAR tIDEN COLON INT ENDL 
    | VAR tIDEN COLON STRING ENDL
    ;

simpleAndIfStmts: 
  simpleStmts
  ;

simpleStmts:
    PRINT expOp ENDL
    | PRINT booleanOp ENDL
    | PRINT tSTRING_LITERAL ENDL
    | PRINT ENDL
    | READ tIDEN ENDL
    | assignOp ENDL
    ;

whileLoop:
    WHILE assignOp DO whileLoop DONE
    | WHILE booleanOp DO whileLoop DONE
    | WHILE tINT DO whileLoop DONE
    | simpleAndIfStmts whileLoop
    | whileLoop simpleAndIfStmts
    | simpleAndIfStmts
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
    ;

assignOp:
    | tIDEN tASSIGN expOp  
    | tIDEN tASSIGN tIDEN
    | tIDEN tASSIGN booleanOp
    | tIDEN tASSIGN tSTRING_LITERAL
    | tIDEN
    ;

booleanOp:
    | expOp '<' expOp
    | expOp '>' expOp
    | expOp LEQUAL expOp
    | expOp GEQUAL expOp
    | expOp EQUAL expOp
    ;




testnumber:
    tFLOAT input { cout << "found a float " << endl; }
    | tINT input  { cout << "found a int " << endl; }
    | tFLOAT  { cout << "found a float " << endl; }
    | tINT      { cout << "found a int " << endl; }
    ;


comment:
    COMMENT         { cout << "This is a comment " << endl; }
    ;


%%


int yyerror(string s)
{
  extern int line_num;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cout << "INVALID: " << s << " at symbol \"" << yytext;
  cout << "\" on line " << line_num << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}

