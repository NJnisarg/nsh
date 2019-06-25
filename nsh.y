%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "command.c"

int yylex(void);
void yyerror(char *);

struct pipeline * pl;
struct simpleCommand * cm;

%}


%union {
	char *str;
	int i;
}


%token <str> WORD
%token <i> NOTOKEN NLINE EXIT LESS GREAT GREATGREAT AMPERSAND PIPE SEMICOLON AND OR UPARROWKEY

%start pipeline

%%

terminator:
	NLINE
	| SEMICOLON
	;

cmd:
	WORD	{
				cm = create_simple_command($1);
			}
	;

arg:
	WORD	{
				insert_arg(cm, $1);
			}
	;

arg_list:
	arg_list arg
	|
	;

simple_command:
	cmd arg_list
	;

simple_command_list:
	simple_command_list PIPE simple_command 	{
													insert_simple_command(pl,cm);
													cm = NULL;
												}
	| simple_command 							{
													insert_simple_command(pl,cm);
													cm = NULL;
												}
	;

io_modifier_opt:
	LESS WORD		{
						pl->infile = $2;
					}
	| GREAT WORD	{
						pl->outfile = $2;
						pl->outfile_append = 0;
					}
	| GREATGREAT WORD 	{
							pl->outfile = $2;
							pl->outfile_append = 1;
						}
	;
redirection:
	redirection io_modifier_opt
	|
	;

background:
	AMPERSAND	{
					pl->background = 1;
				}
	|
	;

pipeline: 
	pipeline simple_command_list redirection background terminator	{
																		execute_pipeline(pl);
																		free(pl);
																		pl = create_pipeline();
																	}
	| pipeline terminator
	| pipeline EXIT 	{
							exit(EXIT_SUCCESS);
						}
	| UPARROWKEY		{
							printf("detects up arrow key!");
						}	
	|																
	;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
int main()
{
	pl = create_pipeline();
	cm = NULL;
	yyparse();
}