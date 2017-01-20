
/* calc.lex */

%{
#include "heading.h"
#include "tok.h"
using namespace std;
int yyerror(char *s);
int line_num = 1;
%}




digit 	    			[0-9]
integer 	    		([1-9]{digit}*|0?)
floatNumber	    		{integer}\.{digit}+
string_literal			(\"([^\\\"]|\\.)*\")
comment 				(\/\/.*)



%%
[ \t\r]*					{}
[\n]						{ ++line_num; }

{integer}					{ yylval.int_val = atoi(yytext); return tINT; }
{floatNumber}				{ yylval.int_val = atof(yytext); return tFLOAT; }


"+"							{ return '+'; }
"*"							{ return '*'; }
"/"							{ return '/'; }
"-"							{ return '-'; }
"=="						{ yylval.op_val = new std::string(yytext); return EQUAL; }

"="         				{ yylval.op_val = new std::string(yytext); return tASSIGN; }
":"							{ yylval.op_val = new std::string(yytext); return COLON; }
";"							{ yylval.op_val = new std::string(yytext); return ENDL; }
{comment}					{ yylval.op_val = new std::string(yytext); return COMMENT; }


var	 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return VAR; }
while 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return WHILE; }
int 						{ yylval.op_val = new std::string(yytext); return INT; }
float 						{ yylval.op_val = new std::string(yytext); return FLOAT; }
string 						{ yylval.op_val = new std::string(yytext); return STRING; }


[_a-zA-Z][a-zA-Z0-9]*		{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return tIDEN; }
{string_literal}			{ yylval.op_val = new std::string(yytext); return tSTRING_LITERAL; }

.           				{ std::cerr << "SCANNER " << endl; yyerror(""); exit(1);    }

%%
