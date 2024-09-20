#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"

int main(int argc, char *argv[]) {
    char *diretorio = argv[1];

    char *stopwordsStr = malloc(strlen(diretorio) + strlen("/stopwords.txt") + 1);
    strcpy(stopwordsStr, diretorio);
    strcat(stopwordsStr, "/stopwords.txt");

    FILE *stopwordsFile  = fopen(stopwordsStr, "r");
    TST *stopwordsTST = create_stopwords_tst(stopwordsFile);
    fclose(stopwordsFile);
    

    char *indexStr = malloc(strlen(diretorio) + strlen("/index.txt") + 1);
    strcpy(indexStr, diretorio);
    strcat(indexStr, "/index.txt");

    char *pagesStr = malloc(strlen(diretorio) + strlen("/pages/") + 1);
    strcpy(pagesStr, diretorio);
    strcat(pagesStr, "/pages/");

    FILE *indexFile  = fopen(indexStr, "r");
    TST *twordsTST = create_twords_tst(indexFile, stopwordsTST, pagesStr);
    fclose(indexFile);

    char *graphStr = malloc(strlen(diretorio) + strlen("/graph.txt") + 1);
    strcpy(graphStr, diretorio);
    strcat(graphStr, "/graph.txt");

    FILE *graphFile = fopen(graphStr, "r");
    int n = 0, it = 0;
    graphTST *graph = create_graph_tst(graphFile, &n);
    fclose(graphFile);

    graph = pageRankCalc(graph, n, &it);

    read_searches(stopwordsTST, twordsTST, graph, it);

    free_tst(stopwordsTST);
    free_tst(twordsTST);
    free_tst_graph(graph);
    
    free(stopwordsStr);
    free(indexStr);
    free(pagesStr);
    free(graphStr);    

    return 0;
}