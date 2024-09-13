#ifndef _GRAPH_TST_H_
#define _GRAPH_TST_H_

#include "TST.h"

typedef struct graphNode graphTST;
struct graphNode {
    Value *inValues, *outValues;
    unsigned char c;
    int inQtt, outQtt;
    graphTST *l, *m, *r;
};

graphTST* create_node_graph();
graphTST* rec_insert_graph(graphTST* t, String* key, Value *valIN, Value *valOut, int d, int qtt);
graphTST* TST_insert_graph(graphTST* t, String* key , Value *valIN, Value *valOut, int qtt);
graphTST* rec_search_graph(graphTST* t, String* key, int d);
Value* TST_search_graph(graphTST* t, String* key);
void free_tst_graph(graphTST *t);

#endif