//#define _DEBUG_GIT_VER_

#include "tg_init.h"
#include "tg_util.h"
#include "tg_add.h"
#include "tg_main.h"



#define _DEBUG_GIT_VER_


    bool IsGlobUser = true;
    char gUser[MAX_LINE_CHAR] = REPO_GLOBAL_FIRST_USER;
    char gEmail[MAX_LINE_CHAR] = REPO_GLOBAL_FIRST_EMAIL;

    int  nOfPrj = NUMOFPRJ;  ////TODO 1 can add in future
    int   current_prj = 0;
    char current_name_prj[MAX_WORD_CHAR];


    char branch[MAX_WORD_CHAR] = REPO_FIRST_BRANCH;
    char topOfCommit[MAX_WORD_CHAR] = REPO_FIRST_TOPCOMMIT;
    int   last_commit_ID = 0; 
    int   current_commit_ID = 0;

    char alias[MAX_LINE_CHAR] = "";
    char aliasLnk[MAX_LINE_CHAR] = "";

    int curFunId = 0;

PRJ prjs[] = {
    {1, REPO_FIRST_USER, REPO_FIRST_EMAIL} 
};

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
    
  	int argc = 1;
	char *argv[] = {"tomgit", "config",  "d"};
#else
int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        if (alias)
        {
            return run_alias(argc, argv);
        }else{
              fprintf(stdout, "please enter a valid command\n");
             return 1;
        }
             
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
                curFunId = i;
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
int run_alias(int argc, char *argv[]){

   
      char aliasLine[MAX_LINE_CHAR]  ;
      strcpy(aliasLine,argv[0]);
      char aliasPart[MAX_ALIAS_PART][MAX_WORD_CHAR] = {""};
      int u = 0, u0 = 0, j = 0;
        
        while (sscanf(u + aliasLine, "%s%n", aliasPart[j], &u0) > 0) //??  &
        {
            j++;
            u += u0;
            if (j >= MAX_ALIAS_PART)
                break;
        }

        int argcc = j;
       
      return run_command(argcc,(char **)aliasPart);
       

}














// git remote add origin https://github.com/TomHexPlus/tomgit.git
// git branch -M main
 