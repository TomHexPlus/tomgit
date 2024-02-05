#ifndef _TG_CHECKOUT_H
#define _TG_CHECKOUT_H
#include "tg_global.h"



int fun_checkout(int argc, char *argv[]);
int find_file_last_change_before_commit(char *filepath, int commit_ID);
int checkout_file(char *filepath, int commit_ID);
extern bool is_tracked(char *filepath);



#endif