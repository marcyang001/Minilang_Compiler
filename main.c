/* main.cc */

#include "heading.h"


// prototype of bison-generated parser function
int yyparse();
EXP *theexpression;

int main(int argc, char **argv)
{
  if ((argc > 1) && (fopen(argv[1], "r") == NULL))
  {
    printf("%s: File %s cannot be opened.\n", argv[0], argv[1]);
    exit(1);
  }
  
  yyparse();
  printf("\nThe result of evaluating:\n");
  prettyEXP(theexpression);
  printf("\n");
  printf ("VALID\n");

  return 0;
}
