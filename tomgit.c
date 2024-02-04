//#include "tg_global.h"

#include "tg_init.h"
#include "tg_util.h"
#include "tg_add.h"
#include "tg_main.h"



//#define _DEBUG_GIT_VER_


//   typedef struct Command
//     {
//         int (* fun)(int argc, char *argv[]);
//         int minArgs;
//         int maxArgs;
//         char  name[MAX_WORD_CHAR];
//         int state;                                //stat that is can act
//         char usage[MAX_USAGE_CHAR];               //help of command

//     }CMD;




    // typedef struct Project
    // {
    //     int id;
    //     //TODO 1 can add projects in future
    // }PRJ;
    // PRJ prjs[NUMOFPRJ];







    bool IsGlobUser = true;
    char gUser[] = "";
    char gEmail[] = "";

    int  nOfPrj = NUMOFPRJ;  ////TODO 1 can add in future
    int   current_prj;
    char current_name_prj[MAX_WORD_CHAR];


    char branch[MAX_WORD_CHAR] = "master";
    char topOfCommit[MAX_WORD_CHAR] = "head";
    int   last_commit_ID = 0; 
    int   current_commit_ID = 0;

PRJ prjs[NUMOFPRJ];

CMD cmds[] = {
    {fun_config, 4, 5, "config",0 ,"\nUsage: tomgit config –global user.name \"a@b.com\"\
                                    \n       tomgit config –global user.email \"Tom\"\
                                    \n       tomgit config  user.name \"a@b.com\"\
                                    \n       tomgit config  user.email \"a@b.com\"\
                                    \n       tomgit config (–global) alias.<alias-name> \"a command\"\
                                    \n" },
    {fun_init, 2, 2, "init",0 ,"\nUsage: tomgit init\
                                    \n" }                                
    
};


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
    //print_command(argc, argv);
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
















// git remote add origin https://github.com/TomHexPlus/tomgit.git
// git branch -M main
 