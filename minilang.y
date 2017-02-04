%{

#include "heading.h"
int yyerror(char *s);
int yylex(void);

extern int line_num;  // defined and maintained in lex.c
extern char *yytext;  // defined and maintained in lex.c
extern EXP *theexpression;

%}

%union  {
    int             int_val;
    char*    stringconst;
    float           f_val;
    struct EXP *exp;
}


// define the keyword tokens:

// keyword tokens 
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


// type tokens
%token<stringconst>   FLOAT 
%token<stringconst>   STRING 
%token<stringconst>   INT


// value tokens
%token<stringconst>   tIDEN
%token<f_val>         tFLOAT 
%token<int_val>       tINT
%token<stringconst>   tSTRING_LITERAL


// numeric operators
%left '+' '-'
%left '*' '/'
%left NEG

// other operators
%token<stringconst> tASSIGN
%token<stringconst> ENDL
%left<stringconst> COLON


// define type
%type <exp> input expOp



%start input 


%%

input:
    expOp
    ;

program:
    statements
    | declarations
    | declarations statements
    | %empty
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
    | statements WHILE expOp DO DONE
    | statements IF expOp THEN ELSE ENDIF
    | statements IF expOp THEN ENDIF 
    | statements simpleStmts
    | WHILE expOp DO statements DONE 
    | IF expOp THEN statements ELSE statements ENDIF
    | IF expOp THEN statements ENDIF
    | WHILE expOp DO DONE
    | IF expOp THEN ENDIF 
    | IF expOp THEN ELSE ENDIF
    | simpleStmts
    ;

expOp:
    expOp '-' expOp 
    | expOp '+' expOp
    | expOp '*' expOp                   { $$ = makeEXPtimes($1, $3); }
    | expOp '/' expOp
    | '(' expOp ')'
    | '-' expOp %prec NEG
    | tIDEN                             { $$ = makeEXPid ($1); }          
    | tSTRING_LITERAL                   { $$ = makeEXPstringconst ($1); }
    | tINT                              { $$ = makeEXPintconst ($1); }               
    | tFLOAT                            { $$ = makeEXPfloatconst($1); }    
    ;
%%


int yyerror(char *s)
{

    printf ("INVALID: at symbol \" %s", yytext);
    printf ("\" on line %d\n", line_num);
    exit(1);
}
