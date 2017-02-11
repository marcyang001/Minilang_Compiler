
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pretty.h"
#include "symbol.h"
#include "string.h"
#include "memory.h"

void generateCode(FILE *file, EXP *e, int indentLevel, SymbolTable *symbolTable) {
    printf("enter here in code generate\n");
    RESULTEXP *s;
    switch (e->kind) {

        // simple statements
        case printstmtK:
            printTabs(file, indentLevel);

            fprintf(file, "printf");
            s = evaluateExpression(symbolTable, e->val.generalE.expVal);
            printf("done evaluating expression");
            if (s->kind == stringK) {
                fprintf(file, "(\"%%s\", %s);\n", s->val.stringVal);
            }
            else if (s->kind == intK) {
                printf("enter here generating\n");
                fprintf(file, "(\"%%d\", %d);\n", s->val.intVal);
            }
            else if (s->kind == floatK) {
                fprintf(file, "(\"%%f\", %f);\n", s->val.floatVal);
            }
            else {
                printf("error in generating printf statement\n");
            }
            break;
        case readstmtK:
            printTabs(file, indentLevel);
            
            s = evaluateExpression(symbolTable, e->val.generalE.expVal);
            
            if (s->kind == stringK) {
                fprintf(file, "scanf(\"%%s\", %s)\n", e->val.idE);
            }
            else if (s->kind == intK) {
                fprintf(file, "scanf(\"%%d\", &%s)\n", e->val.idE);
            }
            else if (s->kind == floatK) {
                fprintf(file, "scanf(\"%%f\", &%s)\n", e->val.idE);
            }
            else {
                printf("error in generating scanf statement\n");
            }

            
            break;
        case assignstmtK:
            printf("ente here2\n");
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
            if (strcmp(idType, "string")== 0) {
                fprintf(file, "char %s[1024];\n", idName);
            }
            else if (strcmp(idType, "int")== 0) {
                fprintf(file, "int %s;\n", idName);
            }
            else if (strcmp(idType, "float")== 0) {
                fprintf(file, "float %s;\n", idName);
            }
            
            break;

        case declarationsK:
            
            printf("ente here5\n");
             break;

        // input (combine)
        case combineK:
            printf("ente here6\n");
            break;
      
        case ifstatementK:
            printf("ente here7\n");

            break;

        case whilestmtK:
            printf("ente here8\n");
            break;

        case emptyK:
            break;
        
        default:
            printf("ente here9\n");
            break;
    }    

}

RESULTEXP *evaluateExpression(SymbolTable *symbolTable, EXP *e) {
    RESULTEXP* r;
    r = NEW(RESULTEXP);
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
            r->val.stringVal = e->val.stringconstE;

            return r;
            break;
        case intconstK:
            r->kind = e->kind;
            r->val.intVal = e->val.intconstE;

            return r;
            break;
        case floatconstK:
            r->kind = e->kind;
            r->val.floatVal = e->val.floatconstE;

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
            else if (leftExpType->kind == intK && rightExpType->kind == intK) {
                r->kind = intK;
                r->val.intVal = leftExpType->val.intVal + rightExpType->val.intVal;

            }
            else if (leftExpType->kind == floatK && rightExpType->kind == floatK) {
                r->kind = floatK;
                r->val.floatVal = leftExpType->val.floatVal + rightExpType->val.floatVal;

            }
            else if ((leftExpType->kind == intK && rightExpType->kind == floatK) || (leftExpType->kind == floatK && rightExpType->kind == intK)) {
                
                if(leftExpType->kind == intK && rightExpType->kind == floatK) {
                    r->val.floatVal = leftExpType->val.intVal + rightExpType->val.floatVal;
                }
                else {
                    r->val.floatVal = leftExpType->val.floatVal + rightExpType->val.intVal;
                }

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
    printf("enter here in code generator\n");
    fprintf(cfile, "#include <stdio.h>\n\n");
    fprintf(cfile, "int main(int argc, char **argv) {\n\n");
    
    generateCode(cfile, e, 1, symbolTable);


    fprintf(cfile, "\treturn 0;\n\n}\n");

    fclose(cfile);

}
