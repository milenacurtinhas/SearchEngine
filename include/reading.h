#ifndef READING_H_
#define READING_H_

#include "TST.h"
#include "graphTST.h"
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char *text;
    double rank;
} Result;

char *string_to_lower(char *str);
TST *create_stopwords_tst(FILE *file);
TST *create_twords_tst(FILE *file, TST *stopwordsTST, char *pagesStr);
TST *read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path);
graphTST *create_graph_tst(FILE *file, int *count);
void read_searches(TST *stopwordsTST, TST *twordsTST, graphTST *graph, int it);
void search_words(char *line, TST *stopwordsTST, TST *twordsTST, graphTST *graph, int it);
void normalize_arrays(char **textsSearched, int *textsQtt, int wordsQtt, int arraySize, graphTST *graph, int it);
Result *exch(Result* a, int i, int j);
int partition(Result *a, int lo, int hi);
Result *quick_sort(Result *a, int lo, int hi);
void print_result(Result *results, int size);

#endif