
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "codegenerator.h"



void generateCode(EXP *e, FILE *cfile) {

    

}


void codegenerator(EXP *e, char *originalFileName) {

    char cfilename[strlen(originalFileName)+2];
    strcpy(cfilename, originalFileName);
    strcat(cfilename, ".c");
    FILE *cfile = fopen(cfilename, "w");

    fprintf(cfile, "#include <stdio.h>\n\n");
    fprintf(cfile, "int main(int argc, char **argv) {\n\n");
    generateCode(e, cfile);

    
    fprintf(cfile, "return 0;\n\n}\n");

    fclose(cfile);

}
