
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pretty.h"
#include "symbol.h"
#include "string.h"

void generateCode(FILE *file, EXP *e, int indentLevel, SymbolTable *symbolTable) {
    
    switch (e->kind) {
        case idK:

            fprintf(file, "%s",e->val.idE);
            break;
        case stringconstK:
             
            fprintf(file, "%s", e->val.stringconstE);
            break;
        case intconstK:

            fprintf(file, "%i",e->val.intconstE);
            break;
        case floatconstK:
             
            fprintf(file, "%f", e->val.floatconstE);
            break;
        case plusK:
             
            fprintf(file, "(");
            generateCode(file, e->val.plusE.left, 0, symbolTable);
             
            fprintf(file, "+");
             
            generateCode(file, e->val.plusE.right, 0, symbolTable);
             
            fprintf(file, ")");
             
            break;
        case minusK:
             
            fprintf(file, "(");
            generateCode(file, e->val.minusE.left, 0, symbolTable);
             
            fprintf(file, "-");

            generateCode(file, e->val.minusE.right, 0, symbolTable);
            
            fprintf(file, ")");
            break;
        case timesK:

            
            fprintf(file, "(");
            generateCode(file, e->val.timesE.left, 0, symbolTable);
            
            fprintf(file, "*");
            generateCode(file, e->val.timesE.right, 0, symbolTable);
            
            fprintf(file, ")");

            break;
        case divK:
            
            fprintf(file, "(");
            generateCode(file, e->val.divE.left, 0, symbolTable);
            
            fprintf(file, "/");
            generateCode(file, e->val.divE.right, 0, symbolTable);
            
            fprintf(file, ")");
            break;
        case unarymK:
            
            fprintf(file, "(-");
            generateCode(file, e->val.generalE.expVal, 0, symbolTable);
            
            fprintf(file, ")");
            break;

        // simple statements
        case printstmtK:
            printTabs(file, indentLevel);
            
            fprintf(file, "printf");
            RESULTEXP *s = evaluateExpression(symbolTable, e->val.generalE.expVal);
            if (s->kind == stringK) {
                //fprintf(file, "(\"\%%s\", ");
            }
            generateCode(file, e->val.generalE.expVal, 0, symbolTable);
            
            fprintf(file, ");\n");
            break;
        case readstmtK:
            printTabs(file, indentLevel);
            
            fprintf(file, "read ");
            
            fprintf(file, "%s",e->val.idE);
            
            fprintf(file, ";\n");
            break;
        case assignstmtK:
            printTabs(file, indentLevel);
            
            fprintf(file, "%s",e->val.assignE.left);
            
            fprintf(file, " = ");
            generateCode(file, e->val.assignE.right, indentLevel, symbolTable);
            
            fprintf(file, ";\n");

            break;
        
        case makeSimplestmtK:
             
             if (e->val.simplestmtsE.left != NULL) {
                generateCode(file, e->val.simplestmtsE.left, indentLevel, symbolTable);   
             }
             
             if (e->val.simplestmtsE.right != NULL) {
                generateCode(file, e->val.simplestmtsE.right, indentLevel, symbolTable);     
             }
             break;

        //declarations
        case declareK:
             printTabs(file, indentLevel);
             char *idName = e->val.declareE.left;
             char *idType = e->val.declareE.right;
             
             fprintf(file, "var %s : %s;\n",idName,idType);
             break;

        case declarationsK:
             
             generateCode(file, e->val.declarationsE.left, indentLevel, symbolTable);
             
             generateCode(file, e->val.declarationsE.right, indentLevel, symbolTable);
             break;

        // input (combine)
        case combineK:
            
            if (e->val.combineE.left != NULL) {
                generateCode(file, e->val.combineE.left, indentLevel, symbolTable);
            }

            if (e->val.combineE.right != NULL) {
                generateCode(file, e->val.combineE.right, indentLevel, symbolTable);
            }
            break;
      
        case ifstatementK:

            if (e->val.ifstatementE.previousstmts != NULL) {
                
                generateCode(file, e->val.ifstatementE.previousstmts, indentLevel, symbolTable);
            }

            printTabs(file, indentLevel);

            
            fprintf (file, "if ");
            generateCode(file, e->val.ifstatementE.ifcondition, 0, symbolTable);
            
            fprintf (file, " then\n");
            if (e->val.ifstatementE.ifbody != NULL) {
                
                generateCode(file, e->val.ifstatementE.ifbody, indentLevel+1, symbolTable);
            }


            if (e->val.ifstatementE.hasElse == 1) {

                printTabs(file, indentLevel);
             
                fprintf (file, "else\n");
                if (e->val.ifstatementE.elsebody != NULL) {
            
                    generateCode(file, e->val.ifstatementE.elsebody, indentLevel+1, symbolTable);
                }
            }

            printTabs(file, indentLevel);
            
            fprintf (file, "endif\n");

            break;

        case whilestmtK:
            
            if (e->val.whilestmtE.previousstmts != NULL) {
                
                generateCode(file, e->val.whilestmtE.previousstmts, indentLevel, symbolTable);
            }

            printTabs(file, indentLevel);

            fprintf (file, "while ");
            
            generateCode(file, e->val.whilestmtE.whileCond, 0, symbolTable);   
            
            fprintf (file, " do\n");
            
            if (e->val.whilestmtE.whileBody != NULL) {
                generateCode(file, e->val.whilestmtE.whileBody, indentLevel+1, symbolTable);
            }

            printTabs(file, indentLevel);
        
            fprintf (file, "done\n");

            break;

        case emptyK:
            break;
    }    

}

RESULTEXP *evaluateExpression(SymbolTable *symbolTable, EXP *e) {
    RESULTEXP* r = NULL;
    int isSymbolDefined;
    RESULTEXP *leftExpType;
    RESULTEXP *rightExpType;

    switch (e->kind) {
        case idK:
            isSymbolDefined = defSymbol(symbolTable, e->val.idE);

            if (isSymbolDefined == 1) {
                SYMBOL *idType = getSymbol(symbolTable, e->val.idE);
                r->kind = idType->kind;

                if (idType->kind == stringK) {
                    r->val.stringVal = idType->val.stringVal;
                }
                else if (idType->kind == intK) {
                    r->val.intVal = idType->val.intVal;
                }
                else if (idType->kind == floatK) {
                    r->val.floatVal = idType->val.floatVal;
                }
                else {
                    printf("error type for identifier \"%s\"---line %d\n", e->val.idE, e->lineno);
                }
            }
            else {
                printf("identifier \"%s\" is undefined ---line %d\n", e->val.idE, e->lineno);
            }

            return r;
            break;
        case stringconstK:
            r->kind = e->kind;
            r->val.stringVal = e->val.stringVal;

            return r;
            break;
        case intconstK:
            r->kind = e->kind;
            r->val.intVal = e->val.intVal;

            return r;
            break;
        case floatconstK:
            r->kind = e->kind;
            r->val.floatVal = e->val.floatVal;

            return r;
            break;
        case plusK:
            // string + string = string 
            // int <op> int
            // float <op> float
            // int <op> float

            leftExpType = evaluateExpression(symbolTable, e->val.plusE.left);
            rightExpType = evaluateExpression(symbolTable, e->val.plusE.right);
            
            if (leftExpType->kind == stringK && rightExpType->kind == stringK) {
                r->kind = stringK;
                char result[strlen(leftExpType->val.stringVal)+strlen(rightExpType->val.stringVal)];
                strcpy(result, leftExpType->val.stringVal);
                strcpy(result, rightExpType->val.stringVal);
                
                r->val.stringVal = result;
                
            }
            else if (leftExpType == intK && rightExpType == intK) {
                

            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                

            }
            else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
                

            }
            else {
                printf("type error in addition ---line  %d\n", e->val.plusE.left->lineno);
            }
            
            return r;
            break;
        // case minusK:
        //     // int <op> int
        //     // float <op> float
        //     // int <op> float

        //     leftExpType =  evaluateExpressType(symbolTable, e->val.minusE.left);

        //     rightExpType = evaluateExpressType(symbolTable, e->val.minusE.right);
        //     if (leftExpType == intK && rightExpType == intK) {
        //         return intK;
        //     }
        //     else if (leftExpType == floatK && rightExpType == floatK) {
        //         return floatK;
        //     }
        //     else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
        //         return floatK;
        //     }
        //     else {
        //         printf("type error in substraction  ---line %d\n", e->val.minusE.left->lineno);
        //     }

        //     break;
        // case timesK:
        //     // int <op> int
        //     // float <op> float
        //     // int <op> float
        //     // string * int 
        //     leftExpType = evaluateExpressType(symbolTable, e->val.timesE.left);
            
        //     rightExpType = evaluateExpressType(symbolTable, e->val.timesE.right);
            
        //     if (leftExpType == intK && rightExpType == intK) {
        //         return intK;
        //     }
        //     else if (leftExpType == floatK && rightExpType == floatK) {
        //         return floatK;
        //     }
        //     else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
        //         return floatK;
        //     }
        //     else if ((leftExpType == stringK && rightExpType == intK) || (leftExpType == intK && rightExpType == stringK)) {
        //         return stringK;
        //     }
        //     else {
        //         printf("type error in multiplication ---line %d\n", e->val.timesE.left->lineno);
        //     }

        //     break;
        // case divK:
        //     // int <op> int
        //     // float <op> float
        //     // int <op> float            

        //     leftExpType = evaluateExpressType(symbolTable, e->val.divE.left);
            
        //     rightExpType = evaluateExpressType(symbolTable, e->val.divE.right);
            
        //     if (leftExpType == intK && rightExpType == intK) {
        //         return intK;
        //     }
        //     else if (leftExpType == floatK && rightExpType == floatK) {
        //         return floatK;
        //     }
        //     else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
        //         return floatK;
        //     }
        //     else {
        //         printf("type error in division  ---line %d\n", e->val.divE.left->lineno);
        //     }

        //     break;
        // case unarymK:

        //     // <expression> must be either of type int or of type float
        //     leftExpType = evaluateExpressType(symbolTable, e->val.generalE.expVal);
        //     if (leftExpType == intK) {
        //         return intK;
        //     }
        //     else if (leftExpType == floatK) {
        //         return floatK;
        //     }
        //     else {
        //         printf("type error in unary operator ---line %d\n", e->lineno);
        //     }            
        //     break;
        default:
            break;
    }

    return r;
    

}


void codegenerator(EXP *e, char *originalFileName, SymbolTable *symbolTable) {

    char cfilename[strlen(originalFileName)+2];
    strcpy(cfilename, originalFileName);
    strcat(cfilename, ".c");
    FILE *cfile = fopen(cfilename, "w");

    fprintf(cfile, "#include <stdio.h>\n\n");
    fprintf(cfile, "int main(int argc, char **argv) {\n\n");
    
    generateCode(cfile, e, 1, symbolTable);


    fprintf(cfile, "return 0;\n\n}\n");

    fclose(cfile);

}
