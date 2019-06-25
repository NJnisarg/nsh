%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"
#include "input.c"

void prepend(char* s, char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for(i = 0;i < len; ++i)
    {
        s[i] = t[i];
    }
}

%}

%%

[ \t]			{
					;
				}
"\n"			{
					return NLINE;
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

[":"-_/.a-zA-Z0-9][":"-_/.a-zA-Z0-9]*	{
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
