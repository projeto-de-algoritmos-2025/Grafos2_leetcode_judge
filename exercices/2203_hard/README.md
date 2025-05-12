# [2203. Minimum Weighted Subgraph With the Required Paths](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/description/)

No problema em questão lidaremos com cinco paramêtros:
- `n`: diz respeito a quantidade de nós existentes no grafo
- `edges`: se trata de um vetor de vetores que segue a seguinte estrutura, `edges[i] = [partida, destino, peso]`.  
- `src1`, `src2`, `dest`: nós do grafo

Precisamos encontrar o menor peso de um subgrafo que conecte tanto `src1` quanto `src2` ao nó de destino `dest`. Para isso utilizaremos o algoritmo Dijkstra 3 vezes, uma para `src1` e `src2` para todos os outros nós utilizando o grafo convertido para uma lista de adjacência, a terceira utilização será do `dest` para todos os outros nós utilizando o grafo invertido.

Cada execução retornará o vetor de distância mínima a partir do nó escolhido. E a partir disso utilizamos um laço que verifica todos os `n` nós e seleciona o menor caminho se o nó `x` verificado alcança `src1`, `src2` e `dist`.

# Submissão

![submissão](/assets/2203_submit.jpeg)

# [Código](./2203_Minimum_Weighted_Subgraph.cpp)