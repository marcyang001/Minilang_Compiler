#include <stdio.h>
#include "pretty.h"
 
void prettyEXP(EXP *e)
{ 
    switch (e->kind) {
        case idK:
             //printf ("enter here identifier ");
             printf("%s",e->val.idE);
             break;
        case stringconstK:
             //printf ("enter here string const "); 
             printf ("%s", e->val.stringconstE);
             break;
        case intconstK:
             //printf (" enter here int ");
             printf("%i",e->val.intconstE);
             break;
        case floatconstK:
             //printf ("enter here float ");
             printf ("%f", e->val.floatconstE);
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
        case unarymK:
             printf("(-");
             prettyEXP(e->val.generalE.expVal);
             printf(")");
             break;

        // simple statements
        case printstmtK:
             printf("print ");
             prettyEXP(e->val.generalE.expVal);
             printf(";\n");
             break;
        case readstmtK:
             printf("read ");
             printf("%s",e->val.idE);
             printf(";\n");
             break;
        case assignstmtK:
             printf("%s",e->val.assignE.left);
             printf(" = ");
             prettyEXP(e->val.assignE.right);
             printf(";\n");
             break;
        
        case makeSimplestmtK:
             if (e->val.simplestmtsE.left != NULL) {
                prettyEXP(e->val.simplestmtsE.left);   
             }

             if (e->val.simplestmtsE.right != NULL) {
                prettyEXP(e->val.simplestmtsE.right);     
             }
             break;

        //declarations
        case declareK:
             printf("var %s : %s;\n",e->val.declareE.left, e->val.declareE.right);
             break;

        case declarationsK:

             prettyEXP(e->val.declarationsE.left);
             prettyEXP(e->val.declarationsE.right);
             break;

        // input (combine)
        case combineK: 
            if (e->val.combineE.left != NULL) {
                prettyEXP(e->val.combineE.left);
            }

            if (e->val.combineE.right != NULL) {
                prettyEXP(e->val.combineE.right);
            }
            break;
      
        case ifstatementK:
            
            if (e->val.ifstatementE.previousstmts != NULL) {
                prettyEXP(e->val.ifstatementE.previousstmts);
            }
            printf ("if ");
            prettyEXP(e->val.ifstatementE.ifcondition);
            printf (" then\n");
            if (e->val.ifstatementE.ifbody != NULL) {
                prettyEXP(e->val.ifstatementE.ifbody);
            }

            if (e->val.ifstatementE.hasElse == 1) {
                printf ("else\n");
                if (e->val.ifstatementE.elsebody != NULL) {

                    prettyEXP(e->val.ifstatementE.elsebody);
                }
            }
            printf ("endif\n");
            break;

        case whilestmtK:

            if (e->val.whilestmtE.previousstmts != NULL) {
                prettyEXP(e->val.whilestmtE.previousstmts);
            }
            printf("while ");

            if (e->val.whilestmtE.whileCond != NULL) {
                prettyEXP(e->val.whilestmtE.whileCond);   
            }
            printf (" do\n");

            if (e->val.whilestmtE.whileBody != NULL) {
                prettyEXP(e->val.whilestmtE.whileBody);
            }
            printf("done\n");

            break;

        case emptyK:
            break;
  }
}
