#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

/*
Este arquivo implementa o algoritmo de Prim para encontrar a árvore geradora mínima (MST) de um grafo não direcionado e ponderado. 
O algoritmo seleciona arestas de menor peso que conectam vértices ainda não incluídos na MST, garantindo que todos os vértices sejam conectados com o menor custo total possível.
O algoritmo de Prim é eficiente para grafos densos e é uma escolha popular para problemas de otimização de redes, como redes de computadores, sistemas de transporte e planejamento urbano.
A função prim() trata grafos desconexos internamente, imprimindo as arestas da árvore/floresta geradora mínima e o peso total da MST.
1. Inicialmente, todos os vértices são considerados não incluídos na MST.
2. O algoritmo começa com um vértice inicial e adiciona arestas de menor peso que conectam vértices ainda não incluídos na MST.
3. O processo continua até que todos os vértices estejam incluídos na MST.
*/

int extrairMinimo(int *chave, int *na_mst, int V) {
    int minimo = -1;
    int indice_minimo = -1;

    for (int v = 0; v < V; v++) {
        if (na_mst[v] == 0 && chave[v] != -1) {
            if (minimo == -1 || chave[v] < minimo) {
                minimo = chave[v];
                indice_minimo = v;
            }
        }
    }
    return indice_minimo;
}


void prim(Grafo *g) {
    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return;
    }

    if (g->direcionado) {
        printf("Aviso: Prim deve ser aplicado em grafos nao-direcionados.\n");
        printf("A execucao continuara usando as arestas carregadas.\n");
    }

    int V = g->V;
    int *pai = (int*)malloc(V * sizeof(int));
    int *chave = (int*)malloc(V * sizeof(int));
    int *na_mst = (int*)calloc(V, sizeof(int));
    int peso_total = 0;

    if (pai == NULL || chave == NULL || na_mst == NULL) {
        free(pai);
        free(chave);
        free(na_mst);
        printf("Erro na alocacao de memoria\n");
        return;
    }

    for (int i = 0; i < V; i++) {
        chave[i] = -1;
        pai[i] = -1;
    }

    for (int inicio = 0; inicio < V; inicio++) {
        if (na_mst[inicio] == 0) {
            chave[inicio] = 0;

            for (int count = 0; count < V; count++) {
                int u = extrairMinimo(chave, na_mst, V);

                if (u == -1) break;

                na_mst[u] = 1;

                No* atual = g->lista[u];
                while (atual != NULL) {
                    int v = atual->destino;
                    int peso = atual->peso;

                    if (na_mst[v] == 0 && (chave[v] == -1 || peso < chave[v])) {
                        pai[v] = u;
                        chave[v] = peso;
                    }
                    atual = atual->prox;
                }
            }
        }
    }

    printf("Arestas da Arvore/Floresta Geradora Minima:\n");
    printf("Origem - Destino \tPeso\n");
    for (int i = 0; i < V; i++) {
        if (pai[i] != -1) {
            printf("  %d    -    %d \t\t%d\n", pai[i], i, chave[i]);
            peso_total += chave[i];
        }
    }
    printf("------------------------------------\n");
    printf("Peso total: %d\n", peso_total);

    free(pai);
    free(chave);
    free(na_mst);
}