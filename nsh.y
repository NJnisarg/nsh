%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "command.c"

int yylex(void);
void yyerror(char *);

struct simpleCommand * cm;
%}


%union {
	char *str;
	int i;
}


%token <str> WORD
%token <i> NOTOKEN NEWLINE EXIT LESS GREAT GREATGREAT AMPERSAND PIPE

%start simple_command

%%
cmd:
	WORD	{cm = create_simple_command($1,5);}
	;
arg:
	WORD	{insert_arg(cm, $1);}
	;
arg_list:
	arg_list arg
	|
	;
io_modifier_opt:
	LESS WORD		{
						cm->infile = $2;
					}
	| GREAT WORD	{
						cm->outfile = $2;
						cm->outfile_append = 0;
					}
	| GREATGREAT WORD 	{
							cm->outfile = $2;
							cm->outfile_append = 1;
						}
	;
redirection:
	redirection io_modifier_opt
	|
	;
simple_command:
	| simple_command cmd arg_list redirection NEWLINE {
												execute_command(cm);
												show_prompt();
											}
	| simple_command NEWLINE
	| simple_command EXIT					{
												exit(EXIT_SUCCESS);
											}
	|
	;



%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
int main()
{
	show_prompt();
	yyparse();
}