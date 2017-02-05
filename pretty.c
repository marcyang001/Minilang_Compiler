#include <stdio.h>
#include "pretty.h"
 
void prettyEXP(EXP *e)
{ switch (e->kind) {
    case idK:
         printf ("enter here identifier ");
         printf("%s",e->val.idE);
         break;
    case intconstK:
         printf ("enter here int ");
         printf("%i",e->val.intconstE);
         break;
    case floatconstK:
         printf ("enter here float ");
         printf ("%f", e->val.floatconstE);
         break;
    case stringconstK:
         printf ("enter here string const "); 
         printf ("%s", e->val.stringconstE);
         break;
    case timesK:
         printf("(");
         prettyEXP(e->val.timesE.left);
         printf("*");
         prettyEXP(e->val.timesE.right);
         printf(")");
         break;
    case divK:
         printf("(");
         prettyEXP(e->val.divE.left);
         printf("/");
         prettyEXP(e->val.divE.right);
         printf(")");
         break;
    case plusK:
         printf("(");
         prettyEXP(e->val.plusE.left);
         printf("+");
         prettyEXP(e->val.plusE.right);
         printf(")");
         break;
    case minusK:
         printf("(");
         prettyEXP(e->val.minusE.left);
         printf("-");
         prettyEXP(e->val.minusE.right);
         printf(")");
         break;
  }
}
