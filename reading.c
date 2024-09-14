#include "reading.h"


TST* create_stopwords_tst(FILE *file){
    TST *stopwordsTST = NULL;
    char *line = NULL;
    size_t len = 0;
    int i = 0;

    while(getline(&line, &len, file) != -1){
        String *word = create_string(line);

        Value* val = calloc(1, sizeof(Value));
        char str[12]; // Tamanho suficiente para armazenar o inteiro e o terminador nulo
        sprintf(str, "%d", i);

        // Converte o inteiro para uma string
        val->str.len = 1;
        val->str.c = strdup(str);
        
        stopwordsTST = TST_insert(stopwordsTST, word, val);
        
        free_string(word);
        i++;
    }

    free(line);
    return stopwordsTST;
}

TST *create_twords_tst(FILE *file, TST *stopwordsTST, char *pagesStr){
    TST *twordsTST = NULL;
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, file) != -1){
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

TST *read_pages(FILE *file, TST *twordsTST, TST *stopwordsTST, char *path){
    char *line = NULL;
    size_t len = 0;
        
    while (getline(&line, &len, file) != -1){
        line[strcspn(line, "\n")] = '\0';
        char *word = strtok(line, " ");

        while(word != NULL){
            String *wordStr = create_string(word);
            Value *val = create_value(path);

            twordsTST = TST_insert(twordsTST, wordStr, val);
            
            free_string(wordStr);
            word = strtok(NULL, " ");
        }    
    }

    free(line);
    return twordsTST;
}

graphTST* create_graph_tst(FILE *file, int *count){
    graphTST *tst = NULL;
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, file) != -1){
        (*count)++;
        line[strcspn(line, "\n")] = '\0';
        char *word = strtok(line, " ");
       
        String *wordStr = create_string(word);

        Value *outVal = NULL;
        
        char *n = strtok(NULL, " ");
        int count = atoi(n);

        while ((word = strtok(NULL, " ")) != NULL) {
            outVal = add_new_value(outVal, word);

            String *outWord = create_string(word);

            Value *inVal = create_value(wordStr->c);

            tst = TST_insert_graph(tst, outWord, inVal, NULL, 1);

            free_string(outWord);
        }
        tst = TST_insert_graph(tst, wordStr, NULL, outVal, count);
        
        free_string(wordStr);
    }
    free(line);
    return tst;
}

Value *add_new_value(Value *head, char *word) {
    Value *new_val = create_value(word);

    if (head == NULL) {
        return new_val; 
    }
    
    Value *current = head;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_val;
    Value *aux = head;
    while(aux){
        aux = aux->next;
    }
    return head;
}