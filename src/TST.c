#include "TST.h"
#include <string.h>
#include <stdbool.h>

#define NULL_Value NULL

TST* create_node(){
    TST* node = calloc(1, sizeof(TST));
    node->val = NULL_Value;
    return node;
}

TST* rec_insert(TST* t, String* key, Value *val, int d) {
    unsigned char c = key->c[d];
    if (t == NULL){ 
        t = create_node(); 
        t->c = c;
    }
    if (c < t->c){
        t->l = rec_insert(t->l, key, val, d); 
    }
    else if (c > t->c) { 
        t->r = rec_insert(t->r, key, val, d); 
    }
    else if (d < key->len - 1){
        t->m = rec_insert(t->m, key, val, d+1);
    } 
    else{
        if(t->val == NULL){
            t->val = val;
            t->tail = val;
        }
        else{
            if(strcmp(t->tail->str.c, val->str.c) == 0){
                free(val->str.c);
                free(val);
            }
            else{
                t->tail->next = val;
                t->tail = val;
            }
        }
    }
    
    return t;
}

TST* TST_insert(TST* t, String* key , Value *val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { 
        return NULL; 
    }
    unsigned char c = key->c[d];
    if (c < t->c) { 
        return rec_search(t->l, key, d); 
    }
    else if (c > t->c) { 
        return rec_search(t->r, key, d); 
    }
    else if (d < key->len - 1) {

        return rec_search(t->m, key, d+1);
    } 
    else { 
        return t; 
    }
}

Value* TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    
    if (t == NULL) { 
        return NULL; 
    }
    else {
        return t->val; 
    }
}

void free_value(Value *val) {
    while (val != NULL) {
        Value *next = val->next;

        free(val->str.c);
        free(val);

        val = next;
    }
}

void free_tst(TST *t) {
    if (t == NULL) {
        return;
    }

    free_tst(t->l);
    free_tst(t->m);
    free_tst(t->r);

    if (t->val) {
        free_value(t->val);
    }

    free(t);
}

Value *create_value(char *string){
    Value *val = calloc(1, sizeof(Value));
    val->str.c = strdup(string);
    val->str.len = strlen(string);

    return val;
}

String *create_string(char *string){
    String *str = malloc(sizeof(String));
    str->c = strdup(string);
    str->len = strlen(str->c);

    return str;
}

void free_string(String *string){
    free(string->c);
    free(string);
}