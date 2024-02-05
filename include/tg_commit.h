#ifndef _TG_COMMIT
#define _TG_COMMIT 
#include "tg_global.h"


int fun_commit(int argc, char *argv[]);
int inc_last_commit_ID();
bool check_file_directory_exists(char *filepath);
int commit_staged_file(int commit_ID, char* filepath);
int track_file(char *filepath);
bool is_tracked(char *filepath);
int create_commit_file(int commit_ID, char *message);
int find_file_last_commit(char* filepath);


int fun_set(int argc, char *argv[]);
int fun_replace(int argc, char *argv[]);
int fun_remove(int argc, char *argv[]);


#endif