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
    char*           stringconst;
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
%type <exp> input program expOp simpleStmts declarations declaration statements 



%start input 


%%

input:
    program { theexpression = $1; }
    ;

program: 
    statements
    | declarations                  { $$ = $1; }
    | declarations statements
    | %empty                        { }
    ;

declarations:
    declarations declaration        { $$ = makeDECLS ($1, $2); }
    | declaration                   { $$ = $1; }
    ;

declaration:
    VAR tIDEN COLON FLOAT ENDL      { $$ = makeDECL ($2, $4); }
    | VAR tIDEN COLON INT ENDL      { $$ = makeDECL ($2, $4); }
    | VAR tIDEN COLON STRING ENDL   { $$ = makeDECL ($2, $4); }

simpleStmts:
    PRINT expOp ENDL                { $$ = makePRINTStmt ($2);  }
    | READ tIDEN ENDL               { $$ = makeREADStmt ($2);   }
    | tIDEN tASSIGN expOp ENDL      { $$ = makeASSIGNStmt ($1, $3); } 
    ;

statements:
    statements WHILE expOp DO statements DONE                         {  }
    | statements IF expOp THEN statements ELSE statements ENDIF       {  }
    | statements IF expOp THEN statements ENDIF                       {  }
    | statements WHILE expOp DO DONE                                  {  }
    | statements IF expOp THEN ELSE ENDIF                             {  }
    | statements IF expOp THEN ENDIF                                  {  }
    | statements simpleStmts                                          {  }
    | WHILE expOp DO statements DONE                                  {  }
    | IF expOp THEN statements ELSE statements ENDIF                  {  }
    | IF expOp THEN statements ENDIF                                  {  }
    | WHILE expOp DO DONE                                             {  }
    | IF expOp THEN ENDIF                                             {  }
    | IF expOp THEN ELSE ENDIF                                        {  }
    | simpleStmts                                                     { $$ = $1; }
    ;

expOp:
    expOp '+' expOp                     { $$ = makeEXPplus ($1, $3); }
    | expOp '-' expOp                   { $$ = makeEXPminus ($1, $3); }
    | expOp '*' expOp                   { $$ = makeEXPtimes ($1, $3); }
    | expOp '/' expOp                   { $$ = makeEXPdiv ($1, $3); }
    | '(' expOp ')'                     { $$ = $2; }
    | '-' expOp %prec NEG               { $$ = makeEXPunarym ($2); }
    | tIDEN                             { $$ = makeEXPid ($1); }          
    | tSTRING_LITERAL                   { $$ = makeEXPstringconst ($1); }
    | tINT                              { $$ = makeEXPintconst ($1); }               
    | tFLOAT                            { $$ = makeEXPfloatconst ($1); }    
    ;
%%


int yyerror(char *s)
{

    printf ("INVALID: at symbol \" %s", yytext);
    printf ("\" on line %d\n", line_num);
    exit(1);
}