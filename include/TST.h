#ifndef TST_H_
#define TST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

typedef struct Value{
    struct Value *next;
    String str;
}Value;

typedef struct node TST;
struct node {
    Value *val;
    Value *tail;
    unsigned char c;
    TST *l, *m, *r;
};

TST* create_node();
TST* rec_insert(TST* t, String* key, Value *val, int d);
TST* TST_insert(TST* t, String* key , Value *val);
TST* rec_search(TST* t, String* key, int d);
Value* TST_search(TST* t, String* key);
Value *create_value(char *string);
void free_value(Value *val);
void free_tst(TST *t);
void free_string(String *string);
String *create_string(char *string);

#endif