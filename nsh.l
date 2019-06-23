%{

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "y.tab.h"

%}

%%
"exit"								{
										return EXIT;
									}
[-_/.a-zA-Z0-9][-_/.a-zA-Z0-9]*		{
										yylval.str = strdup(yytext);
										return WORD;
									}
[ \t]			{
					;
				}
"\n"			{
					return NEWLINE;
				}
.				{
					return NOTOKEN;
				}
%%

int yywrap(void)
{
	return 1;
}
