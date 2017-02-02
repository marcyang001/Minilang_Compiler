
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
{comment}					{}
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


while 						{ yylval.stringconst = new std::string(yytext); return WHILE; }
do 	 						{ yylval.stringconst = new std::string(yytext); return DO; }
done 						{ yylval.stringconst = new std::string(yytext); return DONE; }
print   					{ yylval.stringconst = new std::string(yytext); return PRINT; }
read 						{ yylval.stringconst = new std::string(yytext); return READ; }
int 						{ yylval.op_val = new std::string(yytext); return INT; }
float 						{ yylval.op_val = new std::string(yytext); return FLOAT; }
string 						{ yylval.op_val = new std::string(yytext); return STRING; }
if  						{ yylval.stringconst = new std::string(yytext); return IF; }
then 						{ yylval.stringconst = new std::string(yytext); return THEN; }
else						{ yylval.stringconst = new std::string(yytext); return ELSE; }
endif  						{ yylval.stringconst = new std::string(yytext); return ENDIF; }
var	 						{ yylval.stringconst = new std::string(yytext); return VAR; }


[_a-zA-Z][a-zA-Z0-9]*		{ yylval.stringconst = new std::string(yytext); return tIDEN; }
{string_literal}			{ yylval.op_val = new std::string(yytext); return tSTRING_LITERAL; }

.           				{ yyerror(yytext); exit(1);    }

%%
