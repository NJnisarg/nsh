#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#define YY_INPUT(buf,result,max_size) result = get_input(buf, max_size);

static int get_input(char *buf, int size)
{
	char * line;

	if(feof(yyin)) return YY_NULL;
	line = readline("\033[1;36mnsh:$ \033[0m\0");
	if(!line)        return YY_NULL;
    if(strlen(line) > size-2){
       fprintf(stderr,"input line too long\n"); 
       return YY_NULL; 
   	}
    sprintf(buf,"%s\n",line);
    add_history(line);
    free(line);
    return strlen(buf);
}