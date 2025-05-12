# [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/)

O exercício pede para identificar, em um grafo ponderado, quais arestas são críticas (obrigatórias em toda MST) e quais são pseudo-críticas (podem estar em alguma MST). A saída deve ser uma lista com os índices das arestas críticas e pseudo-críticas.

# Lógica da Solução 

O código utiliza o algoritmo de Kruskal com estrutura de união e busca (DSU) para calcular o peso da árvore geradora mínima (MST) original e, em seguida, verifica cada aresta: se removê-la aumenta o peso da MST, ela é considerada crítica; se forçá-la na MST não altera o peso, ela é pseudo-crítica. A solução retorna os índices dessas arestas separadamente.

# Submissão

![alt text](/exercices/assets/ex_1489.jpg)

# [Código](./critical-pseudo-critical-edges.cpp)
