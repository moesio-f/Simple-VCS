#include "includes/controller.h"
#include "search_sort.h"
#include "vcs.h"

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

char* getDirectory() {
    FILE *config = fopen(CONFIG_FILE_NAME, "r");
    char *dir;
    dir = malloc(sizeof(char[DIR_SIZE + 1]));
    fgets(dir, DIR_SIZE, config);
    dir[strlen(dir) - 1] = '\0';
    fclose(config);
    return dir;
}

char* getUser() {
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
    else if(strcmp(text, "dir") == 0) return SET_DIR;
    else if(strcmp(text, "user") == 0) return SET_USER;
    return -1;
}

void selectOperation(char *args[], int argc) {
    //FILE *file;
    Operation operation = getOperationFromText(args[1]);

    switch (operation) {
        case HELP:
            help();
            break;
        case SET_DIR:
            if(argc < 3) {
                char *dir = getDirectory();
                printf("The current directory is: %s", dir);
                free(dir);
            }
            else {
                setDirectory(args[2]);
                char *dir = getDirectory();
                printf("The current directory is now: %s", dir);
                free(dir);
            }
            break;
        case SET_USER:
            if(argc < 3) {
                char *user = getUser();
                printf("The current user is: %s", user);
                free(user);
            }
            else {
                setUsername(args[2]);
                char *user = getUser();
                printf("The current user is now: %s", user);
                free(user);
            }
            break;
        case LIST_REPOS: break;
        case SEARCH: break;
        case SORT: break;
        case VCS_INIT: break;
        case VCS_COMMIT: break;
        case VCS_LIST_VERSIONS: break;
        case VCS_CHECKOUT: break;
        default:
            printf("Invalid command. Please try again.\n");
            printf("Type \'Simple-VCS help\' to list all commands available\n");
            break;
    }
}

void listRepositories(char *fileName){

}

void help() {
    printf("Available commands:\n");
    printf("help: list all commands\n");
    printf("dir [newDir]: if newDir is empty, show current directory. Otherwise, updates directory to newDir.\n");
    printf("user [newUser]: if newUser is empty, show user. Otherwise, set user to newUser\n");
    printf("General usage: \'Simple-VCS command arguments\'");
}