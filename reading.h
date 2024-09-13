#ifndef READING_H_
#define READING_H_


#include "TST.h"
#include "graphTST.h"

TST* create_stopwords_tst(FILE *file);
TST *create_twords_tst(FILE *file, TST *stopwordsTST, char *pagesStr);
TST * read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path);
graphTST* create_graph_tst(FILE *file);
Value *add_new_value(Value *head, char *word);

#endif