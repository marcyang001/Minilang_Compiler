
#include <stdio.h>
#include "symbol.h"
#include "typecheck.h"


int typeCheck(EXP *e) {

	switch (e->kind) {
        case idK:
        	 
             
             break;
        case stringconstK:
             
             break;
        case intconstK:
             
             break;
        case floatconstK:
             
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

        // simple statements
        case printstmtK:
             
             break;
        case readstmtK:
             
             break;
        case assignstmtK:
             
             break;
        
        case makeSimplestmtK:
             
             break;

        //declarations
        case declareK:
             
             break;

        case declarationsK:
             
             break;

        // input (combine)
        case combineK:
            
            break;
      
        case ifstatementK:

            break;

        case whilestmtK:
            
            
            break;

        case emptyK:
            break;

	return 0;
	}
}
