#ifndef READING_H_
#define READING_H_

#include "TST.h"
#include "graphTST.h"
#include <stdbool.h>

typedef struct {
    char *text;
    double rank;
} Result;

TST* create_stopwords_tst(FILE *file);
TST *create_twords_tst(FILE *file, TST *stopwordsTST, char *pagesStr);
TST * read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path);
graphTST* create_graph_tst(FILE *file, int *count);
Value *add_new_value(Value *head, char *word);
void read_searches(FILE *file, TST *stopwordsTST, TST *twordsTST, graphTST *graph, int it);
void search_words(char *line, TST *stopwordsTST, TST *twordsTST, graphTST *graph, int it);
void normalize_arrays(char **textsSearched, int *textsQtt, int wordsQtt, int arraySize, graphTST *graph, int it);
void exch(Result A, Result B);
int partition(Result *a, int lo, int hi);
void quick_sort(Result *a, int lo, int hi);
void print_result(Result *results, int size);

#endif