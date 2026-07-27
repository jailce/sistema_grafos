#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

/*  Realiza a ordenação topológica de um grafo direcionado acíclico (DAG).
 *  Retorna 1 se a ordenação foi aciclico, ou 0 se o grafo contém ciclos.
 */

int ordenacaoTopologica(Grafo *g, int *ordem) {
    int V = g->V;
    int *grau_entrada = (int*) malloc(sizeof (int) * V);

    for (int i = 0; i < V; i++) {
        No* atual = g->lista[i];
        while (atual != NULL) {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    int *fila = (int*) malloc(V * sizeof(int));
    int inicio = 0, fim = 0;

    //
    for (int i = 0; i < V; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    int contagem = 0;

    // Processa vértices na fila
    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[contagem++] = u;

        No* vizinho = g->lista[u];
        while (vizinho != NULL) {
            int v = vizinho->destino;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
            vizinho = vizinho->prox;
        }
    }
    free(grau_entrada);
    free(fila);
    return (contagem == V) ? 1 : 0;
}


/* Realiza DFS para detectar ciclos em grafos direcionados.
 * Retorna 0 se não tem ciclo, e se tiver, retorna 1.
 */
int dfsCiclo(Grafo *g, int v, int *visitado, int *na_pilha) {
    if (visitado[v] == 0) {
        visitado[v] = 1;
        na_pilha[v] = 1;

        No* atual = g->lista[v];
        while (atual != NULL) {
            int vizinho = atual->destino;

            if (!visitado[vizinho] && dfsCiclo(g, vizinho, visitado, na_pilha)) {
                return 1;
            } else if (na_pilha[vizinho]) {
                return 1;
            }
            atual = atual->prox;
        }
    }
    na_pilha[v] = 0;
    return 0;
}


/* Realiza a detecção de ciclos em grafos direcionados.
 * Retorna 1 se o grafo contém ciclos, ou 0 se não contém.
 */

int detectaCicloDirecionado(Grafo *g) {
    int *visitado = (int*)malloc(g->V * sizeof(int));
    int *na_pilha = (int*)malloc(g->V * sizeof(int));

    for (int i = 0; i < g->V; i++) {
        if (!visitado[i]) {
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