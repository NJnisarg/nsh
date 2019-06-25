// Structure for the entire pipeline. Contains an array of simpleCommands seperated by Pipes
struct pipeline{
	int max_num_simpleCommands;
	int current_num_simpleCommands;
	struct simpleCommand ** simpleCommands;
	char * infile;
	char * outfile;
	int outfile_append;
	int background;

	int current_command_index;
	
};

// Structure for holding a simple command
struct simpleCommand{
	char ** arg_list;
	int max_args_allowed;
	int current_num_args;
};

// Functions for the pipeline
struct pipeline * create_pipeline(int);
void insert_simple_command(struct pipeline *, struct simpleCommand *);
void execute_pipeline(struct pipeline *);

// Functions for a simpleCommand
struct simpleCommand * create_simple_command(char *, int);
void insert_arg(struct simpleCommand *, char *);