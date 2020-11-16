#ifndef SIMPLE_CVS_UTILS_H
#define SIMPLE_CVS_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

#endif //SIMPLE_CVS_UTILS_H
