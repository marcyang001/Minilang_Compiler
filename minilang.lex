
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
string_literal			(\"(\\[atrn"\\]|[^\\"])*\")
comment 				(\/\/.*)



%%
[ \t\r]*					{}
[\n]						{ line_num++; }

{integer}					{ yylval.int_val = atoi(yytext); return tINT; }
{floatNumber}				{ yylval.int_val = atof(yytext); return tFLOAT; }


"+"							{ return '+'; }
"*"							{ return '*'; }
"/"							{ return '/'; }
"-"							{ return '-'; }
"("							{ return '('; }
")"							{ return ')'; }


"="         				{ yylval.op_val = new std::string(yytext); return tASSIGN; }
":"							{ yylval.op_val = new std::string(yytext); return COLON; }
";"							{ yylval.op_val = new std::string(yytext); return ENDL; }
{comment}					{ yylval.op_val = new std::string(yytext); return COMMENT; }


while 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return WHILE; }
do 	 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return DO; }
done 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return DONE; }
print   					{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return PRINT; }
read 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return READ; }
int 						{ yylval.op_val = new std::string(yytext); return INT; }
float 						{ yylval.op_val = new std::string(yytext); return FLOAT; }
string 						{ yylval.op_val = new std::string(yytext); return STRING; }
if  						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return IF; }
then 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return THEN; }
else						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return ELSE; }
endif  						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return ENDIF; }
var	 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return VAR; }


[_a-zA-Z][a-zA-Z0-9]*		{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return tIDEN; }
{string_literal}			{ yylval.op_val = new std::string(yytext); return tSTRING_LITERAL; }

.           				{ yyerror(yytext); exit(1);    }

%%
