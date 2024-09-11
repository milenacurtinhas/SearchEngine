#ifndef READING_H_
#define READING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tst.h"

TST* create_stopwords_tst(FILE *stopwords);
TST *create_twords_tst(char *pagesStr, FILE *index, TST *stopwordsTST);
TST * read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path);

#endif