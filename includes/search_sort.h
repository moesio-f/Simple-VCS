#ifndef SIMPLE_VCS_SEARCH_SORT_H
#define SIMPLE_VCS_SEARCH_SORT_H

#include "utils.h"

typedef enum {INCREASING = 0, DECREASING}SortMode;

char* findString(char *target, FILE *file); //Find the target string on the file (returns the entire line)
bool sortList(int startLine, SortMode mode, FILE *file); //Sort a "list" of the file (Doesn't commit)

#endif //SIMPLE_VCS_SEARCH_SORT_H
