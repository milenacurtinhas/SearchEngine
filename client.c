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
    
    FILE *indexFile  = fopen(indexStr, "r");
    FILE *graphFile = fopen(graphStr, "r");
    FILE *stopwordsFile  = fopen(stopwordsStr, "r");

    TST *stopwordsTST = create_stopwords_tst(stopwordsFile);
    TST *twordsTST = create_twords_tst(indexFile , stopwordsTST, pagesStr);
    int n = 0;
    int it = 0;
    graphTST *graph = create_graph_tst(graphFile, &n);
    graph = pageRankCalc(graph, n, &it);
    printf("n its: %d\n", it);
    
    free_tst(stopwordsTST);
    free_tst(twordsTST);
    free_tst_graph(graph);
    free(indexStr);
    free(graphStr);
    free(stopwordsStr);
    free(pagesStr);
    fclose(indexFile);
    fclose(graphFile);
    fclose(stopwordsFile);

    return 0;
}