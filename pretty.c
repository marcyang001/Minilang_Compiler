#include <stdio.h>
#include "pretty.h"
 
void printTabs(FILE *file, int times) {

    for (int i = 0; i< times; i++) {
        fprintf(file, "\t");
        printf("\t");
    }
}

void prettyEXP(FILE *file, EXP *e, int indentLevel)
{ 
    switch (e->kind) {
        case idK:

             printf("%s",e->val.idE);
             fprintf(file, "%s",e->val.idE);
             break;
        case stringconstK:
             printf ("%s", e->val.stringconstE);
             fprintf(file, "%s", e->val.stringconstE);
             break;
        case intconstK:
             printf("%i",e->val.intconstE);
             fprintf(file, "%i",e->val.intconstE);
             break;
        case floatconstK:
             printf ("%f", e->val.floatconstE);
             fprintf(file, "%f", e->val.floatconstE);
             break;
        case plusK:
             printf("(");
             fprintf(file, "(");
             prettyEXP(file, e->val.plusE.left, 0);
             
             fprintf(file, "+");
             printf("+");
             prettyEXP(file, e->val.plusE.right, 0);
             
             fprintf(file, ")");
             printf(")");
             break;
        case minusK:
             printf("(");
             fprintf(file, "(");
             prettyEXP(file, e->val.minusE.left, 0);
             
             printf("-");
             fprintf(file, "-");

             prettyEXP(file, e->val.minusE.right, 0);
             
             printf(")");
             fprintf(file, ")");
             break;
        case timesK:

            printf("(");
            fprintf(file, "(");
            prettyEXP(file, e->val.timesE.left, 0);
            printf("*");
            fprintf(file, "*");
            prettyEXP(file, e->val.timesE.right, 0);
            printf(")");
            fprintf(file, ")");

            break;
        case divK:
            printf("(");
            fprintf(file, "(");
            prettyEXP(file, e->val.divE.left, 0);
            printf("/");
            fprintf(file, "/");
            prettyEXP(file, e->val.divE.right, 0);
            printf(")");
            fprintf(file, ")");
            break;
        case unarymK:
            printf("(-");
            fprintf(file, "(-");
            prettyEXP(file, e->val.generalE.expVal, 0);
            printf(")");
            fprintf(file, ")");
            break;

        // simple statements
        case printstmtK:
            printTabs(file, indentLevel);
            printf("print ");
            fprintf(file, "print ");
            prettyEXP(file, e->val.generalE.expVal, indentLevel);
            printf(";\n");
            fprintf(file, ";\n");
            break;
        case readstmtK:
            printTabs(file, indentLevel);
            printf("read ");
            fprintf(file, "read ");
            printf("%s",e->val.idE);
            fprintf(file, "%s",e->val.idE);
            printf(";\n");
            fprintf(file, ";\n");
            break;
        case assignstmtK:
            printTabs(file, indentLevel);
            printf("%s",e->val.assignE.left);
            fprintf(file, "%s",e->val.assignE.left);
            printf(" = ");
            fprintf(file, " = ");
            prettyEXP(file, e->val.assignE.right, indentLevel);
            printf(";\n");
            fprintf(file, ";\n");

            break;
        
        case makeSimplestmtK:
             
             if (e->val.simplestmtsE.left != NULL) {
                prettyEXP(file, e->val.simplestmtsE.left, indentLevel);   
             }
             
             if (e->val.simplestmtsE.right != NULL) {
                prettyEXP(file, e->val.simplestmtsE.right, indentLevel);     
             }
             break;

        //declarations
        case declareK:
             printTabs(file, indentLevel);
             char *idName = e->val.declareE.left;
             char *idType = e->val.declareE.right;
             printf("var %s : %s;\n",idName,idType);
             fprintf(file, "var %s : %s;\n",idName,idType);
             break;

        case declarationsK:
             
             prettyEXP(file, e->val.declarationsE.left, indentLevel);
             
             prettyEXP(file, e->val.declarationsE.right, indentLevel);
             break;

        // input (combine)
        case combineK:
            
            if (e->val.combineE.left != NULL) {
                prettyEXP(file, e->val.combineE.left, indentLevel);
            }

            if (e->val.combineE.right != NULL) {
                prettyEXP(file, e->val.combineE.right, indentLevel);
            }
            break;
      
        case ifstatementK:

            if (e->val.ifstatementE.previousstmts != NULL) {
                
                prettyEXP(file, e->val.ifstatementE.previousstmts, indentLevel);
            }

            printTabs(file, indentLevel);

            printf ("if ");
            fprintf (file, "if ");
            prettyEXP(file, e->val.ifstatementE.ifcondition, 0);
            printf (" then\n");
            fprintf (file, " then\n");
            if (e->val.ifstatementE.ifbody != NULL) {
                
                prettyEXP(file, e->val.ifstatementE.ifbody, indentLevel+1);
            }


            if (e->val.ifstatementE.hasElse == 1) {

                printTabs(file, indentLevel);
                printf ("else\n");
                fprintf (file, "else\n");
                if (e->val.ifstatementE.elsebody != NULL) {
            
                    prettyEXP(file, e->val.ifstatementE.elsebody, indentLevel+1);
                }
            }

            printTabs(file, indentLevel);
            printf ("endif\n");

            fprintf (file, "endif\n");

            break;

        case whilestmtK:
            
            if (e->val.whilestmtE.previousstmts != NULL) {
                
                prettyEXP(file, e->val.whilestmtE.previousstmts, indentLevel);
            }

            printTabs(file, indentLevel);

            fprintf (file, "while ");

            printf("while ");

            
            prettyEXP(file, e->val.whilestmtE.whileCond, 0);   
            
            printf (" do\n");

            fprintf (file, " do\n");
            
            if (e->val.whilestmtE.whileBody != NULL) {
                prettyEXP(file, e->val.whilestmtE.whileBody, indentLevel+1);
            }

            printTabs(file, indentLevel);
            printf("done\n");

            fprintf (file, "done\n");

            break;

        case emptyK:
            break;
  }
}


