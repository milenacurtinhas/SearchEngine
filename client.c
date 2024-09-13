#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"

int main(int argc, char *argv[]) {
    char *diretorio = argv[1];

    char *indexStr = malloc(strlen(diretorio) + strlen("/index.txt") + 1);
    strcpy(indexStr, diretorio);
    strcat(indexStr, "/index.txt");

    char *graphStr = malloc(strlen(diretorio) + strlen("/graph.txt") + 1);
    strcpy(graphStr, diretorio);
    strcat(graphStr, "/graph.txt");

    char *stopwordsStr = malloc(strlen(diretorio) + strlen("/stopwords.txt") + 1);
    strcpy(stopwordsStr, diretorio);
    strcat(stopwordsStr, "/stopwords.txt");

    char *pagesStr = malloc(strlen(diretorio) + strlen("/pages/") + 1);
    strcpy(pagesStr, diretorio);
    strcat(pagesStr, "/pages/");
    
    FILE *index = fopen(indexStr, "r");
    FILE *graph = fopen(graphStr, "r");
    FILE *stopwords = fopen(stopwordsStr, "r");

    TST *stopwordsTST = create_stopwords_tst(stopwords);
    TST *twordsTST = create_twords_tst(index, stopwordsTST, pagesStr);
    TST *graphTST = create_graph_tst(graph);
    
    free_tst(stopwordsTST);
    free_tst(twordsTST);
    free_tst(graphTST);
    free(indexStr);
    free(graphStr);
    free(stopwordsStr);
    free(pagesStr);
    fclose(index);
    fclose(graph);
    fclose(stopwords);

    return 0;
}