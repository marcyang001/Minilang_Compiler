
/* calc.lex */

%{
#include "heading.h"
#include "tok.h"
using namespace std;
int yyerror(char *s);
int line_num = 1;
%}




digit 	    		[0-9]
integer 	    	([1-9]{digit}*|0?)
floatNumber	    	{integer}.{digit}+



%%
[ \t\r]*				{}
[\n]					{ ++line_num; }


"+"						{ yylval.op_val = new std::string(yytext); return PLUS; }
"*"						{ yylval.op_val = new std::string(yytext); return MULT; }
"/"						{ yylval.op_val = new std::string(yytext); return DIV; }
"-"						{ yylval.op_val = new std::string(yytext); return MINUS; }
"=="					{ yylval.op_val = new std::string(yytext); return EQUAL; }

"="         			{ yylval.op_val = new std::string(yytext); return tASSIGN; }


[_a-zA-Z][a-zA-Z0-9]*	{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return tIDEN; }




{integer}				{ yylval.int_val = atoi(yytext); return tINT; }
{floatNumber}			{ yylval.int_val = atof(yytext); return tFLOAT; }


int 					{ return INT; }
float 					{ return FLOAT; }
string 					{ return STRING; }


.		{ std::cerr << "SCANNER "; exit(1);	}
