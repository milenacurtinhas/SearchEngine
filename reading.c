#include "reading.h"

TST* create_stopwords_tst(FILE *stopwords){
    TST *stopwordsTST = NULL;
    char *line = NULL;
    size_t len = 0;
    int i = 0;

    while(getline(&line, &len, stopwords) != -1){
        String *word = malloc(sizeof(String));
        word->c = strdup(line);      
        word->len = (int)strlen(word->c);

        
        Value* val = calloc(1, sizeof(Value));
        char str[12]; // Tamanho suficiente para armazenar o inteiro e o terminador nulo
        sprintf(str, "%d", i);

    // Converte o inteiro para uma string
    
        val->str.c = malloc(2*sizeof(char));
        val->str.c = strdup(str);
        val->str.len = 1;
        val->next = NULL;

        

        stopwordsTST = TST_insert(stopwordsTST, word, val);
        free(word->c);
        free(word);
        i++;
    }
    free(line);
    return stopwordsTST;
}