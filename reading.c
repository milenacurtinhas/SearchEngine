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
        val->str.len = 1;
        val->str.c = strdup(str);
        
        stopwordsTST = TST_insert(stopwordsTST, word, val);
        
        free(word->c);
        free(word);
        i++;
    }

    free(line);
    return stopwordsTST;
}

TST *create_twords_tst(char *pagesStr, FILE *index, TST *stopwordsTST){
    TST *twordsTST = NULL;
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, index) != -1){
        line[strcspn(line, "\n")] = '\0';
        char *path = strdup(line);
        char *page = malloc(strlen(pagesStr) + strlen(path) + 1);
        strcpy(page, pagesStr);
        strcat(page, path);

        FILE *file = fopen(page, "r");
        
        twordsTST = read_pages(file, twordsTST, stopwordsTST, path);
                
        fclose(file);
        free(path);
        free(page);
    }
   
    free(line); 
    return twordsTST;
}

TST * read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path){
    char *line = NULL;
    size_t len = 0;
        
    while (getline(&line, &len, file) != -1){

        line[strcspn(line, "\n")] = '\0';
        char *word = strtok(line, " ");

        while(word != NULL){
            String *wordStr = calloc(1, sizeof(String));
            wordStr->c = strdup(word);
            wordStr->len = (int)strlen(word);

            Value *val = TST_search(stopwordsTST, wordStr);
            if(val == NULL){
                val = calloc(1, sizeof(Value));
                val->str.c = strdup(path);
                val->str.len = (int)strlen(path);
                twordsTST = TST_insert(twordsTST, wordStr, val);
            }
            
            free(wordStr->c);
            free(wordStr);

            word = strtok(NULL, " ");
        }
        
    }
    free(line);
    return twordsTST;
}