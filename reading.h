#ifndef READING_H_
#define READING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"

TST* create_stopwords_tst(FILE *file);
TST *create_twords_tst(FILE *file, TST *stopwordsTST, char *pagesStr);
TST * read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path);
TST *create_graph_tst(FILE *file);
Value *add_new_value(Value *head, char *word);

#endif