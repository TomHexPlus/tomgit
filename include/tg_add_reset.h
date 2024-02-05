
#ifndef _TG_ADD_H
#define _TG_ADD_H 
#include "tg_global.h"

// for add command
 int fun_add(int argc, char *argv[]);
 int add_to_staging(char *filepath);
 int run_add_f(int argc, char *argv[]);
 int run_add_n(int argc, char *argv[]);

 int run_add_wild(int argc, char *argv[]);

 int run_add_redo(int argc, char *argv[]);


//for rest command

 int fun_reset(int argc, char *argv[]);
 int remove_from_staging(char *filepath);
 int run_reset_wild(int argc, char *argv[]);
int run_reset_f(int argc, char *argv[]);
 int run_reset_redo(int argc, char *argv[]);

  int act_on_wild(char *filepath);


#endif
