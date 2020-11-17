#ifndef SIMPLE_VCS_VCS_H
#define SIMPLE_VCS_VCS_H

#include "utils.h"

void initRepo(char *name); //Initialize a new repo (.filename folder with main.cvs)
Repository* loadRepo(char *fileName); //Load a repo (i. e., main.cvs)
void listVersions(char *fileName); //List all versions of the file
void commit(FILE *file, Repository *repo, char *message, char *tag); //Commit the file to the repo
void checkout(FILE *file, Repository *repo, char *version); //Checkout to a specified version of the file

#endif //SIMPLE_VCS_VCS_H
