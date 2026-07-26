#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

/* ============================================================
 *  FUNÇÕES INTERNAS
 * ============================================================ */

/* DFS auxiliar para marcar todos os vértices alcançáveis
 * a partir de um vértice. */

static void dfsMarcarConexo(Grafo *g, int v, int *visitado) {
    visitado[v] = 1;
    for (No *aux = g->lista[v]; aux != NULL; aux = aux->prox) {
        if (!visitado[aux->destino]) {
            dfsMarcarConexo(g, aux->destino, visitado);
        }
    }
}

/* DFS auxiliar para detectar ciclo em grafo NÃO-DIRECIONADO.
 * "pai" evita que a aresta de volta ao próprio pai seja
 * confundida com um ciclo. */

static int dfsCicloNaoDirecionado(Grafo *g, int v, int pai, int *visitado) {
    visitado[v] = 1;
    for (No *aux = g->lista[v]; aux != NULL; aux = aux->prox) {
        if (!visitado[aux->destino]) {
            if (dfsCicloNaoDirecionado(g, aux->destino, v, visitado)) {
                return 1;
            }
        } else if (aux->destino != pai) {
            return 1; /* aresta de retorno para vértice já visitado != pai */
        }
    }
    return 0;
}

/* DFS auxiliar para detectar ciclo em grafo DIRECIONADO usando
 * 3 estados (0 = branco, 1 = cinza/na pilha, 2 = preto/finalizado). */
static int dfsCicloDirecionadoUtil(Grafo *g, int v, int *estado) {
    estado[v] = 1; /* cinza: em processamento */
    for (No *aux = g->lista[v]; aux != NULL; aux = aux->prox) {
        if (estado[aux->destino] == 1) {
            return 1; /* aresta de retorno -> ciclo */
        }
        if (estado[aux->destino] == 0 && dfsCicloDirecionadoUtil(g, aux->destino, estado)) {
            return 1;
        }
    }
    estado[v] = 2; /* preto: finalizado */
    return 0;
}

/* ============================================================
 *  CRIAÇÃO / LEITURA / LIBERAÇÃO
 * ============================================================ */

Grafo* criarGrafo(int V, int direcionado) {
    if (V <= 0) {
        fprintf(stderr, "Erro: numero de vertices invalido (%d).\n", V);
        return NULL;
    }

    Grafo *g = (Grafo*) malloc(sizeof(Grafo));
    if (g == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para o grafo.\n");
        return NULL;
    }

    g->V = V;
    g->A = 0;
    g->direcionado = direcionado;
    g->lista = (No**) calloc(V, sizeof(No*)); /* calloc ja inicializa com NULL */

    if (g->lista == NULL) {
        fprintf(stderr, "Erro: falha ao alocar lista de adjacencia.\n");
        free(g);
        return NULL;
    }

    return g;
}

/* Insere aresta origem -> destino de forma ORDENADA por destino.
 * Se o grafo for nao-direcionado, insere tambem destino -> origem.
 * O contador de arestas (A) e incrementado uma unica vez por
 * chamada, representando uma aresta logica do arquivo de entrada. */

void adicionarAresta(Grafo *g, int origem, int destino, int peso) {
    if (g == NULL) {
        fprintf(stderr, "Erro: grafo nao inicializado.\n");
        return;
    }
    if (origem < 0 || origem >= g->V || destino < 0 || destino >= g->V) {
        fprintf(stderr, "Erro: vertice invalido na aresta (%d, %d).\n", origem, destino);
        return;
    }

    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar no da lista de adjacencia.\n");
        return;
    }
    novo->destino = destino;
    novo->peso = peso;

    /* Insercao ordenada por destino na lista de "origem" */

    if (g->lista[origem] == NULL || g->lista[origem]->destino >= destino) {
        novo->prox = g->lista[origem];
        g->lista[origem] = novo;
    } else {
        No *atual = g->lista[origem];
        while (atual->prox != NULL && atual->prox->destino < destino) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    /* Se nao-direcionado, replica a aresta no sentido contrario */

    if (!g->direcionado) {
        No *novo2 = (No*) malloc(sizeof(No));
        if (novo2 == NULL) {
            fprintf(stderr, "Erro: falha ao alocar no da lista de adjacencia.\n");
            return;
        }
        novo2->destino = origem;
        novo2->peso = peso;

        if (g->lista[destino] == NULL || g->lista[destino]->destino >= origem) {
            novo2->prox = g->lista[destino];
            g->lista[destino] = novo2;
        } else {
            No *atual = g->lista[destino];
            while (atual->prox != NULL && atual->prox->destino < origem) {
                atual = atual->prox;
            }
            novo2->prox = atual->prox;
            atual->prox = novo2;
        }
    }

    g->A++;
}

Grafo* lerGrafoDeArquivo(const char *nomeArquivo, int direcionado) {
    FILE *arq = fopen(nomeArquivo, "r");
    if (arq == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo '%s'.\n", nomeArquivo);
        return NULL;
    }

    int V, A;
    if (fscanf(arq, "%d %d", &V, &A) != 2) {
        fprintf(stderr, "Erro: formato invalido no cabecalho do arquivo '%s'.\n", nomeArquivo);
        fclose(arq);
        return NULL;
    }

    Grafo *g = criarGrafo(V, direcionado);
    if (g == NULL) {
        fclose(arq);
        return NULL;
    }

    int origem, destino, peso;
    int lidas = 0;
    while (lidas < A && fscanf(arq, "%d %d %d", &origem, &destino, &peso) == 3) {
        adicionarAresta(g, origem, destino, peso);
        lidas++;
    }

    if (lidas < A) {
        fprintf(stderr, "Aviso: arquivo '%s' informou %d arestas mas apenas %d foram lidas.\n",
                nomeArquivo, A, lidas);
    }

    fclose(arq);
    printf("Grafo carregado com sucesso: %d vertices, %d arestas (%s).\n",
           g->V, g->A, g->direcionado ? "direcionado" : "nao-direcionado");
    return g;
}

void mostrarGrafo(Grafo *g) {
    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return;
    }

    printf("\n=== LISTA DE ADJACENCIA (%s) ===\n", g->direcionado ? "direcionado" : "nao-direcionado");
    for (int v = 0; v < g->V; v++) {
        printf("%d:", v);
        for (No *aux = g->lista[v]; aux != NULL; aux = aux->prox) {
            printf(" -> %d(peso %d)", aux->destino, aux->peso);
        }
        printf(" -> NULL\n");
    }
}

void liberarGrafo(Grafo *g) {
    if (g == NULL) return;

    for (int v = 0; v < g->V; v++) {
        No *atual = g->lista[v];
        while (atual != NULL) {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->lista);
    free(g);
}

/* ============================================================
 *  ESTATISTICAS
 * ============================================================ */

/* Retorna o grau de saida do vertice (para grafos nao-direcionados
 * isso corresponde ao grau total, pois cada aresta foi inserida
 * nas duas listas). */

int grauVertice(Grafo *g, int v) {
    if (g == NULL || v < 0 || v >= g->V) {
        fprintf(stderr, "Erro: vertice invalido (%d).\n", v);
        return -1;
    }
    int grau = 0;
    for (No *aux = g->lista[v]; aux != NULL; aux = aux->prox) {
        grau++;
    }
    return grau;
}

/* Grau de entrada: usado apenas para grafos direcionados,
 * calculado varrendo todas as listas. */

static int grauEntradaVertice(Grafo *g, int v) {
    int grau = 0;
    for (int i = 0; i < g->V; i++) {
        for (No *aux = g->lista[i]; aux != NULL; aux = aux->prox) {
            if (aux->destino == v) grau++;
        }
    }
    return grau;
}

/* Conexidade: para grafos nao-direcionados, verifica se todos os
 * vertices sao alcancaveis a partir do vertice 0 (conexidade real).
 * Para grafos direcionados, verifica conexidade fraca (ignorando
 * a direcao das arestas), ja que "conexo" para digrafos costuma
 * exigir fortemente conexo, tratado como desafio extra. */

int grafoEhConexo(Grafo *g) {
    if (g == NULL || g->V == 0) return 0;

    int *visitado = (int*) calloc(g->V, sizeof(int));
    if (visitado == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para checagem de conexidade.\n");
        return 0;
    }

    if (!g->direcionado) {
        dfsMarcarConexo(g, 0, visitado);
    } else {

        /* Monta uma versao "nao-direcionada" temporaria apenas em memoria
         * de visitados, considerando tambem arestas reversas. */

        int *pilha = (int*) malloc(g->V * sizeof(int));
        int topo = 0;
        pilha[topo++] = 0;
        visitado[0] = 1;
        while (topo > 0) {
            int v = pilha[--topo];
            for (No *aux = g->lista[v]; aux != NULL; aux = aux->prox) {
                if (!visitado[aux->destino]) {
                    visitado[aux->destino] = 1;
                    pilha[topo++] = aux->destino;
                }
            }

            /* considera tambem arestas na direcao reversa (weak connectivity) */

            for (int u = 0; u < g->V; u++) {
                for (No *aux = g->lista[u]; aux != NULL; aux = aux->prox) {
                    if (aux->destino == v && !visitado[u]) {
                        visitado[u] = 1;
                        pilha[topo++] = u;
                    }
                }
            }
        }
        free(pilha);
    }

    int conexo = 1;
    for (int i = 0; i < g->V; i++) {
        if (!visitado[i]) {
            conexo = 0;
            break;
        }
    }

    free(visitado);
    return conexo;
}

int grafoTemCiclo(Grafo *g) {
    if (g == NULL || g->V == 0) return 0;

    int temCiclo = 0;
    int *estado = (int*) calloc(g->V, sizeof(int));
    if (estado == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para checagem de ciclo.\n");
        return 0;
    }

    if (g->direcionado) {
        for (int v = 0; v < g->V && !temCiclo; v++) {
            if (estado[v] == 0) {
                if (dfsCicloDirecionadoUtil(g, v, estado)) {
                    temCiclo = 1;
                }
            }
        }
    } else {
        for (int v = 0; v < g->V && !temCiclo; v++) {
            if (!estado[v]) {
                if (dfsCicloNaoDirecionado(g, v, -1, estado)) {
                    temCiclo = 1;
                }
            }
        }
    }

    free(estado);
    return temCiclo;
}

float densidadeGrafo(Grafo *g) {
    if (g == NULL || g->V <= 1) return 0.0f;

    float maxArestas = (float)g->V * (g->V - 1);
    if (!g->direcionado) {
        maxArestas /= 2.0f;
    }
    return (float) g->A / maxArestas;
}

void mostrarEstatisticas(Grafo *g) {
    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return;
    }

    printf("\n=== ESTATISTICAS DO GRAFO ===\n");
    printf("Vertices: %d\n", g->V);
    printf("Arestas: %d\n", g->A);
    printf("Direcionado: %s\n", g->direcionado ? "Sim" : "Nao");

    printf("\nGrau de cada vertice:\n");
    for (int v = 0; v < g->V; v++) {
        if (g->direcionado) {
            int saida = grauVertice(g, v);
            int entrada = grauEntradaVertice(g, v);
            printf("  Vertice %d -> saida: %d | entrada: %d | total: %d\n",
                   v, saida, entrada, saida + entrada);
        } else {
            printf("  Vertice %d -> grau: %d\n", v, grauVertice(g, v));
        }
    }

    printf("\nConexo: %s\n", grafoEhConexo(g) ? "Sim" : "Nao");
    printf("Contem ciclo: %s\n", grafoTemCiclo(g) ? "Sim" : "Nao");
    printf("Densidade: %.4f\n", densidadeGrafo(g));
}

