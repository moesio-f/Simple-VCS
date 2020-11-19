#ifndef SIMPLE_VCS_CONTROLLER_H
#define SIMPLE_VCS_CONTROLLER_H

#include "utils.h"

typedef enum {HELP = 0, SET_DIR, SET_USER, LIST_REPOS, SEARCH, SORT, VCS_INIT, VCS_COMMIT, VCS_LIST_VERSIONS, VCS_CHECKOUT}Operation;

char* getDirectory(); //Looks for "simple-vcs.config" and returns the dir path (MUST be freed)
char* getUser(); //Looks for "simple-vcs.config" and returns the user (MUST be freed)
void createConfigFile(); //Create "simple-vcs.config" with default values (i. e., current dir and "user")
void setDirectory(char *newDir); //Update "simple-vcs.config" to set the new dir path
void setUsername(char *name); //Update "simple-vcs.config" to set the username
Operation getOperationFromText(char *text);
void selectOperation(char *args[], int argc); //Select the operation to be done (commit, search, checkout, ...)
void listRepositories(char *dir); //List all repositories for the current directory
void help(); //List all commands and the current dir

#endif //SIMPLE_VCS_CONTROLLER_H
