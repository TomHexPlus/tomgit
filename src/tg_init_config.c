
 #include "tg_init_config.h"



 int fun_init(int argc, char *argv[]) {



    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;

    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;

    do {
        // find repo.
        // DIR *dir = opendir(".");
        DIR *dir = opendir("."); //TODO
        if (dir == NULL) {
            perror("\nError opening current directory");
            return 1;
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
            if (chdir("..") != 0) return 1;
        }

    } while (strcmp(tmp_cwd, "/") != 0);

    // return to the initial cwd
    if (chdir(cwd) != 0) return 1;
        
    if (!exists) {
        if (mkdir(REPO_NAME, DIR_MAKE_MODE) != 0) return 1;
        printf("\n%s created.", REPO_NAME);
        printf("\n%s is default global username (changeable).", REPO_GLOBAL_FIRST_USER);
        printf("\n%s is default global useremail (changeable).", REPO_GLOBAL_FIRST_EMAIL);
        return create_configs(gUser,gEmail);
    } else {
        perror("\ntomgit repository has already initialized");
    }

    return 0;
}

int fun_config(int argc, char *argv[]){

    
    bool errFlag = false;

    if (strcmp(argv[2],"-global") == 0)
    {
        strcpy(gUser,argv[3]);
        strcpy(gEmail,argv[4]);
        IsGlobUser = true;
         for (size_t i = 0; i < nOfPrj; i++)
        {
            strcpy(prjs[i].User,argv[3]);
            strcpy(prjs[i].Email,argv[4]);
        }
    }else if (strncmp(argv[2],"alias.",6) == 0){
        if (IsValidAlias(argv[0],argv[3]))
        {
            strcpy(alias,(argv[2]+6));
            strcpy(aliasLnk,(argv[3]));
        }
        else errFlag = false;
               
    }
    else if (argc == 4){
        IsGlobUser = false;
        strcpy(prjs[current_prj].User,argv[2]);
        strcpy(prjs[current_prj].Email,argv[3]);
    }else{
         fprintf(stderr, "Invalid arguments for command %s\n", argv[1]);
         fprintf(stderr, "%s", cmds[curFunId].usage);
                return 1;

    }
    if (errFlag){

        fprintf(stderr, "Invalid arguments for alias in %s\n", argv[1]);
        fprintf(stderr, "%s", cmds[curFunId].usage);

        return 1;
    }
  


   return 0;
}
int create_configs(char *username, char *email) {

    FILE *file = fopen(REPO_NAME_CONFIG_F , "w");
    if (file == NULL) return 1;

    fprintf(file, "username: %s\n", username);
    fprintf(file, "email: %s\n", email);

    fprintf(file, "last_commit_ID: %d\n", last_commit_ID);
    fprintf(file, "current_commit_ID: %d\n",current_commit_ID);
    fprintf(file, "branch: %s\n", branch);

    fclose(file);

    file = fopen(REPO_NAME_STAGING_F, "w");
    fclose(file);

    file = fopen(REPO_NAME_TRACKS_F, "w");
    fclose(file);

    
    // create commits folder
    if (mkdir(REPO_NAME_COMMITS_D, DIR_MAKE_MODE) != 0) return 1;

    // create files folder
    if (mkdir(REPO_NAME_FILES_D, DIR_MAKE_MODE) != 0) return 1;

    
    return 0;
}
bool IsValidAlias(char git[],char aCmd[]){


if (strncmp(git,aCmd,strlen(git)) != 0) return false;


return true;
}

