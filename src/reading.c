#include "reading.h"
#include <string.h>

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

void read_searches(FILE *file, TST *stopwordsTST, TST *twordsTST, graphTST *graph, int it){
    char *line = NULL;
    size_t len = 0;

    while(getline(&line, &len, file) != -1){
        printf("search:%s", line);

        line[strcspn(line, "\n")] = '\0';
        search_words(line, stopwordsTST, twordsTST, graph, it);
    }
    free(line);
}

void search_words(char *line, TST *stopwordsTST, TST *twordsTST, graphTST *graph, int it){
    int size = 20, wordsQtt = 0, arraySize = 0;
    char **textsSearched = malloc(size * sizeof(char*));
    int *textsQtt = malloc(size * sizeof(int));
    
    char *word = strtok(line, " ");
    while (word != NULL) {
        wordsQtt++;
        String *wordStr = create_string(word);

        if(TST_search(stopwordsTST, wordStr) == NULL){
            Value *val = TST_search(twordsTST, wordStr);

            if(val != NULL){
                Value *aux = val;
                bool flag = false;
                while(aux){
                    flag = false;
                    if(arraySize >= size){
                        textsSearched = realloc(textsSearched, size * 2 * sizeof(char*));
                        textsQtt = realloc(textsQtt, size * 2 * sizeof(int));
                        size *= 2;
                    }

                    for(int j = 0; j < arraySize; j++){
                        if(strcmp(textsSearched[j], aux->str.c) == 0){
                            flag = true;
                            textsQtt[j]++;
                            break;
                        }
                    }
                    if(flag == false && wordsQtt == 1){
                        textsSearched[arraySize] = strdup(aux->str.c);
                        textsQtt[arraySize] = 1;
                        arraySize++;
                    }
                    aux = aux->next;
                }
            }
        }
        free_string(wordStr);
        word = strtok(NULL, " ");
    }

    normalize_arrays(textsSearched, textsQtt, wordsQtt, arraySize, graph, it);

    for (int i = 0; i < arraySize; i++) {
        free(textsSearched[i]);
    }
    free(textsSearched);
    free(textsQtt);
}

void normalize_arrays(char **textsSearched, int *textsQtt, int wordsQtt, int arraySize, graphTST *graph, int it){
    Result *results = malloc(arraySize * sizeof(Result));
    int j = 0;

    for(int i = 0; i < arraySize; i++){
        if(textsQtt[i] == wordsQtt){
            String *word = create_string(textsSearched[i]);
            graphTST *node = TST_search_graph(graph, *(word));
            Result result;
            result.text = strdup(textsSearched[i]);
            result.rank = node->pr[it];
            results[j] = result;

            free_string(word);
            j++;
        }
    }

    results = realloc(results, (j * sizeof(Result)));
    quick_sort(results, 0, j-1);
    print_result(results, j);

    for(int i = 0; i < j; i++){
        free(results[i].text);
    }
    free(results);
} 

void exch(Result A, Result B){
    Result t = A; 
    A = B; 
    B = t; 
}

int partition(Result *a, int lo, int hi){
    int i = lo, j = hi+1;
    Result v = a[lo];
    while(1) {
        while (a[++i].rank < v.rank)
        if (i == hi) break;
        while (v.rank < a[--j].rank)
        if (j == lo) break;
        if (i >= j) break;
        exch(a[i], a[j]);
    }
    exch(a[lo], a[j]); 
    return j;
}

void quick_sort(Result *a, int lo, int hi){
    if (hi <= lo) {
        return;
    }
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j-1);
    quick_sort(a, j+1, hi);
}

void print_result(Result *results, int size){
    printf("pages:");
    for(int i = 0; i < size; i++){
        printf("%s ", results[i].text);
    }
    printf("\npr:");
    for(int i = 0; i < size; i++){
        printf("%.17f ", results[i].rank);
    }
    printf("\n");
}