#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>


/*  Realiza a ordenação topológica de um grafo direcionado acíclico (DAG).
 *  Retorna 1 se a ordenação foi aciclico, ou 0 se o grafo contém ciclos.
 */

int ordenacaoTopologica(Grafo *g, int *ordem) {
    int V = g->V;
    int *grau_de_entrada = (int*) malloc(sizeof (int) * V);

    // Calcula o grau de entrada de cada vértice
    for (int i = 0; i < V; i++) {
        No* atual = g->lista[i];
        // Atualiza o grau de entrada do vértice destino para cada aresta
        while (atual != NULL) {
            grau_de_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    int *fila = (int*) malloc(V * sizeof(int));
    int inicio = 0, fim = 0;

    // Adiciona vértices com grau de entrada zero à fila
    for (int i = 0; i < V; i++) {
        if (grau_de_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int contagem = 0;

    // Processa vértices na fila
    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[contagem++] = u;

        No* vizinho = g->lista[u];
        // Atualiza o grau de entrada dos vizinhos e adiciona à fila se o grau de entrada for zero
        while (vizinho != NULL) {
            int v = vizinho->destino;
            grau_de_entrada[v]--;

            if (grau_de_entrada[v] == 0) {
                fila[fim++] = v;
            }
            vizinho = vizinho->prox;
        }
    }
    free(grau_de_entrada);
    free(fila);
    return (contagem == V) ? 1 : 0;
}


/* Realiza DFS para detectar ciclos em grafos direcionados.
 * Retorna 0 se não tem ciclo, e se tiver, retorna 1.
 */
int dfsCiclo(Grafo *g, int v, int *visitado, int *pilha) {
    // Marca o vértice como visitado e adiciona à pilha
    if (visitado[v] == 0) {
        visitado[v] = 1;
        pilha[v] = 1;

        // Percorre os vizinhos do vértice
        No* atual = g->lista[v];
        while (atual != NULL) {
            int vizinho = atual->destino;

            // Se o vizinho não foi visitado, realiza DFS recursivamente
            if (!visitado[vizinho] && dfsCiclo(g, vizinho, visitado, pilha)) {
                return 1;
            }
            // Se o vizinho está na pilha, significa que há um ciclo
            if (pilha[vizinho]) {
                return 1;
            }
            atual = atual->prox;
        }
    }
    pilha[v] = 0;
    return 0;
}


/* Realiza a detecção de ciclos em grafos direcionados.
 * Retorna 1 se o grafo contém ciclos, ou 0 se não contém.
 */

int detectaCicloDirecionado(Grafo *g) {
    int *visitado = (int*)malloc(g->V * sizeof(int));
    int *na_pilha = (int*)malloc(g->V * sizeof(int));

    // Inicializa os arrays de visitado e na_pilha
    for (int i = 0; i < g->V; i++) {
        visitado[i] = 0;
        na_pilha[i] = 0;
    }
    // Percorre todos os vértices
    for (int i = 0; i < g->V; i++) {
        // Se o vértice não foi visitado, realiza DFS
        if (!visitado[i]) {
            // Se a DFS detectar um ciclo, libera a memória e retorna 1
            if (dfsCiclo(g, i, visitado, na_pilha)) {
                free(visitado);
                free(na_pilha);
                return 1;
            }
        }
    }
    free(visitado);
    free(na_pilha);
    return 0;
}