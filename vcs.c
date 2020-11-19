#include "includes/vcs.h"
#include "includes/controller.h"

static void writeRepo(Repository *repo, char *main_path) {
    FILE *vcs_main = fopen(main_path, "w");
    char header[LINE_SIZE], n_commits[LINE_SIZE];

    sprintf(header, "%s %s\n", repo->author.name, repo->author.date);
    sprintf(n_commits, "%d\n", repo->number_commits);

    fputs(header, vcs_main);
    fputs(n_commits, vcs_main);

    for(int i = 0; i < repo->number_commits; i++) {
        fputs("\n", vcs_main);

        char identifier[IDENTIFIER_SIZE], message[LINE_SIZE], authorInfo[LINE_SIZE], commitFileName[LINE_SIZE];
        sprintf(identifier, "%s\n", repo->commits[i].identifier);
        sprintf(authorInfo, "%s %s\n", repo->commits[i].author.name, repo->commits[i].author.date);
        sprintf(message, "%s\n", repo->commits[i].message);
        sprintf(commitFileName, "%s\n", repo->commits[i].fileName);

        fputs(identifier, vcs_main);
        fputs(authorInfo, vcs_main);
        fputs(message, vcs_main);
        fputs(commitFileName, vcs_main);
    }

    fclose(vcs_main);
}

static void newIdentifier(char *str, int n) {
    char res[IDENTIFIER_SIZE];
    sprintf(res, "commit%d", n);
    strcpy(str, res);
}

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
    int i;
    for(i = 0; i < strlen(str); i++) {
        if(str[i] != '.') res[i] = str[i];
        else {
            res[i] = '\0';
            return res;
        }
    }
    res[i] = '\0';
    return res;
}

bool initRepo(char *fileName) {
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
        return false;
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
    return true;
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
    number_commits = atoi(n_commitsLine); // NOLINT(cert-err34-c)
    commits = malloc(number_commits * sizeof(Commit));

    char *line = malloc(LINE_SIZE*sizeof(char));
    for(int i = 0; i < number_commits; i++) {
        fgets(line, LINE_SIZE, main_vcs);
        if(strcmp(line, "\n") == 0) {
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
    Repository *repo = loadRepo(fileName);

    for(int i = 0; i < repo->number_commits; i++) {
        printf("\n********************************\n");
        printf("Identifier: %s\n", repo->commits[i].identifier);
        printf("Author: %s on %s\n", repo->commits[i].author.name, repo->commits[i].author.date);
        printf("Message: %s", repo->commits[i].message);
        printf("\n********************************\n");
    }

    free(repo);
}

void commit(char *fileName, char *message) {
    Repository *repo = loadRepo(fileName);
    char *file_no_ext = discardExtension(fileName);

    repo->number_commits++;
    repo->commits = realloc(repo->commits, repo->number_commits*sizeof(Commit));

    char *user = getUser();
    char date[40];
    Author commitAuthor;
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(date, sizeof(date), "%d/%m/%Y", tm);
    strcpy(commitAuthor.name, user);
    strcpy(commitAuthor.date, date);

    char identifier[IDENTIFIER_SIZE], commitFileName[IDENTIFIER_SIZE];
    newIdentifier(identifier, repo->number_commits - 1);
    sprintf(commitFileName, "%s.txt", identifier);

    strcpy(repo->commits[repo->number_commits - 1].identifier, identifier);
    strcpy(repo->commits[repo->number_commits - 1].message, message);
    strcpy(repo->commits[repo->number_commits - 1].fileName, commitFileName);
    repo->commits[repo->number_commits - 1].author = commitAuthor;

    char repo_path[REPO_PATH_SIZE], main_path[REPO_PATH_SIZE], originalFilePath[REPO_PATH_SIZE], commitFilePath[REPO_PATH_SIZE], *dir;
    dir = getDirectory();
    sprintf(repo_path, "%s/.%s", dir, file_no_ext);
    sprintf(main_path, "%s/main.vcs", repo_path);
    sprintf(originalFilePath, "%s/%s", dir, fileName);
    sprintf(commitFilePath, "%s/%s", repo_path, commitFileName);
    
    writeRepo(repo, main_path);
    CopyFileA(originalFilePath, commitFilePath, FALSE);

    free(file_no_ext);
    free(user);
    free(repo);
    free(dir);
}

void checkout(char *fileName, char *version) {
    Repository *repo = loadRepo(fileName);
    char *file_no_ext = discardExtension(fileName);

    char repo_path[REPO_PATH_SIZE], originalFilePath[REPO_PATH_SIZE], commitFilePath[REPO_PATH_SIZE], *dir;
    dir = getDirectory();
    sprintf(repo_path, "%s/.%s", dir, file_no_ext);
    sprintf(originalFilePath, "%s/%s", dir, fileName);

    for(int i = 0; i < repo->number_commits; i++) {
        if(strcmp(repo->commits[i].identifier, version) == 0) {
            sprintf(commitFilePath, "%s/%s", repo_path, repo->commits[i].fileName);
            break;
        }
    }

    DeleteFileA(originalFilePath);
    CopyFileA(commitFilePath, originalFilePath, FALSE);

    free(dir);
    free(file_no_ext);
    free(repo);
}