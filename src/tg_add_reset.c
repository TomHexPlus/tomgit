#include "tg_add_reset.h"


int fun_add(int argc, char *argv[]){


    if(strcmp(argv[2], "-f") == 0){
        run_add_f( argc, argv);

    }else if (strcmp(argv[2], "-n") == 0){
        run_add_n(argc, argv);
        
    }else if (strstr(argv[2],"*") != NULL) {
        run_add_wild(argc, argv);
    }else if (strcmp(argv[2], "-redo") == 0){
        run_add_redo(argc, argv);
    }else{

                // get root path        
                char* path = realpath(argv[2], NULL);
                //error check
                if(path == NULL){ 
                    printf("cannot find file with name[%s]\n", argv[2]);
                } else{

                //the path is file or dir 
                // if dir reapet  add_to_staging(path) for all files only one level depth //TODO more depth
                struct stat st;
                if (stat(argv[2], &st) == -1) {
                    perror("no shuch file or dir\n");
                    return 1;
                }
                //path Is dir name
                if (S_ISDIR(st.st_mode)) {
                    //printf("%s is a directory.\n", argv[2]);
                
                    
                    DIR *dir = opendir(path);
                    struct dirent *entry;
                        if (dir == NULL) {
                            perror("Error opening current directory\n");
                            return 1;
                        }
                        while ((entry = readdir(dir)) != NULL) {
                            if (entry->d_type == DT_REG)
                            {
                                path = realpath(entry->d_name, NULL);
                //call add fun for each file
                                add_to_staging(path);
                            }
                                
                        }
                        closedir(dir);


                //path Is file name
                } else if (S_ISREG(st.st_mode)) {
                    //printf("%s is a file.\n", argv[2]);
                // call add fun for file
                    add_to_staging(path);

                } else {
                    printf("%s is not a directory or a file.\n", argv[2]);
                }
          
                    free(path);
                } 

         }

   return 0;
}


 int add_to_staging(char *filepath) {
 FILE *file = fopen(REPO_NAME_STAGING_F, "r");
    if (file == NULL) return 1;
    char line[MAX_LINE_CHAR];
 
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);

        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }

        if (strcmp(filepath, line) == 0) return 0;
    }
    fclose(file);
    
    file = fopen(REPO_NAME_STAGING_F,"a");
    if (file == NULL) return 1;

    fprintf(file, "%s\n", filepath);
    fclose(file);

    return 0;


}



        int run_add_f(int argc, char *argv[]){
            printf ("under construct, be patiant and kindly person\n");
            return 0;
        }
        int run_add_n(int argc, char *argv[]){
            printf ("under construct, be patiant and kindly person\n");
            return 0;
        }
        int run_add_wild(int argc, char *argv[]){
            printf ("under construct, be patiant and kindly person\n");
            return 0;
        }
        int run_add_redo(int argc, char *argv[]){
            printf ("under construct, be patiant and kindly person\n");
            return 0;

        }        



int fun_reset(int argc, char *argv[]) {

    if(strcmp(argv[2], "-f") == 0){
        run_reset_f( argc, argv);
    }else if (strstr(argv[2],"*") != NULL){
        run_reset_wild(argc, argv);
    }else if (strcmp(argv[2], "-redo") == 0){
        run_reset_redo(argc, argv);
    }else{

 // get root path        
                char* path = realpath(argv[2], NULL);
                //error check
                if(path == NULL){ 
                    printf("cannot find file with name[%s]\n", argv[2]);
                } else{

                //the path is file or dir 
                // if dir reapet  add_to_staging(path) for all files only one level depth //TODO more depth
                struct stat st;
                if (stat(argv[2], &st) == -1) {
                    perror("no shuch file or dir\n");
                    return 1;
                }
                //path Is dir name
                if (S_ISDIR(st.st_mode)) {
                    //printf("%s is a directory.\n", argv[2]);
                
                    
                    DIR *dir = opendir(path);
                    struct dirent *entry;
                        if (dir == NULL) {
                            perror("Error opening current directory\n");
                            return 1;
                        }
                        while ((entry = readdir(dir)) != NULL) {
                            if (entry->d_type == DT_REG)
                            {
                                path = realpath(entry->d_name, NULL);
                //call reset fun for each file
                                remove_from_staging(argv[2]);
                            }
                                
                        }
                        closedir(dir);


                //path Is file name
                } else if (S_ISREG(st.st_mode)) {
                    //printf("%s is a file.\n", argv[2]);
                // call reset fun for file
                    remove_from_staging(argv[2]);

                } else {
                    printf("%s is not a directory or a file.\n", argv[2]);
                }
          
                    free(path);
                } 

         }
    
    return 0;
}

int remove_from_staging(char *filepath) {
    FILE *file = fopen(REPO_NAME_STAGING_F, "r");
    if (file == NULL) return 1;
    
    FILE *tmp_file = fopen(REPO_NAME_TMP_STAGING_F, "w");
    if (tmp_file == NULL) return 1;

    char line[MAX_LINE_CHAR];
    while (fgets(line, sizeof(line), file) != NULL) {
        int length = strlen(line);

        // remove '\n'
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }

        if (strcmp(filepath, line) != 0) fputs(line, tmp_file);
    }
    fclose(file);
    fclose(tmp_file);

    remove(REPO_NAME_STAGING_F);
    rename(REPO_NAME_TMP_STAGING_F, REPO_NAME_STAGING_F);
    return 0;
}
int run_reset_f(int argc, char *argv[]){
     printf ("under construct, be patiant and kindly person\n");
            return 0;

    
}
int run_reset_redo(int argc, char *argv[]){
     printf ("under construct, be patiant and kindly person\n");
            return 0;

    
}  
int  run_reset_wild(int argc, char *argv[]){
     printf ("under construct, be patiant and kindly person\n");
            return 0;

    
}  

        




