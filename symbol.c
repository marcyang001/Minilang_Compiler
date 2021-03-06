/*
 * JOOS is Copyright (C) 1997 Laurie Hendren & Michael I. Schwartzbach
 *
 * Reproduction of all or part of this software is permitted for
 * educational or research use on condition that this copyright notice is
 * included in any copy. This software comes with no warranty of any
 * kind. In no event will the authors be liable for any damages resulting from
 * use of this software.
 *
 * email: hendren@cs.mcgill.ca, mis@brics.dk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "symbol.h"

extern char *currentfile;

void outputSymbolTable(FILE *fs, char *varname, SymbolKind kind);

int Hash(char *str)
{ unsigned int hash = 0;
  while (*str) hash = (hash << 1) + *str++; 
  return hash % HashSize;
}

SymbolTable *initSymbolTable()
{ SymbolTable *t;
  int i;
  t = NEW(SymbolTable);
  for (i=0; i < HashSize; i++) t->table[i] = NULL;
  t->next = NULL;
  return t;
}

SymbolTable *scopeSymbolTable(SymbolTable *s)
{ SymbolTable *t;
  t = initSymbolTable();
  t->next = s;
  return t;
}

SYMBOL *putSymbol(SymbolTable *t, char *name, SymbolKind kind, FILE *filename)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  s = NEW(SYMBOL);
  s->name = name;
  s->kind = kind;
  if (kind == intK) {
    s->val.intVal = 0;
  }
  else if (kind == floatK) {
    s->val.floatVal = 0.0;
  }
  else {
    s->val.stringVal = "";
  }
  outputSymbolTable(filename, name, kind);
  s->next = t->table[i];
  t->table[i] = s;
  return s;
}

SYMBOL *updateSymbolValue(SymbolTable *t, char *name, RESULTEXP *e) {
    int i = Hash(name);
    SYMBOL *s;

    for (s = t->table[i]; s; s = s->next) {
        if (strcmp(s->name, name)==0) {

            if (e->kind == intK) {
              s->val.intVal = atoi(e->val.expVal);
            }
            else if (e->kind == floatK) {
              s->val.floatVal = atof(e->val.expVal);
            }
            else {
              s->val.stringVal = e->val.expVal;
            }
            return s;
        }
    }
    
    if (t->next==NULL) return NULL;
    return getSymbol(t->next,name);
}


SYMBOL *getSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return s;
  }
  if (t->next==NULL) return NULL;
  return getSymbol(t->next,name);
}
 
int defSymbol(SymbolTable *t, char *name)
{ int i = Hash(name);
  SYMBOL *s;
  for (s = t->table[i]; s; s = s->next) {
      if (strcmp(s->name,name)==0) return 1;
  }
  return 0;
}

void outputSymbolTable(FILE *fs, char *varname, SymbolKind kind) {
    
    char *varType; 

    if (kind == errorK) {
      return;
    }
    else if (kind == intK) {
      varType = "int";
    }
    else if (kind == stringK) {
      varType = "string";
    }
    else {
      varType = "float";
    }
    
    fprintf(fs, "%s : %s\n", varname, varType);
    
    

}


