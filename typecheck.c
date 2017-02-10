
#include <stdio.h>
#include "symbol.h"
#include "typecheck.h"
#include "memory.h"
#include "tree.h"

// returns 1 if the program satisfied type check 
// zero if it does not
SymbolKind evaluateExpressType(SymbolTable *symbolTable, EXP *passE);

int typeCheck(EXP *e) {

	SymbolTable *symboleTable;
    symboleTable = initSymbolTable();
    SymbolKind expType;

	switch (e->kind) {
        
        // simple statements
        case printstmtK:
             
             break;
        case readstmtK:
             // check if the identifer exists in the symbol table 
             // if not --> error 
             // if yes --> correct
             break;
        case assignstmtK:
            
            // get the identifier type 

            // get the expression type
            expType = evaluateExpressType(symboleTable, e->val.assignE.right);
            
            printf("%d\n", expType == stringK);
            break;
        
        case makeSimplestmtK:
            
            if (e->val.simplestmtsE.left != NULL) {
               typeCheck(e->val.simplestmtsE.left);   
            }
            
            if (e->val.simplestmtsE.right != NULL) {
               typeCheck(e->val.simplestmtsE.right);     
            }
            break;

        //declarations
        case declareK:
             // check if there exists the symbol name 
             // if not put the symbol name into the symbol table 

             

            break;

        case declarationsK:
             

             break;

        case combineK:
            
            break;
      
        case ifstatementK:

            break;

        case whilestmtK:
            
            break;

        case emptyK:
            break;

        default:
            break;
	}
	return 1;
}

SymbolKind evaluateExpressType(SymbolTable *symbolTable, EXP *e) {
    int isSymbolDefined;
    SymbolKind leftExpType;
    SymbolKind rightExpType;
    switch (e->kind) {
        case idK:
            isSymbolDefined = defSymbol(symbolTable, e->val.idE);

            if (isSymbolDefined == 1) {
                SYMBOL *idType = getSymbol(symbolTable, e->val.idE);
                return idType->kind;
            }
            else {
                printf("error type in identifer %s\n", e->val.idE);
            }

            break;
        case stringconstK:
            
            return stringK;
            break;
        case intconstK:
            
            return intK;
            break;
        case floatconstK:
            
            return floatK;
            break;
        case plusK:
            // string + string = string 
            // int <op> int
            // float <op> float
            // int <op> float

            leftExpType = evaluateExpressType(symbolTable, e->val.plusE.left);
            rightExpType = evaluateExpressType(symbolTable, e->val.plusE.right);
            
            if (leftExpType == stringK && rightExpType == stringK) {
                return stringK;
            }
            else if (leftExpType == intK && rightExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                return floatK;
            }
            else if (leftExpType == intK && rightExpType == floatK){
                return floatK;
            }
            else {
                printf("type error in addition \n");
            }

            break;
        case minusK:
            // int <op> int
            // float <op> float
            // int <op> float

            leftExpType =  evaluateExpressType(symbolTable, e->val.minusE.left);

            rightExpType = evaluateExpressType(symbolTable, e->val.minusE.right);
            if (leftExpType == intK && rightExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                return floatK;
            }
            else if (leftExpType == intK && rightExpType == floatK) {
                return floatK;
            }
            else {
                printf("type error in substraction\n");
            }

            break;
        case timesK:
            // int <op> int
            // float <op> float
            // int <op> float
            
            leftExpType = evaluateExpressType(symbolTable, e->val.timesE.left);
            
            rightExpType = evaluateExpressType(symbolTable, e->val.timesE.right);
            
            if (leftExpType == intK && rightExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                return floatK;
            }
            else if (leftExpType == intK && rightExpType == floatK) {
                return floatK;
            }
            else {
                printf("type error in multiplication\n");
            }

            break;
        case divK:
            // int <op> int
            // float <op> float
            // int <op> float            

            leftExpType = evaluateExpressType(symbolTable, e->val.timesE.left);
            
            rightExpType = evaluateExpressType(symbolTable, e->val.timesE.right);
            
            if (leftExpType == intK && rightExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                return floatK;
            }
            else if (leftExpType == intK && rightExpType == floatK) {
                return floatK;
            }
            else {
                printf("type error in multiplication\n");
            }

            break;
        case unarymK:
        
            // <expression> must be either of type int or of type float
            return evaluateExpressType(symbolTable, e->val.generalE.expVal);
            break;
        default:
            break;
    }


    return errorK;

}


/*

 putSymbol(symboleTable, e->val.assignE.left, intK);
            
            //int exists = defSymbol(symboleTable, e->val.assignE.left);
            
        	SYMBOL *s = getSymbol(symboleTable, e->val.assignE.left);
            printf("%d\n", s->kind == intK);

            //printf("%d\n", exists);
        	printf("%s\n", s->name); 

*/
