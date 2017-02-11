#ifndef PRETTY_H
#define PRETTY_H

#include "tree.h"

void prettyEXP(FILE *file, EXP *e, int indentLevel);

void printTabs(FILE *file, int times);

#endif /* !PRETTY_H */
