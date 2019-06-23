#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"command.h"

struct simpleCommand * create_simple_command(char * cmd, int max_num_args)
{
	struct simpleCommand * cm = (struct simpleCommand *)malloc(sizeof(struct simpleCommand));
	cm->max_args_allowed = max_num_args;
	cm->current_num_args = 0;
	cm->cmd = cmd;
	cm->arg_list = (char **)malloc(max_num_args * sizeof(char *));

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
	printf("\nWe are going to execute the following command:");
	printf("\nThe command is:%s", cm->cmd);
	printf("\nThe args are:");
	int i=0;
	for(i=0;i<cm->current_num_args;i++)
	{
		printf("%s ",cm->arg_list[i]);
	}
	printf("\n");
}