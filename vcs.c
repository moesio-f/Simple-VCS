#include "includes/vcs.h"
#include "includes/controller.h"

//Instead of editing, open a file, store its contents on a struct and then overwrite the file
// New functions: writeRepo(Repository *repo), printRepo(Repository *repo) #Maybe new variables to hold directory

static void discardNewLine(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}

static char* discardExtension(char *str) { //MUST BE FREED
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

void initRepo(char *fileName) {
    char repo_path[REPO_PATH_SIZE], *dir, main_path[REPO_PATH_SIZE];
    char *name_no_ext = discardExtension(fileName);
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

Repository* loadRepo(char *fileName) { //MUST BE FREED
    char repo_path[REPO_PATH_SIZE], *dir, main_path[REPO_PATH_SIZE];
    char *file_no_ext = discardExtension(fileName);
    dir = getDirectory();

    sprintf(repo_path, "%s/.%s", dir, file_no_ext);
    sprintf(main_path, "%s/main.vcs", repo_path);

    free(file_no_ext);
    free(dir);

    char header[LINE_SIZE], n_commitsLine[LINE_SIZE];
    Author repoAuthor;
    int number_commits;
    Commit *commits;
    Repository *repo;

    FILE *main_vcs = fopen(main_path, "r");

    discardNewLine(fgets(header, LINE_SIZE, main_vcs));
    discardNewLine(fgets(n_commitsLine, LINE_SIZE, main_vcs));

    strcpy(repoAuthor.name, strtok(header, " "));
    strcpy(repoAuthor.date, strtok(NULL, " "));
    number_commits = atoi(n_commitsLine);
    commits = malloc(number_commits * sizeof(Commit));

    char *line = malloc(LINE_SIZE*sizeof(char));
    for(int i = 0; i < number_commits; i++) {
        fgets(line, LINE_SIZE, main_vcs);
        if(strcmp(line, "\n") == 0) {
            printf("\nEntered\n");
            char identifier[IDENTIFIER_SIZE], message[LINE_SIZE], authorInfo[LINE_SIZE], commitFileName[LINE_SIZE];
            Author commitAuthor;

            discardNewLine(fgets(identifier, IDENTIFIER_SIZE, main_vcs));
            discardNewLine(fgets(authorInfo, LINE_SIZE, main_vcs));
            discardNewLine(fgets(message, LINE_SIZE, main_vcs));
            discardNewLine(fgets(commitFileName, LINE_SIZE, main_vcs));

            strcpy(commitAuthor.name, strtok(authorInfo, " "));
            strcpy(commitAuthor.date, strtok(NULL, " "));

            strcpy(commits[i].identifier, identifier);
            strcpy(commits[i].fileName, commitFileName);
            strcpy(commits[i].message, message);
            commits[i].author = commitAuthor;
        }
    }

    free(line);
    fclose(main_vcs);

    repo = malloc(sizeof(Repository));
    repo->author = repoAuthor;
    repo->number_commits = number_commits;
    repo->commits = commits;

    return repo;
}

void listVersions(char *fileName) {

}

void commit(FILE *file, Repository *repo, char *message, char *identifier) {

}

void checkout(FILE *file, Repository *repo, char *version) {

}