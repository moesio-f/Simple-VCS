#ifndef SIMPLE_VCS_SEARCH_SORT_H
#define SIMPLE_VCS_SEARCH_SORT_H

#include "utils.h"

typedef enum {INCREASING = 0, DECREASING}SortMode;

char* findString(char *fileName, char *target); //Find the target string on the file (returns the entire line)
void sortList(int listNumber, SortMode mode, char *fileName); //Sort a "list" of the file (Doesn't commit)

#endif //SIMPLE_VCS_SEARCH_SORT_H
