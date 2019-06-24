# nsh
A Minimalist Linux Terminal Shell.

## Instructions to start the terminal
- Clone the repo and change directory: ``` git clone https://github.com/NJnisarg/nsh && cd nsh/```
- Run the make script: ``` make ```
- While running the `make` command, it will ask for password, since it installs the `nsh` in `/bin/nsh`. If you don't want that please, remove it from the Makefile.
- To run the terminal: ``` nsh ```
- The Makefile has 4 different targets: `all`, `build`, `install` and `clean`. `build` and `install` are ran internally by `all`. 
- To clean up everything, run `make clean`. This command will also ask for sudo password since it attempts to remove the `/bin/nsh` entry.

## Code organization
- The Terminal shell, has 2 major components: 1.) The Parser and 2.) The Executor
- The Parser component is built using Lex and Yacc, where as the executor is organized in the command.h and command.c files
- The Lex is used for getting a Tokenizer/scanner(lexical analyzer) and Yacc is used to get the Parser that parses the Grammar for the shell commands.
- The executor code and the data structures to hold the commands (Command table) are defined in the `command.h` and `command.c` files.

## Features supported (Shell commands and Grammar):
- The shell tries to mimic the `bash` shell grammar.
- It has `simple commands` implemented
- It has `I/O Redirections` implemented
- It has `Pipes and Pipelines` implemented

## Features to implement
- It does not support `cd` yet.
- It does not support `compound commands`, `lists/pipeline lists` and `shell scripting`
- It does not support `shell environment and variables`.
 