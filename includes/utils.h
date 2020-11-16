#ifndef SIMPLE_VCS_UTILS_H
#define SIMPLE_VCS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define LINE_SIZE 512
#define DIR_SIZE 128
#define CONFIG_FILE_NAME "simple-vcs.config"

typedef struct {
    char *name;
    char *date;
}Author;

typedef struct {
    char *identifier;
    char *message;
    char *fileName;
    Author author;
}Commit;

typedef struct {
    Author author;
    int number_commits;
    Commit *commits;
}Repository;

#endif //SIMPLE_VCS_UTILS_H