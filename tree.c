#include "memory.h"
#include "tree.h"
 
extern int line_num;

// expressions

EXP *makeEXPid(char* id)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = idK;
  e->val.idE = id;
  return e;
}

EXP *makeEXPintconst(int intconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = intconstK;
  e->val.intconstE = intconst;
  return e;
}

EXP *makeEXPfloatconst(float floatconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = floatconstK;
  e->val.floatconstE = floatconst;
  return e;
}

EXP *makeEXPstringconst(char* stringconst)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = stringconstK;
  e->val.stringconstE = stringconst;
  return e;
}

EXP *makeEXPtimes(EXP* left, EXP* right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = timesK;
  e->val.timesE.left = left;
  e->val.timesE.right = right;
  return e;
}

EXP *makeEXPdiv(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = divK;
  e->val.divE.left = left;
  e->val.divE.right = right;
  return e; 
}

EXP *makeEXPplus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = plusK;
  e->val.plusE.left = left;
  e->val.plusE.right = right;
  return e;
}

EXP *makeEXPminus(EXP *left, EXP *right)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = minusK;
  e->val.minusE.left = left;
  e->val.minusE.right = right;
  return e;
}

EXP *makeEXPunarym(EXP *exval)
{ EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = unarymK;
  e->val.generalE.expVal = exval;
  return e;
}


//simple statements

EXP *makePRINTStmt(EXP *exval) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = printstmtK;
  e->val.generalE.expVal = exval;
  return e;
}

EXP *makeREADStmt(char* id) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = readstmtK;
  e->val.idE = id;
  return e;
}

EXP *makeASSIGNStmt(char* left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = assignstmtK;
  e->val.assignE.left = left;
  e->val.assignE.right = right;
  return e;
}

EXP *makeSimplestmts(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = makeSimplestmtK;
  e->val.simplestmtsE.left = left;
  e->val.simplestmtsE.right = right;
  return e;
}




// declarations

EXP *makeDECL(char* left, char* right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = declareK;
  e->val.declareE.left = left;
  e->val.declareE.right = right;
  return e;
}

EXP *makeDECLS(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = declarationsK;
  e->val.declarationsE.left = left;
  e->val.declarationsE.right = right;
  return e;  
}


EXP *makeCombineE(EXP *left, EXP *right) {
  EXP *e;
  e = NEW(EXP);
  e->lineno = line_num;
  e->kind = combineK;
  e->val.combineE.left = left;
  e->val.combineE.right = right;
  return e;  
}


