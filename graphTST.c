#include "graphTST.h"

graphTST* create_node_graph(){
    graphTST* node = calloc(1, sizeof(TST));
    
    return node;
}

graphTST* rec_insert_graph(graphTST* t, String* key, Value *valIN, Value *valOut, int d){
    unsigned char c = key->c[d];
    
    if (t == NULL){ 
        t = create_node_graph(); 
        t->c = c;
    }
    if (c < t->c){
        t->l = rec_insert_graph(t->l, key, valIN,valOut, d); 
    }
    else if (c > t->c) { 
        t->r = rec_insert_graph(t->r, key, valIN,valOut, d); 
    }
    else if (d < key->len - 1){
        t->m = rec_insert_graph(t->m, key, valIN,valOut, d+1);
    } 
    else{
        if(valIN){
            if(t->inValues == NULL){
                t->inValues = valIN;
            }
            else{
                Value* value = t->inValues;
                while(value->next != NULL){
                    value = value->next;
                }
                value->next = valIN;
            }
        }
        if(valOut){
            if(t->outValues == NULL){
                t->outValues = valOut;
            }
            else{
                Value* value = t->outValues;
                while(value->next != NULL){
                    value = value->next;
                }
                value->next = valOut;
            }
        }
    }
    
    return t;
}

graphTST* TST_insert_graph(graphTST* t, String* key , Value *valIN, Value *valOut){
    return rec_insert_graph(t, key, valIN,valOut, 0);
}

graphTST* rec_search_graph(graphTST* t, String* key, int d){

}

Value* TST_search_graph(graphTST* t, String* key);
void free_value_graph(Value *val);
void free_tst_graph(graphTST *t);