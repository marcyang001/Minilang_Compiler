/* main.cc */

#include "heading.h"
extern FILE *yyin;

// prototype of bison-generated parser function
int yyparse();
void resultFileName(char* inputFile, char* buffer, int length);
EXP *theexpression;


int main(int argc, char **argv)
{ 

  char *inputFile =argv[1];
  char *newPrettyFileName = NULL;
  char *originalFileName = NULL;
  
  FILE *myfile;
  FILE *prettyFile;

  // open a file handle to a particular file:
	if (argv[1] != NULL) {
    int length = strlen(inputFile);

    newPrettyFileName = (char *) malloc(sizeof(char) * (length+7));
    originalFileName = (char *) malloc(sizeof(char));

    myfile = fopen(inputFile, "r");
  
	  if (!myfile) {
		  printf("%s: File %s cannot be opened.\n", argv[0], argv[1]);
		  exit(1);
	  }
    
    resultFileName(inputFile, originalFileName, length);
    strcpy(newPrettyFileName, originalFileName);
    strcat(newPrettyFileName, ".pretty.min");

    
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
    
    printf("new file name: %s\n", newPrettyFileName);

    prettyFile = fopen(newPrettyFileName, "w");
    
    printf("pretty print to file: %s\n", newPrettyFileName);
    
    //pretty print
    prettyEXP(prettyFile, theexpression, 0);
    printf("done pretty print\n");
    fclose(prettyFile);
    SymbolTable *symbolTable;
    symbolTable = initSymbolTable();
    int satisfyTypecheck = typeCheck(theexpression, originalFileName, symbolTable);
   
    printf("\n");
    if (satisfyTypecheck == 1) {
        printf ("VALID\n");
        resultFileName(inputFile, originalFileName, length);

        // generator c code
        codegenerator(theexpression, originalFileName, symbolTable);
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
}
