#ifndef TREE_H
#define TREE_H
 

typedef struct EXP {
  int lineno;
  enum { idK,    // identifier
         intconstK, // int value
         floatconstK, // float value
         stringconstK, //string value 
         timesK, // *
         divK, // / 
         plusK, // + 
         minusK,  // - 
         unarymK,  // unary -
         printstmtK, // print statement  
         readstmtK, // read statement
         assignstmtK, // assign statement 
         makeSimplestmtK,  
         declareK,   // declarations
         declarationsK, // multiple declarations 
         combineK,
         ifstatementK,  // if statements 
         whilestmtK, // while statements
         emptyK  // empty statement

    } kind; 
  
  union {
    char* idE;
    int intconstE;
    float floatconstE;
    char* stringconstE;
    struct {struct EXP *left; struct EXP *right;} timesE;
    struct {struct EXP *left; struct EXP *right;} divE;
    struct {struct EXP *left; struct EXP *right;} plusE;
    struct {struct EXP *left; struct EXP *right;} minusE;
    struct {char* left; struct EXP *right; } assignE;
    struct {char* left; char* right; } declareE;
    struct {struct EXP *left; struct EXP *right;} declarationsE;
    struct {struct EXP *left; struct EXP *right;} simplestmtsE;
    struct {struct EXP *expVal; } generalE;
    struct {struct EXP *previousstmts; struct EXP *ifcondition; struct EXP *ifbody; struct EXP *elsebody; int hasElse;} ifstatementE;
    struct {struct EXP *previousstmts; struct EXP *whileCond; struct EXP *whileBody;} whilestmtE;
    struct {struct EXP *left; struct EXP *right;} combineE;
  } val;

} EXP;

typedef enum{stringK, intK, floatK, errorK} SymbolKind;

typedef struct SYMBOL {
    char *name;
    SymbolKind kind;
    union {
      char* stringVal;
      float floatVal;
      int   intVal;
    } val;
    struct SYMBOL *next;
} SYMBOL; 

typedef struct RESULTEXP {
  SymbolKind kind;
  union {
      char* stringVal;
      char* expVal;
  } val;
} RESULTEXP;


EXP *makeEXPid(char *id);

EXP *makeEXPintconst(int intconst);

EXP *makeEXPfloatconst(float floatconst);

EXP *makeEXPstringconst(char* stringconst);

EXP *makeEXPtimes(EXP *left, EXP *right);

EXP *makeEXPdiv(EXP *left, EXP *right);

EXP *makeEXPplus(EXP *left, EXP *right);

EXP *makeEXPminus(EXP *left, EXP *right);

EXP *makeEXPunarym(EXP *exval);

EXP *makePRINTStmt(EXP *exval);

EXP *makeREADStmt(char* exval);

EXP *makeASSIGNStmt(char* left, EXP *right);

EXP *makeDECL(char* left, char* right);

EXP *makeDECLS(EXP *left, EXP *right);

EXP *makeSimplestmts(EXP *left, EXP *right);

EXP *makeCombineE(EXP *left, EXP *right);

EXP *makeIFstmt(EXP *previousstmts, EXP *ifcondition, EXP *ifbody, EXP *elsebody, int hasElse);

EXP *makeWHILEstmt(EXP *previousstmts, EXP *whileExp, EXP *whileBody);

EXP *treatEmptystmt();

#endif /* !TREE_H */
