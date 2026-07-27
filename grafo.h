#ifndef GRAFO_H
#define GRAFO_H

typedef struct No {
  int destino;
  int peso;
  struct No *prox;
} No;

typedef struct {
  int V;           // Número de vértices
  int A;           // Número de arestas
  No **lista;      // Lista de adjacência
  int direcionado; // 1 se direcionado, 0 se não
} Grafo;

// ===== Ana Julia: grafo.c =====
Grafo *criarGrafo(int V, int direcionado);
void adicionarAresta(Grafo *g, int origem, int destino, int peso);
Grafo *lerGrafoDeArquivo(const char *nomeArquivo, int direcionado);
void mostrarGrafo(Grafo *g);
void liberarGrafo(Grafo *g);

// Estatísticas (opção 8)
void mostrarEstatisticas(Grafo *g);
int grauVertice(Grafo *g, int v);
int grafoEhConexo(Grafo *g);
int grafoTemCiclo(Grafo *g);
float densidadeGrafo(Grafo *g);

// ===== Heitor: busca.c =====
void dfsRecursiva(Grafo *g, int origem, int *visitado);
void dfsIterativa(Grafo *g, int origem);
int componentesConexos(Grafo *g); // retorna a quantidade e imprime cada um
void bfs(Grafo *g, int origem);
int *bfsDistancias(Grafo *g, int origem); // retorna vetor de distâncias

// ===== Victor: topologica.c e prim.c =====
int ordenacaoTopologica(Grafo *g,int *ordem); // retorna 0 se tem ciclo, 1 se ok
int detectaCicloDirecionado(Grafo *g);

void prim(Grafo *g); // trata desconexos internamente, imprime arestas + peso total

// ===== Jailce: dijkstra.c e main.c =====
void dijkstra(Grafo *g, int origem, int **dist, int **anterior);
void imprimirCaminho(int *anterior, int origem, int destino);
void executarDijkstra(Grafo *g, int origem, int destinoAlvo); // junta dijkstra+caminho pro menu

void exibirMenu(void);
int main(void);

#endif
