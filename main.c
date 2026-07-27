#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
/*
Este arquivo integra o sistema de grafos, fornecendo uma interface de menu 
para o usuário interagir com as funcionalidades do grafo, como carregamento de arquivo, exibição, buscas (DFS e BFS), ordenação topológica, árvore geradora mínima (Prim), menor caminho (Dijkstra) e estatísticas do grafo.
*/
static void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int carregarGrafo(Grafo **g) {
    char arquivo[256];
    int direcionado;

    printf("Nome do arquivo: ");
    if (scanf("%255s", arquivo) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    printf("Grafo direcionado? (1-sim, 0-nao): ");
    if (scanf("%d", &direcionado) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    if (*g != NULL) {
        liberarGrafo(*g);
        *g = NULL;
    }

    *g = lerGrafoDeArquivo(arquivo, direcionado ? 1 : 0);
    return 1;
}

static int executarDFS(Grafo *g) {
    int origem, modo;

    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return 0;
    }

    printf("Vertice de origem: ");
    if (scanf("%d", &origem) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    printf("1. DFS recursiva\n2. DFS iterativa\nOpcao: ");
    if (scanf("%d", &modo) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    if (origem < 0 || origem >= g->V) {
        printf("Vertice invalido.\n");
        return 0;
    }

    printf("DFS: ");
    if (modo == 1) {
        int *visitado = (int*) calloc(g->V, sizeof(int));
        if (visitado == NULL) {
            printf("Erro de memoria.\n");
            return 0;
        }
        dfsRecursiva(g, origem, visitado);
        free(visitado);
    } else {
        dfsIterativa(g, origem);
    }
    printf("\n");
    return 1;
}

static int executarBFS(Grafo *g) {
    int origem;

    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return 0;
    }

    printf("Vertice de origem: ");
    if (scanf("%d", &origem) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    if (origem < 0 || origem >= g->V) {
        printf("Vertice invalido.\n");
        return 0;
    }

    printf("BFS: ");
    bfs(g, origem);
    printf("\n");
    return 1;
}

static int executarTopologica(Grafo *g) {
    int *ordem;

    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return 0;
    }
    if (!g->direcionado) {
        printf("Ordenacao topologica exige grafo direcionado.\n");
        return 0;
    }
    if (detectaCicloDirecionado(g)) {
        printf("O grafo contem ciclo, nao e possivel ordenar topologicamente.\n");
        return 0;
    }

    ordem = (int*) malloc(sizeof(int) * g->V);
    if (ordem == NULL) {
        printf("Erro de memoria.\n");
        return 0;
    }

    if (ordenacaoTopologica(g, ordem)) {
        printf("\n=== ORDENACAO TOPOLOGICA ===\nOrdem: ");
        for (int i = 0; i < g->V; i++) {
            printf("%d", ordem[i]);
            if (i < g->V - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("Nao foi possivel obter uma ordenacao topologica.\n");
    }

    free(ordem);
    return 1;
}

static int executarDijkstraMenu(Grafo *g) {
    int origem, destino;

    if (g == NULL) {
        printf("Nenhum grafo carregado.\n");
        return 0;
    }

    printf("Vertice de origem: ");
    if (scanf("%d", &origem) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    printf("Vertice destino alvo: ");
    if (scanf("%d", &destino) != 1) {
        printf("Entrada invalida.\n");
        limparEntrada();
        return 0;
    }

    executarDijkstra(g, origem, destino);
    return 1;
}

void exibirMenu(void) {
    printf("\n=== SISTEMA DE GRAFOS ===\n");
    printf("1. Carregar grafo de arquivo\n");
    printf("2. Mostrar grafo (lista de adjacencia)\n");
    printf("3. Busca em Profundidade (DFS)\n");
    printf("4. Busca em Largura (BFS)\n");
    printf("5. Ordenacao Topologica\n");
    printf("6. Arvore Geradora Minima (Prim)\n");
    printf("7. Menor Caminho (Dijkstra)\n");
    printf("8. Estatisticas do grafo\n");
    printf("9. Sair\n");
}
//
int main(void) {
    Grafo *g = NULL;
    int opcao = 0;

    do {
        exibirMenu();
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida.\n");
            limparEntrada();
        } else if (opcao == 1) {
            carregarGrafo(&g);
        } else if (opcao == 2) {
            mostrarGrafo(g);
        } else if (opcao == 3) {
            executarDFS(g);
        } else if (opcao == 4) {
            executarBFS(g);
        } else if (opcao == 5) {
            executarTopologica(g);
        } else if (opcao == 6) {
            prim(g);
        } else if (opcao == 7) {
            executarDijkstraMenu(g);
        } else if (opcao == 8) {
            mostrarEstatisticas(g);
        } else if (opcao == 9) {
            printf("Encerrando...\n");
        } else {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 9);

    liberarGrafo(g);
    return 0;
}
