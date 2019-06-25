#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "command.h"

struct pipeline * create_pipeline(int max_num_simple_commands)
{
	struct pipeline * pl = (struct pipeline *)malloc(sizeof(struct pipeline));
	pl->max_num_simpleCommands = max_num_simple_commands;
	pl->current_num_simpleCommands = 0;
	pl->simpleCommands = (struct simpleCommand ** )malloc(max_num_simple_commands * sizeof(struct simpleCommand *));
	pl->infile = NULL;
	pl->outfile = NULL;
	pl->outfile_append = 0;
	pl->background = 0;
	pl->current_command_index = -1;

	return pl;
}

void insert_simple_command(struct pipeline * pl, struct simpleCommand * cm)
{
	int i = pl->current_num_simpleCommands;
	pl->simpleCommands[i] = cm;
	(pl->current_num_simpleCommands)+=1;
}

void execute_pipeline(struct pipeline * pl)
{
	int i=0;
	int tmpin = dup(0);
	int tmpout = dup(1);

	int fdin;
	if(pl->infile)
		fdin = open(pl->infile, O_RDONLY);
	else
		fdin = dup(tmpin);

	int ret;
	int fdout;
	for(i=0;i<pl->current_num_simpleCommands;i++)
	{
		dup2(fdin,0);
		close(fdin);

		if(i == (pl->current_num_simpleCommands - 1))
		{
			if(pl->outfile)
		   	{
		   		if(pl->outfile_append==1)
		   			fdout = open(pl->outfile, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
		   		else
		   		{
		   			truncate(pl->outfile,0);
		   			fdout = open(pl->outfile, O_WRONLY | O_CREAT, S_IRWXU);
		   		}
		   	}
		   	else
		   	{
		   		fdout = dup(tmpout);
		   	}
		}
		else
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}

		dup2(fdout,1);
		close(fdout);

		ret = fork();
		if(ret == 0)
		{
			// We are in child
			struct simpleCommand * cm = pl->simpleCommands[i];
			execvp(cm->arg_list[0], cm->arg_list);
			perror("execvp");
			_exit(1);
		}
		else if(ret < 0)
		{
			perror("fork");
			return;
		}
	}
	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);

	if(pl->background==0)
	{
		waitpid(ret, NULL);
	}
}

struct simpleCommand * create_simple_command(char * cmd, int max_num_args)
{
	struct simpleCommand * cm = (struct simpleCommand *)malloc(sizeof(struct simpleCommand));
	cm->max_args_allowed = max_num_args;
	cm->current_num_args = 1;
	cm->arg_list = (char **)malloc(max_num_args * sizeof(char *));
	cm->arg_list[0] = cmd;

	return cm;
}

void insert_arg(struct simpleCommand * cm, char * arg)
{
	if(cm->current_num_args < cm->max_args_allowed)
	{
		cm->arg_list[cm->current_num_args] = arg;
		cm->current_num_args+=1;
	}
	else
	{
		printf("\nExceeded the number of arguments");
	}
}