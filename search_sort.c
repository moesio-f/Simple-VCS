#include "includes/search_sort.h"
#include "includes/controller.h"

static bool swap(SortMode mode, char **first, char **second) {
    bool swapped = false;
    switch(mode) {
        case DECREASING: {
            if(strcmp(*first, *second) < 0) {
                char *aux = *second;
                *second = *first;
                *first = aux;
                swapped = true;
            }
            break;
        }
        case INCREASING: {
            if(strcmp(*first, *second) > 0) {
                char *aux = *second;
                *second = *first;
                *first = aux;
                swapped = true;
            }
            break;
        }
        default: break;
    }

    return swapped;
}

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
    char filePath[REPO_PATH_SIZE], *dirPath;
    dirPath = getDirectory();
    sprintf(filePath, "%s/%s", dirPath, fileName);

    FILE *file = fopen(filePath, "r");

    char **elements = malloc(MAX_LIST_ELEMENTS * sizeof(char*));
    for(int i = 0; i < MAX_LIST_ELEMENTS; i++) {
        elements[i] = malloc(LINE_SIZE * sizeof(char));
        elements[i][0] = '\0';
    }

    int currentList = 0, currentElement = 0, numberElements = 0;
    bool foundList = false;
    while(!feof(file)) {
        char line[LINE_SIZE];
        fgets(line, LINE_SIZE, file);

        if(line[0] == '-') {
            if(!foundList) {
                foundList = true;
                currentList++;
            }

            if(currentList == listNumber) {
                char *token = strtok(line, "-");
                discardNewLine(token);
                strcat(elements[currentElement], token + 1);
                currentElement++;
            }
        }

        if(feof(file) || line[0] != '-'){
            if(foundList) {
                numberElements = currentElement;
                foundList = false;
                currentElement = 0;
                if(currentList == listNumber) {
                    break;
                }
            }
        }
    }

    elements = realloc(elements, numberElements * sizeof(char*));

    bool swapped = false;
    int n = numberElements;
    do {
        swapped = false;
        for(int i = 1; i < n; i++) {
            swapped = swap(mode, &elements[i - 1], &elements[i]);
        }
        n = n - 1;
    } while (swapped);

    printf("\nSorted list:\n");
    for(int i = 0; i < numberElements; i++) {
        printf("- %s\n", elements[i]);
        free(elements[i]);
    }
    free(elements);
    free(dirPath);
    fclose(file);
}