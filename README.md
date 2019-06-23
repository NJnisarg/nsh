# nsh
A Linux terminal Shell

## Instructions to start the terminal
- Clone the repo: ``` git clone https://github.com/NJnisarg/nsh```
- Change directory into the repo: ``` cd nsh/```
- Run the build script: ``` chmod +x build.sh && ./build.sh```
- To run the terminal: ``` ./nsh ```

## Code organization
- The Terminal shell, has 2 major components: 1.) The Parser and 2.) The Executor
- The Parser component is built using Lex and Yacc, where as the executor is organized in the command.h and command.c files
- The Lex is used for getting a Tokenizer/scanner(lexical analyzer) and Yacc is used to get the Parser that parses the Grammar for the shell commands
- The commands that build the parser and the executor are there in build.sh file.
- In future I would like to move to a makefile

## Command syntax (Shell grammar) supported as of now:
- The shell can execute simple command with IO redirects without pipelines(No pipe support)
- The shell does not support `cd` for now.
- The shell support `exit` command for exiting the shell
