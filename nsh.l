%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "y.tab.h"

%}

%%

[ \t]			{
					;
				}
"\n"			{
					return NEWLINE;
				}
";"				{
					return SEMICOLON;
				}
">"				{
					return GREAT;
				}
">>"			{
					return GREATGREAT;
				}
"<"				{
					return LESS;
				}

"|"				{
					return PIPE;
				}
"&"				{
					return AMPERSAND;
				}
"&&"			{
					return AND;
				}	
"||"			{
					return OR;
				}




"exit"								{
										return EXIT;
									}

[-_/.a-zA-Z0-9][-_/.a-zA-Z0-9]*		{
										yylval.str = strdup(yytext);
										return WORD;
									}
.				{
					return NOTOKEN;
				}
%%

int yywrap(void)
{
	return 1;
}
