/* main.cc */

#include "heading.h"


// prototype of bison-generated parser function
int yyparse();

int main(int argc, char **argv)
{
  if ((argc > 1) && (fopen(argv[1], "r") == NULL))
  {
    printf("%s: File %s cannot be opened.\n", argv[0], argv[1]);
    exit(1);
  }
  
  yyparse();
  
  printf ("VALID\n");

  return 0;
}
