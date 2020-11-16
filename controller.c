#include "includes/controller.h"

static void replaceBackSlash(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '\\') {
            str[i] = '/';
        }
    }
}

void createConfigFile() {
    FILE *config = openFile(CONFIG_FILE_NAME, "r");
    if(config != NULL) return;

    config = openFile(CONFIG_FILE_NAME, "w");

    time_t t = time(NULL);
    struct tm *localTime = localtime(&t);
    char date[100], time[100];
    char user_info[200];

    strftime(time, sizeof(time), "%H:%M:%S", localTime);
    strftime(date, sizeof(date), "%d/%m/%Y", localTime);

    sprintf(user_info, "Created by User on %s %s\n", date, time);

    char dir[DIR_SIZE];
    sprintf(dir, "%s\n", _getcwd(NULL, DIR_SIZE));
    replaceBackSlash(dir);

    fputs(dir, config);
    fputs(user_info, config);
    fclose(config);
}

FILE* openFile(char *name, char *mode) {
    return fopen(name, mode);
}

char* getDirectory() {
    FILE *config = openFile(CONFIG_FILE_NAME, "r");
    char *dir;
    dir = malloc(sizeof(char[DIR_SIZE + 1]));
    fgets(dir, DIR_SIZE, config);
    dir[strlen(dir) - 1] = '\0';
    return dir;
}

void setDirectory(char *newDir){
    char user_info[200];
    char dir[DIR_SIZE];
    FILE *config = openFile(CONFIG_FILE_NAME, "r");
    fgets(dir, DIR_SIZE, config);
    fgets(user_info, sizeof(user_info), config);

    FILE *new_config = openFile("temp.config", "w");
    sprintf(dir, "%s\n", newDir);
    fputs(dir, new_config);
    fputs(user_info, new_config);

    fclose(config);
    fclose(new_config);

    remove(CONFIG_FILE_NAME);
    rename("temp.config", CONFIG_FILE_NAME);
    remove("temp.config");
}

void setUsername(char *name) {

}

void selectOperation(Operation operation, FILE *file) {

}

void listRepositories(char *fileName){

}

void help() {

}