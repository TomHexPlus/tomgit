#include "tg_main.h"



//#define _DEBUG_GIT_VER_





#ifdef _DEBUG_GIT_VER_
int main(){
	int argc = 3;
	char *argv[] = {"tomgit", "config",  "d"};
#else
int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        fprintf(stdout, "please enter a valid command\n");
        return 1;
    }
 #endif  
    return run_command(argc, argv);
}

int run_command(int argc,  char *argv[]) {
    print_command(argc, argv);
    int i;
    for (i = 0; i < NUMOFFUN ; i++) {
        if (strcmp(argv[1], cmds[i].name) == 0) {
            if (argc >= cmds[i].minArgs && argc <= cmds[i].maxArgs) {
                return cmds[i].fun(argc, argv);
            } else {
                fprintf(stderr, "Invalid number of arguments for command %s\n", argv[1]);
                fprintf(stderr, "%s", cmds[i].usage);
                return 1;
            }
        }
    }
    fprintf(stderr, "Unknown command %s\n", argv[1]);
    return 1;
}
















