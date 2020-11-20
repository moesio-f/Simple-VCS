#include "includes/search_sort.h"
#include "includes/controller.h"

char* findString(char *fileName, char *target) { //MUST BE FREED!
    char filePath[REPO_PATH_SIZE], *dirPath;
    dirPath = getDirectory();
    sprintf(filePath, "%s/%s", dirPath, fileName);

    FILE *file = fopen(filePath, "r");

    char *result = malloc(LINE_SIZE * sizeof(char));
    sprintf(result, "\"%s\" not found in %s", target, fileName);

    int nLine = 1;
    bool found = false;
    while(!feof(file) && !found) {
        char line[LINE_SIZE], auxLine[LINE_SIZE];
        fgets(line, LINE_SIZE, file);
        strcpy(auxLine, line);
        discardNewLine(auxLine);

        char *token = strtok(line, " ");
        while(token != NULL && !found) {
            discardNewLine(token);
            if(strcmp(target, token) == 0) {
                found = true;
                sprintf(result, "Line %d: \"%s\"", nLine, auxLine);
            }
            token = strtok(NULL, " ");
        }

        nLine++;
    }

    free(dirPath);
    fclose(file);
    return result;
}

void sortList(int listNumber, SortMode mode, char *fileName) {

}