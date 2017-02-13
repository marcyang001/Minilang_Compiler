/* main.cc */

#include "heading.h"
extern FILE *yyin;

// prototype of bison-generated parser function
int yyparse();
void resultFileName(char* inputFile, char* bufferc, int length);
EXP *theexpression;


int main(int argc, char **argv)
{ 

  char *inputFile =argv[1];
  char *newPrettyFileName = NULL;
  char *originalFileName = NULL;
  char *symbolTableFileName = NULL;
  char *cfilename = NULL;

  FILE *myfile;
  FILE *prettyFile;

  // open a file handle to a particular file:
	if (argv[1] != NULL) {
    int length = strlen(inputFile);

    originalFileName = (char *) malloc(sizeof(char)*(length-4+6));
    newPrettyFileName = (char *) malloc(sizeof(char) * (length+7+6));
    symbolTableFileName = (char *) malloc(sizeof(char) * (length-4+11+6));
    cfilename = (char *) malloc(sizeof(char) * (length-4+2+7));

    myfile = fopen(inputFile, "r");
  
	  if (!myfile) {
		  printf("%s: File %s cannot be opened.\n", argv[0], argv[1]);
		  exit(1);
	  }
    printf("input file name %s \n", inputFile);
    // delete the extension and take the input file name
    // store into originalFileName
    resultFileName(inputFile, originalFileName, length);
     
    // create foo.pretty.min file name
    strcpy(newPrettyFileName, originalFileName);
    strcat(newPrettyFileName, ".pretty.min");

    strcpy(symbolTableFileName, originalFileName);
    strcat(symbolTableFileName, ".symbol.txt");

    // create c file name
    strcpy(cfilename, originalFileName);
    strcat(cfilename, ".c");




    printf("pretty print to file: %s\n", newPrettyFileName);
    printf("symbol table : %s\n", symbolTableFileName);
    printf("c file : %s", cfilename);

	  // set flex to read from it instead of defaulting to STDIN:
	  yyin = myfile;
    // parse through the input until there is no more:
	  do {
		  yyparse();
	  } while (!feof(yyin));

    fclose(myfile);
    printf("\nThe result of evaluating:\n");
    
    if (newPrettyFileName == NULL) {
      
      newPrettyFileName = "a.output.min";
      strcpy(originalFileName, "a.output");

      
    }

    //pretty print
    prettyFile = fopen(newPrettyFileName, "w");
    prettyEXP(prettyFile, theexpression, 0);
    printf("done pretty print\n");
    fclose(prettyFile);

    // type check
    SymbolTable *symbolTable;
    symbolTable = initSymbolTable();
    int satisfyTypecheck = typeCheck(theexpression, symbolTableFileName, symbolTable);
   
    printf("\n");
    if (satisfyTypecheck == 1) {
       printf ("VALID\n");
      FILE *cfile = fopen(cfilename, "w");
      //generator c code
      codegenerator(theexpression, cfile, symbolTable);
      fclose(cfile);
    }
    else {
     printf ("INVALID\n");
    }
  }
  else {
    printf("Please give an input file\n");
  }
  
  return 0;
}

void resultFileName(char* inputFile, char* buffer, int length) {

   int i = 0;
  while (i < length) {

    if (inputFile[i] == '.' && inputFile[i+1] == 'm' && inputFile[i+2] == 'i' && inputFile[i+3]=='n') {
      break;
    }
    else {
        buffer[i] = inputFile[i];    
    }

    i++;
  }
  buffer[i] = '\0';

}
