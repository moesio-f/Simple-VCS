#include "includes/controller.h"
#include "includes/search_sort.h"
#include "includes/vcs.h"

static void replaceBackSlash(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '\\') {
            str[i] = '/';
        }
    }
}

void createConfigFile() {
    FILE *config = fopen(CONFIG_FILE_NAME, "r");
    if(config != NULL) {
        fclose(config);
        return;
    }

    config = fopen(CONFIG_FILE_NAME, "w");

    char user_info[USER_SIZE] = "User\n";
    char dir[DIR_SIZE];
    sprintf(dir, "%s\n", _getcwd(NULL, DIR_SIZE));
    replaceBackSlash(dir);

    fputs(dir, config);
    fputs(user_info, config);
    fclose(config);
}

char* getDirectory() { //MUST BE FREED
    FILE *config = fopen(CONFIG_FILE_NAME, "r");
    char *dir;
    dir = malloc(sizeof(char[DIR_SIZE + 1]));
    fgets(dir, DIR_SIZE, config);
    dir[strlen(dir) - 1] = '\0';
    fclose(config);
    return dir;
}

char* getUser() { //MUST BE FREED
    FILE *config = fopen(CONFIG_FILE_NAME, "r");
    char *dir;
    dir = malloc(sizeof(char[DIR_SIZE + 1]));
    fgets(dir, DIR_SIZE, config);
    free(dir);

    char *user;
    user = malloc(sizeof(char[USER_SIZE + 1]));
    fgets(user, USER_SIZE, config);
    user[strlen(user) - 1] = '\0';
    fclose(config);
    return user;
}

void setDirectory(char *newDir){
    FILE *new_config = fopen("temp.config", "w");

    char *user = getUser();
    replaceBackSlash(newDir);
    sprintf(newDir, "%s\n", newDir);
    sprintf(user, "%s\n", user);

    fputs(newDir, new_config);
    fputs(user, new_config);

    fclose(new_config);
    free(user);

    remove(CONFIG_FILE_NAME);
    rename("temp.config", CONFIG_FILE_NAME);
}

void setUsername(char *name) {
    FILE *new_config = fopen("temp.config", "w");
    char *dir = getDirectory();

    sprintf(dir, "%s\n", dir);
    sprintf(name, "%s\n", name);

    fputs(dir, new_config);
    fputs(name, new_config);

    fclose(new_config);
    free(dir);

    remove(CONFIG_FILE_NAME);
    rename("temp.config", CONFIG_FILE_NAME);
}

Operation getOperationFromText(char *text) {
    if(text == NULL) return -1;
    if(strcmp(text, "help") == 0) return HELP;
    if(strcmp(text, "dir") == 0) return SET_DIR;
    if(strcmp(text, "user") == 0) return SET_USER;
    if(strcmp(text, "init") == 0) return VCS_INIT;
    if(strcmp(text, "commit") == 0) return VCS_COMMIT;
    if(strcmp(text, "checkout") == 0) return VCS_CHECKOUT;
    if(strcmp(text, "log") == 0) return VCS_LIST_VERSIONS;
    return -1;
}

void selectOperation(char *args[], int argc) {
    //FILE *file;
    Operation operation = getOperationFromText(args[1]);
    switch (operation) {
        case HELP: {
            help();
            break;
        }
        case SET_DIR: {
            if (argc < 3) {
                char *dir = getDirectory();
                printf("The current directory is: %s", dir);
                free(dir);
            } else {
                setDirectory(args[2]);
                char *dir = getDirectory();
                printf("The current directory is now: %s", dir);
                free(dir);
            }
            break;
        }
        case SET_USER: {
            if (argc < 3) {
                char *user = getUser();
                printf("The current user is: %s", user);
                free(user);
            } else {
                setUsername(args[2]);
                char *user = getUser();
                printf("The current user is now: %s", user);
                free(user);
            }
            break;
        }
        //case LIST_REPOS: break;
        //case SEARCH: break;
        //case SORT: break;
        case VCS_INIT: {
            if (initRepo(args[2])) {
                printf("A new repository has been created for %s\n", args[2]);
            } else {
                printf("%s already has a repository.\n", args[2]);
            }
            break;
        }
        case VCS_COMMIT: {
            char message[LINE_SIZE];
            strcpy(message, args[3]);
            for(int i = 4; i < argc; i++) {
                strcat(message, " ");
                strcat(message, args[i]);
            }
            commit(args[2], message);
            break;
        }
        case VCS_LIST_VERSIONS: {
            listVersions(args[2]);
            break;
        }
        case VCS_CHECKOUT: {
            checkout(args[2], args[3]);
            break;
        }
        default:
            printf("Invalid command. Please try again.\n");
            printf("Type \'Simple-VCS help\' to list all commands available\n");
            break;
    }
}

void listRepositories(){

}

void help() {
    printf("\nAvailable commands:\n");
    printf("help: list all commands\n");
    printf("dir [newDir]: if newDir is empty, show current directory. Otherwise, updates directory to newDir.\n");
    printf("user [newUser]: if newUser is empty, show user. Otherwise, set user to newUser\n");
    printf("init [fileName]: Initialize a new repository for the given file. (File must be on the current directory)\n");
    printf("commit [fileName] [message]: Commit the current version of the file. (message can contain blanks and multiple words)\n");
    printf("checkout [fileName] [identifier]: Go to another version of the file.\n");
    printf("log [fileName]: List all (committed) versions of the file.\n");
    printf("General usage: \'Simple-VCS command arguments\'\n");
}