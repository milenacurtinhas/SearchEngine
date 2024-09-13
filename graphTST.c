#include "graphTST.h"

graphTST* create_node_graph(){
    graphTST* node = calloc(1, sizeof(graphTST));
    
    return node;
}

graphTST* rec_insert_graph(graphTST* t, String* key, Value *valIN, Value *valOut, int d, int qtt){
    unsigned char c = key->c[d];
    

    if (t == NULL){ 
        t = create_node_graph(); 
        t->c = c;

    }
    if (c < t->c){
        t->l = rec_insert_graph(t->l, key, valIN,valOut, d, qtt); 
    }
    else if (c > t->c) { 
        t->r = rec_insert_graph(t->r, key, valIN,valOut, d, qtt); 
    }
    else if (d < key->len - 1){
        t->m = rec_insert_graph(t->m, key, valIN,valOut, d+1, qtt);
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
            t->inQtt += qtt;
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
            t->outQtt += qtt;
        }
    }
    
    return t;
}

graphTST* TST_insert_graph(graphTST* t, String* key , Value *valIN, Value *valOut, int qtt){
    return rec_insert_graph(t, key, valIN,valOut, 0, qtt);
}

graphTST* rec_search_graph(graphTST* t, String* key, int d){
    if (t == NULL) { 
        return NULL; 
    }
    unsigned char c = key->c[d];
    if (c < t->c) { 
        return rec_search_graph(t->l, key, d); 
    }
    else if (c > t->c) { 
        return rec_search_graph(t->r, key, d); 
    }
    else if (d < key->len - 1) {
        return rec_search_graph(t->m, key, d+1);
    } 
    else { 
        return t; 
    }
}

Value* TST_search_graph(graphTST* t, String* key){
    t = rec_search_graph(t, key, 0);
    if (t == NULL) { 
        return NULL; 
    }
    else {
        return t->outValues; 
    }
}
void free_tst_graph(graphTST *t){
    if (t == NULL) {
        return;
    }

    // Libera a subárvore esquerda, do meio e direita recursivamente
    free_tst_graph(t->l);
    free_tst_graph(t->m);
    free_tst_graph(t->r);

    // Libera os valores associados ao nó atual
    if (t->inValues) {
        free_value(t->inValues);
    }
    if (t->outValues) {
        free_value(t->outValues);
    }

    // Finalmente, libera o nó atual
    free(t);
}