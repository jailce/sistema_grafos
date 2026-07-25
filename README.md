# Sistema de Grafos - AED2

Este repositório contém a implementação do Trabalho Prático da disciplina de Algoritmos e Estruturas de Dados 2 (AED2) da UFU/FACOM/BCC. 

O objetivo do projeto é desenvolver um sistema completo, em linguagem C (padrão C99), para a manipulação de grafos utilizando alocação dinâmica e listas de adjacência. O sistema lê grafos a partir de arquivos de texto, executa diversos algoritmos clássicos e apresenta os resultados através de um menu interativo.
 
## Estrutura do Repositorio
sistema-de-grafos-aed2/
├── Makefile                # Script de compilação (facilita para você juntar tudo)
├── README.md               # Documentação que geramos (ajuda no relatório)
├── grafo.h                 # O coração: Estruturas 'No' e 'Grafo' e assinaturas de funções
├── basico.c                # Parte 1: Leitura, construção e estatísticas (Opções 1, 2 e 8)
├── buscas.c                # Parte 2: Buscas DFS e BFS (Opções 3 e 4)
├── arvores_dags.c          # Parte 3: Ordenação Topológica e Prim (Opções 5 e 6)
├── dijkstra.c              # Parte 4 (Sua): Algoritmo de Dijkstra
├── main.c                  # Parte 4 (Sua): O Menu Interativo e a função main()
├── grafo1.txt              # Arquivo de teste exigido: Grafo não-direcionado simples [1]
├── grafo2.txt              # Arquivo de teste exigido: DAG para ordenação topológica [1]
├── grafo3.txt              # Arquivo de teste exigido: Grafo com ciclo [1]
└── grafo4.txt              # Arquivo de teste exigido: Grafo ponderado para Dijkstra [1]
## 🛠️ Estruturas de Dados
O sistema utiliza as seguintes estruturas base para a representação do grafo na memória:
- **Nó:** Armazena o vértice de destino, o peso da aresta e um ponteiro para o próximo nó.
- **Grafo:** Armazena o número de vértices (V), número de arestas (A) e um vetor de ponteiros para a lista de adjacência.

## 🚀 Funcionalidades e Algoritmos (Menu Interativo)
O sistema possui um menu principal `=== SISTEMA DE GRAFOS ===` com as seguintes opções:

1. **Carregar grafo de arquivo:** Leitura no formato "Origem Destino Peso" e inserção ordenada.
2. **Mostrar grafo:** Exibição estruturada da lista de adjacência.
3. **Busca em Profundidade (DFS):** Versões recursiva e iterativa, mostrando ordem de visitação e componentes conexos.
4. **Busca em Largura (BFS):** Implementação com fila, mostrando ordem e cálculo de distâncias.
5. **Ordenação Topológica:** Focada em grafos direcionados acíclicos (DAGs), com detecção de ciclo.
6. **Árvore Geradora Mínima (Prim):** Exibe as arestas selecionadas e o peso total, tratando grafos desconexos.
7. **Menor Caminho (Dijkstra):** Exibe as distâncias para todos os vértices e reconstrói a rota (ex: `0 -> 2 -> 1`) para um alvo.
8. **Estatísticas do grafo:** Informa número de V/A, graus, se é conexo, se tem ciclos, se é direcionado e a densidade.
9. **Sair**.

## 🗂️ Arquivos de Teste
O sistema foi testado com os arquivos padronizados fornecidos na especificação:
- `grafo1.txt`: Grafo não-direcionado simples.
- `grafo2.txt`: DAG para ordenação topológica.
- `grafo3.txt`: Grafo com ciclo.
- `grafo4.txt`: Grafo ponderado para validação do Dijkstra.

## 💻 Como Compilar e Executar

Este projeto foi modularizado em arquivos `.c` e `.h` para melhor organização do código. Para compilar o projeto, certifique-se de ter o `gcc` e o `make` instalados, e execute os seguintes comandos no terminal:

```bash
# Para compilar o projeto usando o Makefile
make

# Para executar o sistema
./sistema_grafos
```

## 👥 Integrantes e Divisão de Tarefas
Trabalho desenvolvido em grupo para entrega em 26/07/26:

* **Anna Julia:** Leitura de arquivo, criação do grafo, adicionar aresta, mostrar grafo e estatísticas (Opções 1, 2 e 8).
* **Heitor:** Buscas (DFS recursiva/iterativa, componentes conexos e BFS com fila) (Opções 3 e 4).
* **Victor:** Ordenação Topológica, detecção de ciclos e Algoritmo de Prim para AGM (Opções 5 e 6).
* **Jailce Fernanda:** Menor Caminho (Dijkstra + reconstrução de rota), Menu Interativo, integração final e estruturação do Makefile (Opção 7 e Integração Geral).

## 🌟 Desafios Extras (Opcional)
*Planejados para implementação visando pontuação extra:*
- [ ] Detecção de Ciclos com DFS.
- [ ] Componentes Fortemente Conexos (Kosaraju ou Tarjan).
- [ ] Caminho Crítico para DAGs.
- [ ] Teste de estresse com grafo de 1000+ vértices.
```

