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

// Função para extrair o vértice com a chave mínima que ainda não está na árvore geradora mínima
int extrairMinimo(int *chave, int *na_mst, int V) {
    // -1 indica que nenhum vértice foi encontrado ainda
    int minimo = -1;
    int indice_minimo = -1;

    // Loop para encontrar o vértice com a chave mínima
    for (int v = 0; v < V; v++) {
        // Verifica se o vértice v ainda não está na árvore geradora mínima e se sua chave é válida
        if (na_mst[v] == 0 && chave[v] != -1) {
            if (minimo == -1 || chave[v] < minimo) {
                minimo = chave[v];
                indice_minimo = v;
            }
        }
    }
    return indice_minimo;
}

// Função para implementar o algoritmo de Prim para encontrar a árvore geradora mínima de um grafo
void prim(Grafo *g) {
    int V = g->V;
    int *pai = (int*)malloc(V * sizeof(int));
    int *chave = (int*)malloc(V * sizeof(int));
    int *mst = (int*)malloc(V * sizeof(int));
    int peso_total = 0;

    for (int i = 0; i < V; i++) {
        chave[i] = -1;
        pai[i] = -1;
    }

    // Inicializa todos os vértices como não incluídos na árvore geradora mínima
    for (int inicio = 0; inicio < V; inicio++) {
        // Verifica se o vértice de início ainda não está na árvore geradora mínima
        if (mst[inicio] == 0) {
            chave[inicio] = 0;

            // Continua o processo até que todos os vértices estejam incluídos na árvore geradora mínima
            for (int count = 0; count < V; count++) {
                int u = extrairMinimo(chave, mst, V);

                // Se não houver mais vértices para processar, sai do loop
                if (u == -1) break;

                mst[u] = 1;
                No* atual = g->lista[u];

                // Atualiza as chaves e os pais dos vértices adjacentes ao vértice
                while (atual != NULL) {
                    int v = atual->destino;
                    int peso = atual->peso;

                    // Se o vértice v ainda não estiver na árvore geradora mínima e o peso da aresta for menor que a chave atual, atualiza o pai e a chave
                    if (mst[v] == 0 && (chave[v] == -1 || peso < chave[v])) {
                        pai[v] = u;
                        chave[v] = peso;
                    }
                    atual = atual->prox;
                }
            }
        }
    }

    // Imprime as arestas da árvore geradora mínima e calcula o peso total
    printf("Arestas da Árvore Geradora Minima:\n");
    printf("Origem - Destino - Peso\n");
    for (int i = 0; i < V; i++) {
        if (pai[i] != -1) {
            printf("    %d - %d | %d\n", pai[i], i, chave[i]);
            peso_total += chave[i];
        }
    }
    printf("Peso total: %d\n", peso_total);

    free(pai);
    free(chave);
    free(mst);
}