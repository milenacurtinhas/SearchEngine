#include "graphTST.h"
#include <math.h>

graphTST* create_node_graph(){
    graphTST* node = calloc(1, sizeof(graphTST));
    node->pr = NULL;

    return node;
}

graphTST* rec_insert_graph(graphTST* t, String* key, Value *valIN, Value *valOut, int d, int qtt){
    unsigned char c = key->c[d];
    

    if (t == NULL){ 
        t = create_node_graph(); 
        t->c = c;

    }
    if (c < t->c){
        t->l = rec_insert_graph(t->l, key, valIN,valOut, d, qtt); 
    }
    else if (c > t->c) { 
        t->r = rec_insert_graph(t->r, key, valIN,valOut, d, qtt); 
    }
    else if (d < key->len - 1){
        t->m = rec_insert_graph(t->m, key, valIN,valOut, d+1, qtt);
    } 
    else{
        if(valIN){
            if(t->inValues == NULL){
                t->inValues = valIN;
            }
            else{
                Value* value = t->inValues;
                while(value->next != NULL){
                    value = value->next;
                }
                value->next = valIN;
            }
            t->inQtt += qtt;
        }
        if(valOut){
            if(t->outValues == NULL){
                t->outValues = valOut;
            }
            else{
                Value* value = t->outValues;
                while(value->next != NULL){
                    value = value->next;
                }
                value->next = valOut;
            }
            t->outQtt += qtt;
        }
    }
    
    return t;
}

graphTST* TST_insert_graph(graphTST* t, String* key , Value *valIN, Value *valOut, int qtt){
    return rec_insert_graph(t, key, valIN,valOut, 0, qtt);
}

graphTST* rec_search_graph(graphTST* t, String key, int d){
    if (t == NULL) { 
        return NULL; 
    }
    unsigned char c = key.c[d];
    if (c < t->c) { 
        return rec_search_graph(t->l, key, d); 
    }
    else if (c > t->c) { 
        return rec_search_graph(t->r, key, d); 
    }
    else if (d < key.len - 1) {
        return rec_search_graph(t->m, key, d+1);
    } 
    else { 
        return t; 
    }
}

graphTST* TST_search_graph(graphTST* t, String key){
    t = rec_search_graph(t, key, 0);
    if (t == NULL) { 
        return NULL; 
    }
    else {
        return t; 
    }
}
void free_tst_graph(graphTST *t){
    if (t == NULL) {
        return;
    }

    // Libera a subárvore esquerda, do meio e direita recursivamente
    free_tst_graph(t->l);
    free_tst_graph(t->m);
    free_tst_graph(t->r);

    // Libera os valores associados ao nó atual
    if (t->inValues) {
        free_value(t->inValues);
    }
    if (t->outValues) {
        free_value(t->outValues);
    }
    
    free(t->pr);
    // Finalmente, libera o nó atual
    free(t);
}

graphTST *collectWordsFirstIT(graphTST *node, char *buffer, int depth, int qtt) {
    if (node == NULL) return node;

    // Percorrer a subárvore da esquerda
    node->l = collectWordsFirstIT(node->l, buffer, depth, qtt);

    // Adiciona o caractere atual ao buffer
    buffer[depth] = node->c;

    // Se chegamos ao final de uma palavra (quando inValues ou outValues estão definidos), imprime a palavra
    if (node->inValues != NULL || node->outValues != NULL) {
        buffer[depth + 1] = '\0';  // Termina a string

        // Aloca memória para node->pr
        node->pr = malloc(sizeof(double) * 10);
        // Inicializa o primeiro elemento de node->pr
        node->pr[0] = 1 / (double)qtt;
         printf("page rank iteracao 0 palavra %s: %f\n", buffer, node->pr[0]);
    }

    // Percorrer o meio
    node->m = collectWordsFirstIT(node->m, buffer, depth + 1, qtt);

    // Percorrer a subárvore da direita
    node->r = collectWordsFirstIT(node->r, buffer, depth, qtt);

    return node;
}


graphTST* collectWords(graphTST *node,graphTST *root, char *buffer, int depth, int qtt, int it) {
    if (node == NULL) return node;

    // Percorrer a subárvore da esquerda
    node->l = collectWords(node->l, root,buffer, depth, qtt, it);

    // Adiciona o caractere atual ao buffer
    buffer[depth] = node->c;

    // Se chegamos ao final de uma palavra (quando inValues ou outValues estão definidos)
    if (node->inValues != NULL || node->outValues != NULL) {
        buffer[depth + 1] = '\0';  // Termina a string
        
        if(it%10 == 0){
            node->pr = realloc(node->pr, (it + 10) * sizeof(double));
        }
        double sum = prSum(node, root, it);
        node->pr[it] = prCalc(node->pr[it-1], node->outQtt, sum, qtt);
        
        printf("quantidade de ins: %d // quantidade de outs: %d//page rank iteracao %d palavra %s: %f\n",node->inQtt,node->outQtt ,it, buffer, node->pr[it]);
    }

    // Percorrer o meio
    node->m = collectWords(node->m, root, buffer, depth + 1, qtt, it);

    // Percorrer a subárvore da direita
    node->r = collectWords(node->r,root, buffer, depth, qtt, it);

    return node;  // Retorna o nó atualizado
}

double prSum(graphTST *node, graphTST *root, int it){
    double sum = 0;
    if(node->inValues != NULL){

        Value *aux = node->inValues;
        
        while(aux){
            printf("ins: %s ", aux->str.c);
            graphTST *inNode = TST_search_graph(root, aux->str);

            if(inNode != NULL){
                sum = inNode->pr[it-1]/(double)inNode->outQtt;
                aux = aux->next;
            }
        }
    }
    printf("\n");
    return sum;
}

double prCalc(double prMinus, int outQtt, double sum, int n){
    if(outQtt > 0){
        return (0.15/(double)n) + (0.85*sum);
    }
    else if(outQtt == 0){
        return (0.15/(double)n) + (0.85*prMinus) + (0.85*sum);
    }
}
void collectDifferences(graphTST *node, double *sum, int it) {
    if (node == NULL) return;

    // Percorrer a subárvore da esquerda
    collectDifferences(node->l, sum, it);

    // Verifica se o nó tem um array `pr` e se o índice `it` é válido
    if (node->pr != NULL && it > 0 && it < node->inQtt) {
        *sum += fabs((node->pr[it] - node->pr[it - 1]));
        
    }

    // Percorrer o meio
    collectDifferences(node->m, sum, it);

    // Percorrer a subárvore da direita
    collectDifferences(node->r, sum, it);
}

double errorAtt(int n, int k, graphTST *tst){
    double sum = 0;
    collectDifferences(tst, &sum, k);
    
    return (1/(double)n)*sum;
}

graphTST *pageRankCalc(graphTST* tst, int tstSize){
    char buffer[100];
    tst = collectWordsFirstIT(tst, buffer, 0, tstSize);
    double error = 1;
    int it = 1;
    graphTST *root = tst;

    while(error > 0.000001){
        tst = collectWords(tst, root, buffer, 0, tstSize, it);
        error = errorAtt(tstSize, it,tst);
        it++;
    }
    printf("iteracoes: %d\n", it);
    return tst;
}

