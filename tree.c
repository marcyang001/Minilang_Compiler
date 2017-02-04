#include "memory.h"
#include "tree.h"
 
extern int line_num;

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

// EXP *makeEXPdiv(EXP *left, EXP *right)
// { EXP *e;
//   e = NEW(EXP);
//   e->lineno = line_num;
//   e->kind = divK;
//   e->val.divE.left = left;
//   e->val.divE.right = right;
//   return e; 
// }

// EXP *makeEXPplus(EXP *left, EXP *right)
// { EXP *e;
//   e = NEW(EXP);
//   e->lineno = line_num;
//   e->kind = plusK;
//   e->val.plusE.left = left;
//   e->val.plusE.right = right;
//   return e;
// }

// EXP *makeEXPminus(EXP *left, EXP *right)
// { EXP *e;
//   e = NEW(EXP);
//   e->lineno = line_num;
//   e->kind = minusK;
//   e->val.minusE.left = left;
//   e->val.minusE.right = right;
//   return e;
// }
