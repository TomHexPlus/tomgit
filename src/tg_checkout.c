#include "tg_checkout.h"


int fun_checkout(int argc, char *argv[]) {
   print_command(argc, argv);
   //error handling arg numbers in main
    
    int commit_ID = atoi(argv[2]);

    DIR *dir = opendir(".");
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
            checkout_file(entry->d_name, find_file_last_change_before_commit(entry->d_name, commit_ID));
        }
    }
    closedir(dir);

    return 0;
}

int find_file_last_change_before_commit(char *filepath, int commit_ID) {
    char filepath_dir[MAX_FILENAME_LENGTH];
    strcpy(filepath_dir, REPO_NAME_FILES_D);
    strcat(filepath_dir, filepath);

    int max = -1;
    
    DIR *dir = opendir(filepath_dir);
    struct dirent *entry;
    if (dir == NULL) return 1;

    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            int tmp = atoi(entry->d_name);
            if (tmp > max && tmp <= commit_ID) {
                max = tmp;
            }
        }
    }
    closedir(dir);

    return max;
}

int checkout_file(char *filepath, int commit_ID) {
   
    if(commit_ID < 0) return 1;
    //TODO for don't writing if change of file not commited


    char src_file[MAX_FILENAME_LENGTH];
    strcpy(src_file,REPO_NAME_FILES_D);
    strcat(src_file, filepath);
    char tmp[10];
    sprintf(tmp, "/%d", commit_ID);
    strcat(src_file, tmp);

    FILE *read_file = fopen(src_file, "r");
    if (read_file == NULL) return 1;
    FILE *write_file = fopen(filepath, "w");
    if (write_file == NULL) return 1;
    
    char line[MAX_LINE_CHAR];

    while (fgets(line, sizeof(line), read_file) != NULL) {
        fprintf(write_file, "%s", line);
    }
    
    fclose(read_file);
    fclose(write_file);

    return 0;
}
//