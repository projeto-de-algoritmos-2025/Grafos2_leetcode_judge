# [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/description/)

Dada a propriedade `root` de uma árvore binária, retorne a soma máxima de qualquer caminho não vazio.

# Lógica da Solução 

O código utiliza o algoritmo de Kruskal com estrutura de união e busca (DSU) para calcular o peso da árvore geradora mínima (MST) original e, em seguida, verifica cada aresta: se removê-la aumenta o peso da MST, ela é considerada crítica; se forçá-la na MST não altera o peso, ela é pseudo-crítica. A solução retorna os índices dessas arestas separadamente.

# Submissão

![alt text](/exercices/assets/ex_1489.jpg)

# [Código](./critical-pseudo-critical-edges.cpp)