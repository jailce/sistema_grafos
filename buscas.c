#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

/*
  Imprime o percurso da DFS a partir do vértice 'origem'
  Implementada recursivamente
*/

void dfsRecursiva(Grafo *g, int origem, int *visitado) {
  // Marca o nó atual como visitado e imprime seu índice
  No *atual = g->lista[origem];
  visitado[origem] = 1;
  printf("%d ", origem);

  // Para todos os vértices adjacentes ao atual, processar recursivamente
  while (atual != NULL) {
    if (visitado[atual->destino] == 0) {
      dfsRecursiva(g, atual->destino, visitado);
    }
    atual = atual->prox;
  }
}

/*
  Imprime o percurso da DFS a partir do vértice 'origem'
  Implementada iterativamente
*/

void dfsIterativa(Grafo *g, int origem) {
  int *pilha = (int *)malloc(sizeof(int) * g->V);
  int *visitado = (int *)calloc(g->V, sizeof(int));

  if (visitado == NULL || pilha == NULL) {
    printf("Erro na alocacao de memoria\n");
    exit(1);
  }

  // Começa empilhando a origem
  pilha[0] = origem;
  visitado[origem] = 1;
  int topo = 1;

  while (topo > 0) {
    // Desempilha o vértice do topo
    int v = pilha[--topo];
    printf("%d ", v);

    // Empilha todos os vizinhos não visitados do vértice v
    No *atual = g->lista[v];
    while (atual != NULL) {
      if (!visitado[atual->destino]) {
        visitado[atual->destino] = 1;
        pilha[topo++] = atual->destino;
      }
      atual = atual->prox;
    }
  }

  free(visitado);
  free(pilha);
}

/*
  Imprime o percurso da busca em largura a partir do vértice 'origem'
*/

void bfs(Grafo *g, int origem) {
  int *fila = (int *)malloc(sizeof(int) * g->V);
  int *visitado = (int *)calloc(g->V, sizeof(int));

  if (fila == NULL || visitado == NULL) {
    printf("Erro na alocacao de memoria\n");
    exit(1);
  }

  fila[0] = origem;
  visitado[origem] = 1;

  int inicio = 0; // ponteiro para o inicio da fila (próximo a ser processado)
  int fim = 1;

  while (inicio < fim) {
    // Desenfileira o próximo vértice a ser processado
    int v = fila[inicio++];
    printf("%d ", v);

    // Enfileira todos os vizinhos não visitados do vértice v
    No *atual = g->lista[v];
    while (atual != NULL) {
      if (visitado[atual->destino] == 0) {
        visitado[atual->destino] = 1; // No BFS é necessário marcar como
                                      // visitado assim que o nó é enfileirado
        fila[fim++] = atual->destino;
      }
      atual = atual->prox;
    }
  }

  free(visitado);
  free(fila);
}

/*
  Imprime todos os componentes conexos do grafo e retorna um inteiro
  representando o número de componentes conexos do grafo
*/

int componentesConexos(Grafo *g) {
  int qtd = 0;
  int *visitado = (int *)calloc(g->V, sizeof(int));
  if (visitado == NULL) {
    printf("Erro na alocacao de memoria\n");
    exit(1);
  }

  for (int i = 0; i < g->V; ++i) {
    if (visitado[i] == 0) {
      printf("Componente conexo %d\n", ++qtd);
      dfsRecursiva(g, i, visitado);
      printf("\n\n");
    }
  }

  free(visitado);

  return qtd;
}

/*
  Retorna um array de inteiros alocado dinamicamente com tamanho igual
  ao número de vértices do grafo, onde dist[i] representa a distância do
  vértice origem até o vértice i.
*/

int *bfsDistancias(Grafo *g, int origem) {
  int *dist = (int *)malloc(sizeof(int) * g->V);
  int *fila = (int *)malloc(sizeof(int) * g->V);
  int *visitado = (int *)calloc(g->V, sizeof(int));

  if (fila == NULL || dist == NULL || visitado == NULL) {
    printf("Erro na alocacao de memoria\n");
    exit(1);
  }

  for (int i = 0; i < g->V; ++i) {
    dist[i] = -1;
  }

  fila[0] = origem;
  dist[origem] = 0;
  visitado[origem] = 1;
  int inicio = 0; // ponteiro para o inicio da fila (próximo a ser processado)
  int fim = 1;

  while (inicio < fim) {
    // Desenfileira o próximo vértice a ser processado
    int v = fila[inicio++];

    // Enfileira todos os vizinhos não visitados do vértice v
    No *atual = g->lista[v];
    while (atual != NULL) {
      if (!visitado[atual->destino]) {
        visitado[atual->destino] = 1; // No BFS é necessário marcar como
                                      // visitado assim que o nó é enfileirado

        // A distância do vértice atual é a distância até o pai + 1:
        dist[atual->destino] = dist[v] + 1;

        fila[fim++] = atual->destino;
      }
      atual = atual->prox;
    }
  }

  free(visitado);
  free(fila);

  return dist;
}
