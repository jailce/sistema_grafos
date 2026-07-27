#include "grafo.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


/* Este arquivo implementa o algoritmo de Dijkstra para encontrar 
o menor caminho entre dois vértices em um grafo ponderado. */

#define INF (INT_MAX / 4)
// Função auxiliar para extrair o vértice com a menor distância ainda não visitado
static int extrairMinimoDijkstra(int *dist, int *visitado, int V) {
    int minimo = INF;
    int indice = -1;

    for (int v = 0; v < V; v++) {
        if (!visitado[v] && dist[v] < minimo) {
            minimo = dist[v];
            indice = v;
        }
    }

    return indice;
}
// Implementação do algoritmo de Dijkstra
void dijkstra(Grafo *g, int origem, int **dist, int **anterior) {
    if (g == NULL || dist == NULL || anterior == NULL || origem < 0 || origem >= g->V) {
        return;
    }

    int V = g->V;
    int *distancias = (int*) malloc(V * sizeof(int));
    int *predecessor = (int*) malloc(V * sizeof(int));
    int *visitado = (int*) calloc(V, sizeof(int));

    if (distancias == NULL || predecessor == NULL || visitado == NULL) {
        free(distancias);
        free(predecessor);
        free(visitado);
        return;
    }

    for (int i = 0; i < V; i++) {
        distancias[i] = INF;
        predecessor[i] = -1;
    }
    distancias[origem] = 0;

    for (int cont = 0; cont < V; cont++) {
        int u = extrairMinimoDijkstra(distancias, visitado, V);
        if (u == -1) {
            break;
        }

        visitado[u] = 1;

        for (No *atual = g->lista[u]; atual != NULL; atual = atual->prox) {
            int v = atual->destino;
            int peso = atual->peso;

            if (!visitado[v] && distancias[u] != INF && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                predecessor[v] = u;
            }
        }
    }

    free(visitado);
    *dist = distancias;
    *anterior = predecessor;
}
// Função para imprimir o caminho do vértice de origem até o vértice de destino usando o vetor de predecessores
void imprimirCaminho(int *anterior, int origem, int destino) {
    if (destino == origem) {
        printf("%d", origem);
        return;
    }

    if (anterior[destino] == -1) {
        printf("sem caminho");
        return;
    }

    imprimirCaminho(anterior, origem, anterior[destino]);
    printf(" -> %d", destino);
}
// Função que combina a execução do algoritmo de Dijkstra e a impressão do caminho até um vértice alvo
void executarDijkstra(Grafo *g, int origem, int destinoAlvo) {
    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return;
    }

    if (origem < 0 || origem >= g->V || destinoAlvo < 0 || destinoAlvo >= g->V) {
        printf("Vertice invalido.\n");
        return;
    }

    int *dist = NULL;
    int *anterior = NULL;
    dijkstra(g, origem, &dist, &anterior);

    if (dist == NULL || anterior == NULL) {
        printf("Erro ao executar Dijkstra.\n");
        free(dist);
        free(anterior);
        return;
    }

// Imprime os resultados do algoritmo de Dijkstra
    printf("\n=== DIJKSTRA (Origem: %d) ===\n", origem);
    printf("Vertice | Distancia | Caminho\n");
    printf("--------|-----------|------------------\n");

    for (int v = 0; v < g->V; v++) {
        printf("%d | ", v);
        if (dist[v] == INF) {
            printf("INF | sem caminho\n");
            continue;
        }

        printf("%d | ", dist[v]);
        imprimirCaminho(anterior, origem, v);
        printf("\n");
    }

    if (destinoAlvo >= 0 && destinoAlvo < g->V) {
        printf("\nCaminho ate o alvo %d: ", destinoAlvo);
        if (dist[destinoAlvo] == INF) {
            printf("sem caminho\n");
        } else {
            imprimirCaminho(anterior, origem, destinoAlvo);
            printf("\n");
        }
    }

    free(dist);
    free(anterior);
}
