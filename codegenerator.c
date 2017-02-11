
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "pretty.h"
#include "symbol.h"
#include "string.h"
#include "memory.h"

void generateCode(FILE *file, EXP *e, int indentLevel, SymbolTable *symbolTable) {
    
    RESULTEXP *s;
    EXP* temp;
    switch (e->kind) {

        // simple statements
        case printstmtK:
            printTabs(file, indentLevel);

            fprintf(file, "printf");
            s = evaluateExpression(symbolTable, e->val.generalE.expVal);
            printf("done evaluating expression\n");
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
            temp = NEW(EXP);
            temp->kind = idK;
            temp->val.idE = e->val.idE;
            
            s = evaluateExpression(symbolTable, temp);
            

            if (s->kind == stringK) {

                fprintf(file, "scanf(\"%%s\", %s);\n", e->val.idE);
            }
            else if (s->kind == intK) {
                
                fprintf(file, "scanf(\"%%d\", &%s);\n", e->val.idE);
            }
            else if (s->kind == floatK) {
                fprintf(file, "scanf(\"%%f\", &%s);\n", e->val.idE);
            }
            else {
                printf("error in generating  in scanf statement\n");
            }

            break;
        case assignstmtK:
            printTabs(file, indentLevel);

            s = evaluateExpression(symbolTable, e->val.assignE.right);
            
            if (s->kind == intK || s->kind == floatK) {
                fprintf(file, "%s = ",e->val.assignE.left);
                if (s->kind == intK) {
                    fprintf(file, "%d;\n", s->val.intVal); 
                }
                else {
                    fprintf(file, "%f;\n", s->val.floatVal);
                }
            }
            else if (s->kind == stringK) {
                fprintf(file, "strcpy(%s, %s);\n",e->val.assignE.left, s->val.stringVal);
            }
            else {
                printf("error in generating assign statement\n");
            }

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
            
            // if (e->val.ifstatementE.previousstmts != NULL) {
                
            //     generateCode(file, e->val.ifstatementE.previousstmts, indentLevel);
            // }

            // printTabs(file, indentLevel);

            
            // fprintf (file, "if ");
            // prettyEXP(file, e->val.ifstatementE.ifcondition, 0);
            
            // fprintf (file, " then\n");
            // if (e->val.ifstatementE.ifbody != NULL) {
                
            //     prettyEXP(file, e->val.ifstatementE.ifbody, indentLevel+1);
            // }


            // if (e->val.ifstatementE.hasElse == 1) {

            //     printTabs(file, indentLevel);
             
            //     fprintf (file, "else\n");
            //     if (e->val.ifstatementE.elsebody != NULL) {
            
            //         prettyEXP(file, e->val.ifstatementE.elsebody, indentLevel+1);
            //     }
            // }

            // printTabs(file, indentLevel);
            
            // fprintf (file, "endif\n");
            break;

        case whilestmtK:
            printf("ente here8\n");
            break;

        case emptyK:
            break;

        default:
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
                    printf("this is  a string type\n");
                    r->val.stringVal = idType->val.stringVal;
                }
                else if (idType->kind == intK) {
                    printf("this is an int type\n");
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
            
            r->kind = stringK;
            r->val.stringVal = e->val.stringconstE;

            return r;
            break;
        case intconstK:
            r->kind = intK;
            r->val.intVal = e->val.intconstE;

            return r;
            break;
        case floatconstK:
            r->kind = floatK;
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
                
                r->kind = floatK;
                if(leftExpType->kind == intK && rightExpType->kind == floatK) {
                    r->val.floatVal = leftExpType->val.intVal + rightExpType->val.floatVal;
                }
                else {
                    r->val.floatVal = leftExpType->val.floatVal + rightExpType->val.intVal;
                }
              

            }
            else {
                printf("code generation error in addition ---line  %d\n", e->val.plusE.left->lineno);
            }
            
            return r;
            break;
        case minusK:
            // int <op> int
            // float <op> float
            // int <op> float

            leftExpType =  evaluateExpression(symbolTable, e->val.minusE.left);
            rightExpType = evaluateExpression(symbolTable, e->val.minusE.right);
            
           
            if (leftExpType->kind == intK && rightExpType->kind == intK) {
                r->kind = intK;
                r->val.intVal = leftExpType->val.intVal - rightExpType->val.intVal;

            }
            else if (leftExpType->kind == floatK && rightExpType->kind == floatK) {
                r->kind = floatK;
                r->val.floatVal = leftExpType->val.floatVal - rightExpType->val.floatVal;

            }
            else if ((leftExpType->kind == intK && rightExpType->kind == floatK) || (leftExpType->kind == floatK && rightExpType->kind == intK)) {
                
                r->kind = floatK;
                if(leftExpType->kind == intK && rightExpType->kind == floatK) {
                    r->val.floatVal = leftExpType->val.intVal - rightExpType->val.floatVal;
                }
                else {
                    r->val.floatVal = leftExpType->val.floatVal - rightExpType->val.intVal;
                }

            }
            else {
                printf("code generation error in subtraction ---line  %d\n", e->val.plusE.left->lineno);
            }

            break;
        case timesK:
            // int <op> int
            // float <op> float
            // int <op> float
            // string * int 

            leftExpType = evaluateExpression(symbolTable, e->val.timesE.left);
            
            rightExpType = evaluateExpression(symbolTable, e->val.timesE.right);
            

            if (leftExpType->kind == intK && rightExpType->kind == intK) {
                r->kind = intK;
                r->val.intVal = leftExpType->val.intVal * rightExpType->val.intVal;
            }
            else if (leftExpType->kind == floatK && rightExpType->kind == floatK) {
                r->kind = floatK;
                r->val.intVal = leftExpType->val.floatVal * rightExpType->val.floatVal;
            }
            else if ((leftExpType->kind == intK && rightExpType->kind == floatK) || (leftExpType->kind == floatK && rightExpType->kind == intK)) {
                r->kind = floatK;
                
                if(leftExpType->kind == intK && rightExpType->kind == floatK) {
                    r->val.floatVal = leftExpType->val.intVal * rightExpType->val.floatVal;
                }
                else {
                    r->val.floatVal = leftExpType->val.floatVal * rightExpType->val.intVal;
                }

            }
            else if ((leftExpType->kind == stringK && rightExpType->kind == intK) || (leftExpType->kind == intK && rightExpType->kind == stringK)) {
                
                char *resultString;
                char *pattern; 
                int times; 
                int i;

                r->kind = stringK;

                if(leftExpType->kind == stringK && rightExpType->kind == intK) {

                    pattern = leftExpType->val.stringVal;
                    times = rightExpType->val.intVal;
                }
                else {
                    pattern = rightExpType->val.stringVal;
                    times = leftExpType->val.intVal;
                }

                if (times > 0) {
                    resultString = (char *) malloc(sizeof(char) * (((strlen(pattern)) * times) + 2));
                    char temp[strlen(pattern)];
                    
                    strncpy(temp, &pattern[1], strlen(pattern)-2);
                    temp[strlen(pattern)-2] = '\0';

                    resultString[0] = '"';
                    printf("pattern is %s\n", temp);
                    for (i = 0; i < (times); i++) {
                        strcat(resultString, temp);
                    }
                    resultString[strlen(resultString)-1] = '"';
                }
                else {
                    resultString = "\"\"";
                }

                r->val.stringVal = resultString;

            }
            else {
                printf("code generation error in multiplication ---line %d\n", e->val.timesE.left->lineno);
            }

            break;
        case divK:
            // int <op> int
            // float <op> float
            // int <op> float            

            leftExpType = evaluateExpression(symbolTable, e->val.divE.left);
            
            rightExpType = evaluateExpression(symbolTable, e->val.divE.right);
            
            if (leftExpType->kind == intK && rightExpType->kind == intK) {
                r->kind = intK;

                r->val.intVal = leftExpType->val.intVal / rightExpType->val.intVal;

            }
            else if (leftExpType->kind == floatK && rightExpType->kind == floatK) {
                r->kind = floatK;

                r->val.floatVal = leftExpType->val.floatVal / rightExpType->val.floatVal;
            }
            else if ((leftExpType->kind == intK && rightExpType->kind == floatK) || (leftExpType->kind == floatK && rightExpType->kind == intK)) {
                r->kind = floatK;

                if(leftExpType->kind == intK && rightExpType->kind == floatK) {
                    r->val.floatVal = leftExpType->val.intVal / rightExpType->val.floatVal;
                }
                else {
                    r->val.floatVal = leftExpType->val.floatVal / rightExpType->val.intVal;
                }
            }
            else {
                printf("code generation error in division  ---line %d\n", e->val.divE.left->lineno);
            }

            break;
        case unarymK:

            // <expression> must be either of type int or of type float
            leftExpType = evaluateExpression(symbolTable, e->val.generalE.expVal);
            if (leftExpType->kind == intK) {
                r->kind = intK;
                r->val.intVal = -leftExpType->val.intVal;
            }
            else if (leftExpType->kind == floatK) {
                r->kind = floatK;
                r->val.floatVal = -leftExpType->val.floatVal;

            }
            else {
                printf("code generation error in unary operator ---line %d\n", e->lineno);
            }            
            break;
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
    
    fprintf(cfile, "#include <stdio.h>\n");
    fprintf(cfile, "#include <stdlib.h>\n");
    fprintf(cfile, "#include <string.h>\n");
    fprintf(cfile, "\n\n\n");
    fprintf(cfile, "int main(int argc, char **argv) {\n\n");
    
    generateCode(cfile, e, 1, symbolTable);


    fprintf(cfile, "\n\n\treturn 0;\n\n}\n");

    fclose(cfile);

}
