#ifndef TREE_H
#define TREE_H
 
typedef struct EXP {
  int lineno;
  enum { idK,
         intconstK,
         floatconstK,
         stringconstK,
         timesK,
         divK,
         plusK,
         minusK } kind;
  
  union {
    char* idE;
    int intconstE;
    float floatconstE;
    char* stringconstE;
    struct {struct EXP *left; struct EXP *right;} timesE;
    struct {struct EXP *left; struct EXP *right;} divE;
    struct {struct EXP *left; struct EXP *right;} plusE;
    struct {struct EXP *left; struct EXP *right;} minusE;
  } val;

} EXP;

EXP *makeEXPid(char *id);

EXP *makeEXPintconst(int intconst);

EXP *makeEXPfloatconst(float floatconst);

EXP *makeEXPstringconst(char* stringconst);

EXP *makeEXPtimes(EXP *left, EXP *right);

EXP *makeEXPdiv(EXP *left, EXP *right);

EXP *makeEXPplus(EXP *left, EXP *right);

EXP *makeEXPminus(EXP *left, EXP *right);

#endif /* !TREE_H */
