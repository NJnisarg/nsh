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
%token <i> NOTOKEN NEWLINE EXIT LESS GREAT GREATGREAT AMPERSAND PIPE

%start pipeline

%%
cmd:
	WORD	{
				cm = create_simple_command($1,10);
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
	pipeline simple_command_list redirection background NEWLINE		{
																		execute_pipeline(pl);
																		show_prompt();
																	}
	| pipeline NEWLINE
	| pipeline EXIT 	{
							exit(EXIT_SUCCESS);
						}	
	|																
	;

/*
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
*/

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
int main()
{
	pl = create_pipeline(10);
	cm = NULL;
	show_prompt();
	yyparse();
}