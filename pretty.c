#include <stdio.h>
#include "pretty.h"
 
void printTabs(int times) {

    for (int i = 0; i< times; i++) {
        printf("\t");
    }
}

void prettyEXP(EXP *e, int indentLevel)
{ 
    switch (e->kind) {
        case idK:

             printf("%s",e->val.idE);
             break;
        case stringconstK:
             printf ("%s", e->val.stringconstE);
             break;
        case intconstK:
             printf("%i",e->val.intconstE);
             break;
        case floatconstK:
             printf ("%f", e->val.floatconstE);
             break;
        case plusK:
             printf("(");
             prettyEXP(e->val.plusE.left, 0);
             printf("+");
             prettyEXP(e->val.plusE.right, 0);
             printf(")");
             break;
        case minusK:
             printf("(");
             prettyEXP(e->val.minusE.left, 0);
             printf("-");
             prettyEXP(e->val.minusE.right, 0);
             printf(")");
             break;
        case timesK:
             printf("(");
             prettyEXP(e->val.timesE.left, 0);
             printf("*");
             prettyEXP(e->val.timesE.right, 0);
             printf(")");
             break;
        case divK:
             printf("(");
             prettyEXP(e->val.divE.left, 0);
             printf("/");
             prettyEXP(e->val.divE.right, 0);
             printf(")");
             break;
        case unarymK:
             printf("(-");
             prettyEXP(e->val.generalE.expVal, 0);
             printf(")");
             break;

        // simple statements
        case printstmtK:
             printTabs(indentLevel);
             printf("print ");
             prettyEXP(e->val.generalE.expVal, indentLevel);
             printf(";\n");
             break;
        case readstmtK:
             printTabs(indentLevel);
             printf("read ");
             printf("%s",e->val.idE);
             printf(";\n");
             break;
        case assignstmtK:
             printTabs(indentLevel);
             printf("%s",e->val.assignE.left);
             printf(" = ");
             prettyEXP(e->val.assignE.right, indentLevel);
             printf(";\n");
             break;
        
        case makeSimplestmtK:
             
             if (e->val.simplestmtsE.left != NULL) {
                prettyEXP(e->val.simplestmtsE.left, indentLevel);   
             }
             
             if (e->val.simplestmtsE.right != NULL) {
                prettyEXP(e->val.simplestmtsE.right, indentLevel);     
             }
             break;

        //declarations
        case declareK:
             printTabs(indentLevel);
             printf("var %s : %s;\n",e->val.declareE.left, e->val.declareE.right);
             break;

        case declarationsK:
             
             prettyEXP(e->val.declarationsE.left, indentLevel);
             
             prettyEXP(e->val.declarationsE.right, indentLevel);
             break;

        // input (combine)
        case combineK:
            
            if (e->val.combineE.left != NULL) {
                prettyEXP(e->val.combineE.left, indentLevel);
            }

            if (e->val.combineE.right != NULL) {
                prettyEXP(e->val.combineE.right, indentLevel);
            }
            break;
      
        case ifstatementK:

            if (e->val.ifstatementE.previousstmts != NULL) {
                
                prettyEXP(e->val.ifstatementE.previousstmts, indentLevel);
            }

            printTabs(indentLevel);

            printf ("if ");
            prettyEXP(e->val.ifstatementE.ifcondition, 0);
            printf (" then\n");
            if (e->val.ifstatementE.ifbody != NULL) {
                
                prettyEXP(e->val.ifstatementE.ifbody, indentLevel+1);
            }


            if (e->val.ifstatementE.hasElse == 1) {

                printTabs(indentLevel);
                printf ("else\n");
                if (e->val.ifstatementE.elsebody != NULL) {
            
                    prettyEXP(e->val.ifstatementE.elsebody, indentLevel+1);
                }
            }

            printTabs(indentLevel);
            printf ("endif\n");
            break;

        case whilestmtK:
            
            if (e->val.whilestmtE.previousstmts != NULL) {
                
                prettyEXP(e->val.whilestmtE.previousstmts, indentLevel);
            }

            printTabs(indentLevel);
            printf("while ");

            
            prettyEXP(e->val.whilestmtE.whileCond, 0);   
            
            printf (" do\n");

            if (e->val.whilestmtE.whileBody != NULL) {
                prettyEXP(e->val.whilestmtE.whileBody, indentLevel+1);
            }

            printTabs(indentLevel);
            printf("done\n");

            break;

        case emptyK:
            break;
  }
}


