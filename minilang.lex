
/* calc.lex */

%{
#include "heading.h"
#include "tok.h"
int yyerror(char *s);
int line_num = 1;
%}



digit 	    			[0-9]
integer 	    		([1-9]{digit}*|0?)
floatNumber	    		{digit}\.{digit}+
string_literal			(\"(\\[abfnrtv"\\]|[^\\"])*\")
comment 				(\/\/.*)



%%
[ \t\r]*					{}
{comment}					{}
[\n]						{ line_num++; }


{integer}					{ yylval.int_val = atoi(yytext); return tINT; }
{floatNumber}				{ yylval.f_val = atof(yytext); return tFLOAT; }


"+"							{ return '+'; }
"*"							{ return '*'; }
"/"							{ return '/'; }
"-"							{ return '-'; }
"("							{ return '('; }
")"							{ return ')'; }


"="         				{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return tASSIGN; }
":"							{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return COLON; }
";"							{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return ENDL; }


while 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return WHILE; }
do 	 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return DO; }
done 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return DONE; }
print   					{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return PRINT; }
read 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return READ; }
int 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); sprintf (yylval.stringconst, "%s", yytext); return INT; }
float 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); sprintf (yylval.stringconst, "%s", yytext); return FLOAT; }
string 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); sprintf (yylval.stringconst, "%s", yytext); return STRING; }
if  						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return IF; }
then 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return THEN; }
else						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return ELSE; }
endif  						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return ENDIF; }
var	 						{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); return VAR; }


[_a-zA-Z][_a-zA-Z0-9]*		{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); sprintf (yylval.stringconst, "%s", yytext); return tIDEN; }
{string_literal}			{ yylval.stringconst = (char *) malloc (strlen (yytext) + 1); sprintf (yylval.stringconst, "%s", yytext); return tSTRING_LITERAL; }
.           				{ yyerror(yytext); exit(1);    }

%%
