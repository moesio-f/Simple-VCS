#include "includes/controller.h"
#include "includes/search_sort.h"
#include "vcs.h"

int main(int argc, char *argv[]) {
    createConfigFile();
    selectOperation(argv, argc);
    return 0;
}
