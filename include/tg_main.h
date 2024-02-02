#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "tg_util.h"
#include "tg_config.h"
#include "tg_init.h"

#define MAX_WORD_CHAR  50
#define MAX_USAGE_CHAR 1000
//TODO 1 increase number of projects  and command functions in future

#define NUMOFFUN 2 //TODO number of func
#define NUMOFPRJ 1
typedef struct Command
{
    int (* fun)(int argc, char *argv[]);
    int minArgs;
    int maxArgs;
    char  name[MAX_WORD_CHAR];
    int state;                                //stat that is can act
    char usage[MAX_USAGE_CHAR];               //help of command

}CMD;

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



typedef struct Project
{
    int id;
    //TODO 1 can add projects in future
}PRJ;
PRJ prjs[NUMOFPRJ];






char branch[MAX_WORD_CHAR] = "master";
char topOfCommit[MAX_WORD_CHAR] = "head";
char gUser[] = "";
char gEmail[] = "";
int  nOfPrj = NUMOFPRJ;  ////TODO 1 can add in future
bool IsGlobUser = true;

int run_command(int argc,  char * argv[]);

