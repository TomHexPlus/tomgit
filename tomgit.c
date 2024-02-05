//#define _DEBUG_GIT_VER_

#include "tg_init_config.h"
#include "tg_util.h"
#include "tg_add_reset.h"
#include "tg_main.h"
#include "tg_commit.h"



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

    char comm_mesge[MAX_LINE_CHAR] = "";
    char comm_shcut_mesge[MAX_LINE_CHAR] = "";
    bool IsCommMsge = false;

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
                                    \n" },
    {fun_add, 3, MAX_ARGS, "add",0 ,"\nUsage: tomgit add [file address or directory address]\
                                    \n       tomgit add -f <file1> <file2> <dir1>\
                                    \n       tomgit add -n <depth>\
                                    \n       tomgit add -redo <depth>\
                                    \n" },
    {fun_reset, 3, MAX_ARGS, "reset",0 ,"\nUsage: tomgit reset [file address or directory address]\
                                    \n       tomgit reset -f <file1> <file2> <dir1>\
                                    \n       tomgit reset -undo\
                                    \n" },  
    {fun_commit, 4, 6, "commit",0 ,"\nUsage: tomgit commit -m [commit message]\
                                    \n       tomgit commit -s shortcut-name\
                                    \n" },
    {fun_set, 6, 6, "set",0 ,      "\nUsage: tomgit set -m ”shortcut message” -s shortcut-name\
                                    \n" },
    {fun_replace, 4, 4, "replace",0,"\nUsage:  tomgit replace -m ”new shortcut message” -s shortcut-name\
                                     \n" },
    {fun_remove, 4, 4, "remove",0,   "\nUsage:  tomgit remove -s shortcut-name\
                                     \n" }                                                                                                
};



#ifdef _DEBUG_GIT_VER_
int main(){
    
  	int argc = 1;
	char *argv[] = {"tomgit", "config",  "d"};
#else
int main(int argc, char *argv[]) {

    if (!isExistRipo())
    {
        if ((argc == 2) && (!strcmp(argv[1],"init"))) return run_command(argc, argv);
        else{
                fprintf(stdout, "please first init \n");
                return 1;
            }    
    }
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

bool isExistRipo()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return false;//TODO

    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;

       do {
        // find repo.
        // DIR *dir = opendir(".");
        DIR *dir = opendir(cwd); //TODO
        if (dir == NULL) {
            perror("Error opening current directory\n");
            return false;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, REPO_NAME) == 0)
                exists = true;
        }
        closedir(dir);

        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;

        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return false;
        }

    } while (strcmp(tmp_cwd, "/") != 0);

        return exists;

    
}












// git remote add origin https://github.com/TomHexPlus/tomgit.git
// git branch -M main
 