
#include <stdio.h>
#include "symbol.h"
#include "typecheck.h"
#include "memory.h"
#include "tree.h"
#include <string.h>

// returns 1 if the program satisfied type check 
// zero if it does not
SymbolKind evaluateExpressType(SymbolTable *symbolTable, EXP *passE);
int checker(SymbolTable *symbolTable, EXP *e);

int typeCheck(EXP *e) {

    SymbolTable *symbolTable;
    symbolTable = initSymbolTable();

    return checker(symbolTable, e);
}


int checker(SymbolTable *symbolTable, EXP *e) {
	
    
    SymbolKind exp1Type;
    SymbolKind exp2Type;
    int exp1Valid;
    int exp2Valid;
    int isSymbolDefined;

	switch (e->kind) {
        
        // simple statements
        case printstmtK:
            exp1Type = evaluateExpressType(symbolTable, e->val.generalE.expVal);
            if (exp1Type == errorK) {
                return 0;
            }
            break;
        
        case readstmtK:
             // check if the identifer exists in the symbol table 
             // if not --> error 
             // if yes --> continue

            isSymbolDefined = defSymbol(symbolTable, e->val.declareE.left);
            if (isSymbolDefined == 0) {
                printf("the identifier %s is not defined -- line %d\n", e->val.declareE.left, e->lineno);
                return 0;
            }

            break;
        
        // assignment
        case assignstmtK:
            
            // get the identifier type 
            isSymbolDefined = defSymbol(symbolTable, e->val.declareE.left);
            if (isSymbolDefined == 1) {
                // get the identifier type
                SYMBOL *idType = getSymbol(symbolTable, e->val.idE);
                exp1Type = idType->kind;
                
                // get the expression type
                exp2Type = evaluateExpressType(symbolTable, e->val.assignE.right);
                
                // compare the identifer with the assigned expression
                if (exp1Type != exp2Type || exp1Type == errorK || exp2Type == errorK) {
                    printf("identifer %s is assigned to a bad type  ---line %d\n", e->val.assignE.left, e->lineno);
                    return 0;
                }
            }
            else {
                printf("identifer %s is not defined  ---line %d\n", e->val.assignE.left, e->lineno);
                return 0;
            }

            break;

        //declaration
        case declareK:

            // check if there exists the symbol name 
            isSymbolDefined = defSymbol(symbolTable, e->val.declareE.left);
            // if not put the symbol name into the symbol table 
            if (isSymbolDefined == 0) {
                
                SymbolKind skind;
                if (strcmp("string", e->val.declareE.right) == 0) {
                    skind = stringK;
                }
                else if (strcmp("int", e->val.declareE.right) == 0) {
                    skind = intK;
                }
                else {
                    skind = floatK;
                }

                putSymbol(symbolTable, e->val.declareE.left, skind);
                
            }
            else {
                printf("identifer %s is already declared  ---line %d\n", e->val.idE, e->lineno);
                return 0;
            }

            break;
        
        // multiple simple statements
        case makeSimplestmtK:
            
            if (e->val.simplestmtsE.left != NULL) {
                exp1Valid = checker(symbolTable, e->val.simplestmtsE.left);   
                if (exp1Valid == 0) {
                    return 0;
                }
            }
            
            if (e->val.simplestmtsE.right != NULL) {
                exp2Valid = checker(symbolTable, e->val.simplestmtsE.right);     
                if (exp2Valid == 0) {
                    return 0;
                }
            }

            break;

        // multiple declarations
        case declarationsK:
             
            exp1Valid = checker(symbolTable, e->val.declarationsE.left);
            if (exp1Valid == 0) {
                return 0;
            }
            exp2Valid = checker(symbolTable, e->val.declarationsE.right);
            if (exp2Valid == 0) {
                return 0;
            }
            break;
      
        case ifstatementK:

            
            // check the validity of the statements before ifstatements
            if (e->val.ifstatementE.previousstmts != NULL) {
                
                exp1Valid = checker(symbolTable, e->val.ifstatementE.previousstmts);
                if (exp1Valid == 0) {
                    return 0;
                }
            }

            // The condition <expression> must be an integer
            exp1Type = evaluateExpressType(symbolTable, e->val.ifstatementE.ifcondition);
            if (exp1Type != intK) {
                return 0;
            }
            //check the if statement body
            if (e->val.ifstatementE.ifbody != NULL) {
                
                exp2Valid = checker(symbolTable, e->val.ifstatementE.ifbody);
                if (exp2Valid == 0) {
                    return 0;
                }
            }

            //check the else statement body 
            if (e->val.ifstatementE.hasElse == 1) {

                if (e->val.ifstatementE.elsebody != NULL) {
            
                    exp2Valid = checker(symbolTable, e->val.ifstatementE.elsebody);
                    if (exp2Valid == 0) {
                        return 0;
                    }
                }
            }

            break;

        case whilestmtK:
            
            // check the validity of the statements before while statement
            if (e->val.whilestmtE.previousstmts != NULL) {
                
                exp1Valid = checker(symbolTable, e->val.whilestmtE.previousstmts);
                if (exp1Valid == 0) {
                    return 0;
                }
            }
            
            // The condition <expression> must be an integer
            
            exp1Type = evaluateExpressType(symbolTable, e->val.whilestmtE.whileCond);
            if (exp1Type != intK) {
                return 0;
            }  
            
            // check the while statement body
            if (e->val.whilestmtE.whileBody != NULL) {
                exp2Valid = checker(symbolTable, e->val.whilestmtE.whileBody);
                if (exp2Valid == 0) {
                    return 0;
                }
            }

            break;
        
        // combine declarations and statements
        case combineK:
            
            
            exp1Valid = checker(symbolTable, e->val.combineE.left);
            
            exp2Valid = checker(symbolTable, e->val.combineE.right);
            
            if (exp1Valid == 0 || exp2Valid == 0) {
                return 0;
            }
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
                printf("identifer %s is undefined ---line %d\n", e->val.idE, e->lineno);
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
            else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
                return floatK;
            }
            else {
                printf("type error in addition ---line  %d\n", e->val.plusE.left->lineno);
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
            else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
                return floatK;
            }
            else {
                printf("type error in substraction  ---line %d\n", e->val.minusE.left->lineno);
            }

            break;
        case timesK:
            // int <op> int
            // float <op> float
            // int <op> float
            // string * int 
            leftExpType = evaluateExpressType(symbolTable, e->val.timesE.left);
            
            rightExpType = evaluateExpressType(symbolTable, e->val.timesE.right);
            
            if (leftExpType == intK && rightExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                return floatK;
            }
            else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
                return floatK;
            }
            else if ((leftExpType == stringK && rightExpType == intK) || (leftExpType == intK && rightExpType == stringK)) {
                return stringK;
            }
            else {
                printf("type error in multiplication ---line %d\n", e->val.timesE.left->lineno);
            }

            break;
        case divK:
            // int <op> int
            // float <op> float
            // int <op> float            

            leftExpType = evaluateExpressType(symbolTable, e->val.divE.left);
            
            rightExpType = evaluateExpressType(symbolTable, e->val.divE.right);
            
            if (leftExpType == intK && rightExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK && rightExpType == floatK) {
                return floatK;
            }
            else if ((leftExpType == intK && rightExpType == floatK) || (leftExpType == floatK && rightExpType == intK)) {
                return floatK;
            }
            else {
                printf("type error in division  ---line %d\n", e->val.divE.left->lineno);
            }

            break;
        case unarymK:

            // <expression> must be either of type int or of type float
            leftExpType = evaluateExpressType(symbolTable, e->val.generalE.expVal);
            if (leftExpType == intK) {
                return intK;
            }
            else if (leftExpType == floatK) {
                return floatK;
            }
            else {
                printf("type error in unary operator ---line %d\n", e->lineno);
            }            
            break;
        default:
            break;
    }


    return errorK;

}
