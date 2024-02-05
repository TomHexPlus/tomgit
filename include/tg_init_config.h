
#ifndef _TG_INIT_H
#define _TG_INIT_H 
#include "tg_global.h"



int fun_init(int argc, char *argv[]);
int fun_config(int argc, char *argv[]);
int create_configs(char *username, char *email);

bool IsValidAlias(char git[],char aCmd[]);
int write_in_config();

#endif