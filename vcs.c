#include "includes/vcs.h"
#include "includes/controller.h"

static char* discardExtension(char *str) {
    char *res;
    res = malloc(strlen(str)*sizeof(char));
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] != '.') res[i] = str[i];
        else {
            res[i] = '\0';
            return res;
        }
    }
}

void initRepo(char *name) {
    char repo_path[2*DIR_SIZE], *dir, main_path[2*DIR_SIZE];
    char *name_no_ext = discardExtension(name);
    dir = getDirectory();

    sprintf(repo_path, "%s/.%s", dir, name_no_ext);
    sprintf(main_path, "%s/main.vcs", repo_path);

    free(dir);
    free(name_no_ext);

    FILE *vcs_main = fopen(main_path, "r");
    if(vcs_main != NULL) {
        fclose(vcs_main);
        return;
    }

    CreateDirectoryA(repo_path, NULL);
    SetFileAttributesA(repo_path, FILE_ATTRIBUTE_HIDDEN);

    vcs_main = fopen(main_path, "w");

    char *user = getUser();
    char header[LINE_SIZE], date[40];
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(date, sizeof(date), "%d/%m/%Y", tm);
    sprintf(header, "%s %s\n", user, date);

    fputs(header, vcs_main);
    fputs("0", vcs_main);

    free(user);
    fclose(vcs_main);
}

Repository* loadRepo(char *fileName) {

}

void listVersions(char *fileName) {

}

void commit(FILE *file, Repository *repo, char *message, char *tag) {

}

void checkout(FILE *file, Repository *repo, char *version) {

}