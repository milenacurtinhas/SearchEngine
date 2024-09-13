#ifndef _GRAPH_TST_H_
#define _GRAPH_TST_H_

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "TST.h"

typedef struct graphNode graphTST;
struct graphNode {
    Value *inValues, *outValues;
    unsigned char c;
    int inQtt, outQtt;
    TST *l, *m, *r;
};

graphTST* create_node_graph();
graphTST* rec_insert_graph(graphTST* t, String* key, Value *valIN, Value *valOut, int d);
graphTST* TST_insert_graph(graphTST* t, String* key , Value *valIN, Value *valOut);
graphTST* rec_search_graph(graphTST* t, String* key, int d);
Value* TST_search_graph(graphTST* t, String* key);
void free_value_graph(Value *val);
void free_tst_graph(graphTST *t);

#endif