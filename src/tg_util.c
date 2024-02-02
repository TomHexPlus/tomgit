#include "tg_util.h"



void print_command(int argc, char * argv[]) {
  
  	fprintf(stdout, "The Number of arguments is : \"%d\" \n", argc);
    for (int i = 0; i < argc; i++)
        fprintf(stdout, "The Argument[%d] is : \"%s\" \n", i, argv[i]);
    fprintf(stdout, "\n");

}


