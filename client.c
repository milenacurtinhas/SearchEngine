#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reading.h"
#include <time.h>

int main(int argc, char *argv[]) {
    char *diretorio = argv[1];
    // clock_t start, end, head, tail;
    // double cpu_time_used;

    // head = clock();

    char *stopwordsStr = malloc(strlen(diretorio) + strlen("/stopwords.txt") + 1);
    strcpy(stopwordsStr, diretorio);
    strcat(stopwordsStr, "/stopwords.txt");

    FILE *stopwordsFile  = fopen(stopwordsStr, "r");
// start = clock();
    TST *stopwordsTST = create_stopwords_tst(stopwordsFile);
// end = clock();
// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
// printf("create_stopwords_tst() time: %.3lf seconds\n", cpu_time_used);
    fclose(stopwordsFile);
    

    char *indexStr = malloc(strlen(diretorio) + strlen("/index.txt") + 1);
    strcpy(indexStr, diretorio);
    strcat(indexStr, "/index.txt");

    char *pagesStr = malloc(strlen(diretorio) + strlen("/pages/") + 1);
    strcpy(pagesStr, diretorio);
    strcat(pagesStr, "/pages/");

    FILE *indexFile  = fopen(indexStr, "r");
// start = clock();
    TST *twordsTST = create_twords_tst(indexFile, stopwordsTST, pagesStr);
// end = clock();
// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
// printf("create_twords_tst() time: %.3lf seconds\n", cpu_time_used);
    fclose(indexFile);

    char *graphStr = malloc(strlen(diretorio) + strlen("/graph.txt") + 1);
    strcpy(graphStr, diretorio);
    strcat(graphStr, "/graph.txt");

    FILE *graphFile = fopen(graphStr, "r");
    int n = 0, it = 0;
// start = clock();
    graphTST *graph = create_graph_tst(graphFile, &n);
// end = clock();
// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;   
// printf("create_graph_tst() time: %.3lf seconds\n", cpu_time_used);
    fclose(graphFile);

// start = clock();
     graph = pageRankCalc(graph, n, &it);
// end = clock();
// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
// printf("pageRankCalc() time: %.3lf seconds\n", cpu_time_used);


    char *searchesStr = malloc(strlen(diretorio) + strlen("/searches.txt") + 1);
    strcpy(searchesStr, diretorio);
    strcat(searchesStr, "/searches.txt");

    FILE *searchesFile = fopen(searchesStr, "r");
// start = clock();
    read_searches(searchesFile, stopwordsTST, twordsTST, graph, it);
// end = clock();
// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
// printf("read_searches() time: %.3lf seconds\n", cpu_time_used);
    fclose(searchesFile);

    free_tst(stopwordsTST);
    free_tst(twordsTST);
    free_tst_graph(graph);
    
    free(stopwordsStr);
    free(indexStr);
    free(pagesStr);
    free(graphStr);
    free(searchesStr);

    // tail = clock();
    // cpu_time_used = ((double)(tail - head)) / CLOCKS_PER_SEC;
    // printf("total time: %.3lf seconds\n", cpu_time_used);

    return 0;
}