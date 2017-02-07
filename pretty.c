#include <stdio.h>
#include "pretty.h"
 
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
             
             printf("print ");
             prettyEXP(e->val.generalE.expVal, 0);
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
             prettyEXP(e->val.assignE.right, 0);
             printf(";\n");
             break;
        
        case makeSimplestmtK:
             
             if (e->val.simplestmtsE.left != NULL) {
                prettyEXP(e->val.simplestmtsE.left, needIndent);   
             }
             
             if (e->val.simplestmtsE.right != NULL) {
                prettyEXP(e->val.simplestmtsE.right, needIndent);     
             }
             break;

        //declarations
        case declareK:
             
             printf("var %s : %s;\n",e->val.declareE.left, e->val.declareE.right);
             break;

        case declarationsK:
             
             prettyEXP(e->val.declarationsE.left, needIndent);
             
             prettyEXP(e->val.declarationsE.right, needIndent);
             break;

        // input (combine)
        case combineK:
            printf("enter the root!!\n");
            if (e->val.combineE.left != NULL) {
                prettyEXP(e->val.combineE.left, needIndent);
            }

            if (e->val.combineE.right != NULL) {
                prettyEXP(e->val.combineE.right, needIndent);
            }
            break;
      
        case ifstatementK:

            if (e->val.ifstatementE.previousstmts != NULL) {
                
                prettyEXP(e->val.ifstatementE.previousstmts, needIndent);
            }

            
            printf ("if ");
            prettyEXP(e->val.ifstatementE.ifcondition, 0);
            printf (" then\n");
            if (e->val.ifstatementE.ifbody != NULL) {
 
                prettyEXP(e->val.ifstatementE.ifbody, 1);
            }

            if (e->val.ifstatementE.hasElse == 1) {

                printf ("else\n");
                if (e->val.ifstatementE.elsebody != NULL) {
            
                    prettyEXP(e->val.ifstatementE.elsebody, 1);
                }
            }
            
            printf ("endif\n");
            break;

        case whilestmtK:
            printf("enter the while root!!\n");
            if (e->val.whilestmtE.previousstmts != NULL) {
                
                prettyEXP(e->val.whilestmtE.previousstmts, needIndent);
            }
            
            printf("while ");

            
            prettyEXP(e->val.whilestmtE.whileCond, 0);   
            
            printf (" do\n");

            if (e->val.whilestmtE.whileBody != NULL) {
                prettyEXP(e->val.whilestmtE.whileBody, 1);
            }
            
            printf("done\n");

            break;

        case emptyK:
            break;
  }
}
