
#ifndef _GLOBB_H 
#define _GLOBB_H	

    #include <stdio.h>  

    #include <time.h>

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
    #include "tg_util.h"


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
        char User[MAX_LINE_CHAR] ;
        char Email[MAX_LINE_CHAR] ;
        
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
        
    extern     PRJ prjs[NUMOFPRJ]; //projects in tomgit
    extern     CMD cmds[];          // valid commands in tomgit

   extern int   last_commit_ID ; 
   extern int   current_commit_ID ;

   extern char alias[MAX_LINE_CHAR]; //alias name
   extern char aliasLnk[MAX_LINE_CHAR]; //command for alias name

   extern int curFunId;  // zero index of calling fun in tomgit

    extern char comm_mesge[MAX_LINE_CHAR];
    extern bool IsCommMsge;
    extern char comm_shcut_mesge[MAX_LINE_CHAR];

#endif
