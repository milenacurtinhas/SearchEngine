#ifndef _GRAPH_TST_H_
#define _GRAPH_TST_H_

#include "TST.h"

typedef struct graphNode graphTST;
struct graphNode {
    Value *inValues, *outValues;
    unsigned char c;
    int inQtt, outQtt;
    graphTST *l, *m, *r;
    double *pr;
};

graphTST* create_node_graph();
graphTST* rec_insert_graph(graphTST* t, String* key, Value *valIN, Value *valOut, int d, int qtt);
graphTST* TST_insert_graph(graphTST* t, String* key , Value *valIN, Value *valOut, int qtt);
graphTST* rec_search_graph(graphTST* t, String key, int d);
graphTST* TST_search_graph(graphTST* t, String key);
void free_tst_graph(graphTST *t);
graphTST* collectWordsFirstIT(graphTST *node, char *buffer, int depth, int qtt);
graphTST* collectWords(graphTST *node,graphTST *root, char *buffer, int depth, int qtt, int *it);
void collectDifferences(graphTST *node, double *sum, int *it);
double prCalc(double prMinus, int outQtt, double sum, int n);
double prSum(graphTST *node, graphTST *root, int *it);
graphTST *pageRankCalc(graphTST* tst, int tstSize, int *it);
double errorAtt(int n, int *k, graphTST *tst);

#endif