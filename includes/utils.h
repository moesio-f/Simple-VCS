#ifndef SIMPLE_VCS_UTILS_H
#define SIMPLE_VCS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>

#define LINE_SIZE 512
#define USER_SIZE 64
#define DIR_SIZE 128
#define REPO_PATH_SIZE 256
#define IDENTIFIER_SIZE 32
#define NAME_SIZE 48
#define DATE_SIZE 24
#define CONFIG_FILE_NAME "simple-vcs.config"

typedef struct {
    char name[NAME_SIZE];
    char date[DATE_SIZE];
}Author;

typedef struct {
    char identifier[IDENTIFIER_SIZE];
    char message[LINE_SIZE];
    char fileName[IDENTIFIER_SIZE];
    Author author;
}Commit;

typedef struct {
    Author author;
    int number_commits;
    Commit *commits;
}Repository;

#endif //SIMPLE_VCS_UTILS_H