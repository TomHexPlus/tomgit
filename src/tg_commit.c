#include "tg_commit.h"



    int fun_commit(int argc, char *argv[]) {
    print_command(argc, argv);
    
     if(!IsCommMsge)
         if ((strcmp(argv[2], "-m"))){

        fprintf(stderr,"error : error in command\n");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
         }
char message[MAX_MESSAGE_LENGTH];
    strcpy(message, argv[3]);
    //error handling
    if (strlen(message) > LIMIT_MESSAGE) {
        fprintf(stderr,"message must less than 72 char");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
    }
    // error of absent of message and withspase in main fun done

    if(IsCommMsge)//short cut message
    {
        if (strcmp(argv[2],"-s"))
        {
            if (strcmp(argv[3],comm_shcut_mesge) == 0)
            {
                strcpy(message,comm_mesge);
            }
            
        
        }
        




    }




    int commit_ID = inc_last_commit_ID();
    if (commit_ID == -1) return 1;
    
    FILE *file = fopen(REPO_NAME_STAGING_F, "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_CHAR];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);

        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        
        if (!check_file_directory_exists(line)) {
            char dir_path[MAX_FILENAME_LENGTH];
            strcpy(dir_path, REPO_NAME_FILES_D);
            strcat(dir_path, line);
            if (mkdir(dir_path, DIR_MAKE_MODE) != 0) return 1;
        }
        printf("commit %s\n", line);
        commit_staged_file(commit_ID, line);
        track_file(line);
    }
    fclose(file); 
    
    // free staging
    file = fopen(REPO_NAME_STAGING_F, "w");
    if (file == NULL) return 1;
    fclose(file);

    create_commit_file(commit_ID, message);
    fprintf(stdout, "commit successfully with commit ID %d\n", commit_ID);
    fprintf(stdout, "commit message: %s\n", message);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("%s", asctime(tm));


    
    return 0;
}

// returns new commit_ID
int inc_last_commit_ID() {
    FILE *file = fopen(REPO_NAME_CONFIG_F, "r");
    if (file == NULL) return -1;
    
    FILE *tmp_file = fopen(REPO_NAME_TMP_CONFIG_F, "w");
    if (tmp_file == NULL) return -1;

    int last_commit_ID;
    char line[MAX_LINE_CHAR];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line,  "last_commit_ID", 14) == 0) {
            sscanf(line, "last_commit_ID: %d\n", &last_commit_ID);
            last_commit_ID++;
            fprintf(tmp_file, "last_commit_ID: %d\n", last_commit_ID);

        } else fprintf(tmp_file, "%s", line);
    }
    fclose(file);
    fclose(tmp_file);

    remove(REPO_NAME_CONFIG_F);
    rename(REPO_NAME_TMP_CONFIG_F, REPO_NAME_CONFIG_F);
    return last_commit_ID;
}

bool check_file_directory_exists(char *filepath) {
    DIR *dir = opendir(REPO_NAME_FILES_D);
    struct dirent *entry;
    if (dir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, filepath) == 0) return true;
    }
    closedir(dir);

    return false;
}

int commit_staged_file(int commit_ID, char* filepath) {
    FILE *read_file, *write_file;
    char read_path[MAX_FILENAME_LENGTH];
    strcpy(read_path, filepath);
    char write_path[MAX_FILENAME_LENGTH];
    strcpy(write_path, REPO_NAME_FILES_D);
    strcat(write_path, filepath);
    strcat(write_path, "/");
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(write_path, tmp);

    read_file = fopen(read_path, "r");
    if (read_file == NULL) return 1;

    write_file = fopen(write_path, "w");
    if (write_file == NULL) return 1;

    char buffer;
    buffer = fgetc(read_file);
    while(buffer != EOF) {
        fputc(buffer, write_file);
        buffer = fgetc(read_file);
    }
    fclose(read_file);
    fclose(write_file);

    return 0;
}

int track_file(char *filepath) {
    if (is_tracked(filepath)) return 0;

    FILE *file = fopen(REPO_NAME_TRACKS_F, "a");
    if (file == NULL) return 1;
    fprintf(file, "%s\n", filepath);
    return 0;
}

bool is_tracked(char *filepath) {
    FILE *file = fopen(REPO_NAME_TRACKS_F, "r");
    if (file == NULL) return false;
    char line[MAX_LINE_CHAR];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);

        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        
        if (strcmp(line, filepath) == 0) return true;

    }
    fclose(file); 

    return false;
}

int create_commit_file(int commit_ID, char *message) {
    char commit_filepath[MAX_FILENAME_LENGTH];
    strcpy(commit_filepath, REPO_NAME_COMMITS_D);
    char tmp[10];
    sprintf(tmp, "%d", commit_ID);
    strcat(commit_filepath, tmp);

    FILE *file = fopen(commit_filepath, "w");
    if (file == NULL) return 1;

    fprintf(file, "message: %s\n", message);
    fprintf(file, "files:\n");
    
    DIR *dir = opendir(".");
    struct dirent *entry;
    if (dir == NULL) {
        perror("Error opening current directory");
        return 1;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG && is_tracked(entry->d_name)) {
            int file_last_commit_ID = find_file_last_commit(entry->d_name);
            fprintf(file, "%s %d\n", entry->d_name, file_last_commit_ID);
        }
    }
    closedir(dir); 
    fclose(file);
    return 0;
}

int find_file_last_commit(char* filepath) {
    char filepath_dir[MAX_FILENAME_LENGTH];
    strcpy(filepath_dir,REPO_NAME_FILES_D);
    strcat(filepath_dir, filepath);

    int max = -1;
    
    DIR *dir = opendir(filepath_dir);
    struct dirent *entry;
    if (dir == NULL) return 1;

    while((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            int tmp = atoi(entry->d_name);
            max = max > tmp ? max: tmp;
        }
    }
    closedir(dir);

    return max;
}

int fun_set(int argc, char *argv[]){
    print_command(argc, argv);
    //error handling do in main with number of args
    if (strlen(argv[3]) > LIMIT_MESSAGE){

        printf("error : message more than 72 char\n");
        return 1;
    }

    strcpy(comm_mesge ,argv[3]);
    strcpy(comm_shcut_mesge, argv[5]);
    IsCommMsge = true;
    return 0;


    
}
int fun_replace(int argc, char *argv[]){
    print_command(argc, argv);
    //error handling do in main with number of args
    if ( (strcmp(argv[2], "-m") || strcmp(argv[4] , "-s"))){

        fprintf(stderr,"error : error in command\n");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
    }
    if(!IsCommMsge){

        fprintf(stderr,"error : don't exist shortcut message\n");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
    }
    if (strlen(argv[3]) > LIMIT_MESSAGE){

        fprintf(stderr,"error : message more than 72 char\n");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
    }
    if ((strlen(argv[5]) , comm_shcut_mesge) != 0){

        fprintf(stderr,"error : dont exist shcut name\n");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
    }

    strcpy(comm_mesge ,argv[3]);
   
    return 0;
}
int fun_remove(int argc, char *argv[]){
    print_command(argc, argv);

     if ((strlen(argv[3]) , comm_shcut_mesge) != 0){

        fprintf(stderr,"error : dont exist shcut name\n");
        fprintf(stderr, "%s", cmds[curFunId].usage);
        return 1;
    }
    
    IsCommMsge=false;
    comm_mesge[0]='\0';
    comm_shcut_mesge[0]='\0';

}
