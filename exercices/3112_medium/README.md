# [3112. Minimum Time to Visit Disappearing Nodes](https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/description/)

Calcule o menor tempo para alcançar cada nó a partir do nó 0 antes que ele desapareça.

# Lógica da Solução 

Para resolver o problema, usamos o algoritmo de Dijkstra para encontrar o menor tempo de chegada a cada nó a partir do nó 0. Durante a busca, só continuamos explorando um caminho se ainda for possível chegar ao nó antes dele desaparecer, conforme o vetor disappear.

# Submissão

![alt text](/exercices/assets/ex_3112.jpg)

# [Código](./minimum_time.cpp)
