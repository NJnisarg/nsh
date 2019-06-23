#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
struct simpleCommand * create_simple_command(char * cmd, int max_num_args)
{
	struct simpleCommand * cm = (struct simpleCommand *)malloc(sizeof(struct simpleCommand));
	cm->max_args_allowed = max_num_args;
	cm->current_num_args = 1;
	cm->arg_list = (char **)malloc(max_num_args * sizeof(char *));
	cm->arg_list[0] = cmd;
	cm->infile = NULL;
	cm->outfile = NULL;

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

void execute_command(struct simpleCommand * cm)
{
	// Informational Debugging
	// Uncomment if you want to see the contents of the command

	// printf("\nWe are going to execute the following command:");
	// printf("\nThe command is:%s", cm->arg_list[0]);
	// printf("\nThe args are:");
	// int i=0;
	// for(i=0;i<cm->current_num_args;i++)
	// {
	// 	printf("%s ",cm->arg_list[i]);
	// }
	// printf("\n");

	// Execute the command

	// First do the IO Redirections
	int tmpin = dup(0);
	int tmpout = dup(1);
	
	int fdin;
	int fdout;

	if(cm->infile)
	{
		fdin = open(cm->infile, O_RDONLY);
	}
	else{
		fdin = dup(tmpin);
	}
	dup2(fdin, 0);
   	close(fdin);

   	if(cm->outfile)
   	{
   		fdout = open(cm->outfile, O_WRONLY | O_CREAT, S_IRWXU);
   	}
   	else
   	{
   		fdout = dup(tmpout);
   	}

   	dup2(fdout,1);
	close(fdout);

	int ret;
	ret = fork();
	if(ret == 0)
	{
		// We are in child
		execvp(cm->arg_list[0], cm->arg_list);
		perror("execvp");
		_exit(1);
	}
	else if(ret < 0)
	{
		perror("fork");
		return;
		waitpid(ret, NULL);
	}
	waitpid(ret, NULL);
	
	 //restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
}

void show_prompt()
{
	printf("nsh>");
}