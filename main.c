#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dependencies/transpiler.h"
#include "dependencies/lexer.h"

int main(int argc, char *argv[]) {
    
    char buff[256];
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <carbon file>\n", argv[0]);
        return 1;
    }

    char *file_extension = strrchr(argv[1], '.');

    if(strcmp(file_extension, ".crb") != 0) {
        fprintf(stderr, "Error: CarbonScript File must have a .crb file extension\n");
        return 1;
    }

    FILE *carbonScript = fopen(argv[1], "r");
    if (!carbonScript) {
        perror("Error opening input file");
        return 1;
    }

    while (fgets(buff, sizeof(buff), carbonScript)) {
        line_parser(buff, carbonScript);
    }

    fclose(carbonScript);

    // int k = sizeof(buff) / sizeof(buff[0]);

    // for (int i = 0; i < k; i++)
    // {
    //     printf("%c", buff[i]);
    // }
    
    return 0;
}