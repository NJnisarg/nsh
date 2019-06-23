struct simpleCommand{
	char ** arg_list;
	int max_args_allowed;
	int current_num_args;
};

struct simpleCommand * create_simple_command(char *, int);
void insert_arg(struct simpleCommand *, char *);
void execute_command(struct simpleCommand *);

void show_prompt();