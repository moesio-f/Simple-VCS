#ifndef SIMPLE_VCS_CONTROLLER_H
#define SIMPLE_VCS_CONTROLLER_H

#include "utils.h"

typedef enum {SEARCH = 0, SORT, CVS_INIT, CVS_COMMIT, CVS_LIST, CVS_CHECKOUT}Operation;

FILE* openFile(char *name); //Open the file
char* getDirectory(); //Looks for "simple-vcs.config" and returns the dir path
void createConfigFile(); //Create "simple-vcs.config" with default values (i. e., current dir and "user")
void setDirectory(char *newDir); //Update "simple-vcs.config" to set the new dir path
void setUsername(char *name); //Update "simple-vcs.config" to set the username
void selectOperation(Operation operation, FILE *file); //Select the operation to be done (commit, search, checkout, ...)
void listRepositories(char *fileName); //List all repositories for the current directory
void help(); //List all commands and the current dir

#endif //SIMPLE_VCS_CONTROLLER_H
