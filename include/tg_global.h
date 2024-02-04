
#ifndef _GLOBB_H 
#define _GLOBB_H	

    #include <stdio.h>  
    //tg_init: perror()
    
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>    
    //tg_init: getcwd() - chdir() - mkdir()
    
    #include <dirent.h>    
    //tg_init: DIR - DT_DIR - struct dirent - ->d_type - ->d_name -opendir()- readdir()-closedir()

    #include "tg_def.h"


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




    typedef struct Project
    {
        int id;
        //TODO 1 can add projects in future
    }PRJ;








    extern bool IsGlobUser ;
    extern char gUser[];
    extern char gEmail[];

    extern int  nOfPrj ;  
    extern int   current_prj;
    extern char current_name_prj[MAX_WORD_CHAR];


    extern char branch[MAX_WORD_CHAR] ;
    extern char topOfCommit[MAX_WORD_CHAR] ;
    extern int   last_commit_ID; 
    extern int   current_commit_ID ;
        
    extern     PRJ prjs[NUMOFPRJ];
    extern     CMD cmds[];

   extern int   last_commit_ID ; 
   extern int   current_commit_ID ;

#endif
