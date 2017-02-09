
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
             
             break;
        case assignstmtK:
            
            // get the identifier type 

            // get the expression type
            expType = evaluateExpressType(symboleTable, e->val.assignE.right);
            
            printf("%d\n", expType == intK);
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

SymbolKind evaluateExpressType(SymbolTable *symbolTable, EXP *passE) {
    
    switch (passE->kind) {
        
        case idK:
            
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


            break;
        case minusK:
                
            break;
        case timesK:
                
            break;
        case divK:
                
            break;
        case unarymK:
            
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
