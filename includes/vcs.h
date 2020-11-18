#ifndef SIMPLE_VCS_VCS_H
#define SIMPLE_VCS_VCS_H

#include "utils.h"

bool initRepo(char *fileName); //Initialize a new repo (.filename folder with main.cvs)
Repository* loadRepo(char *fileName); //Load a repo (i. e., main.cvs)
void listVersions(char *fileName); //List all versions of the file
void commit(char *fileName, char *message); //Commit the file to the repo
void checkout(char *fileName, char *version); //Checkout to a specified version of the file

#endif //SIMPLE_VCS_VCS_H
