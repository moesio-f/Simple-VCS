#include "includes/controller.h"

int main(int argc, char *argv[]) {
    createConfigFile();
    selectOperation(argv, argc);
    return 0;
}
