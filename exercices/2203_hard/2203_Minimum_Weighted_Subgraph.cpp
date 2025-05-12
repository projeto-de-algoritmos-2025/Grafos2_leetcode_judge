// Autor: Leonardo Fernandes - 200067036
// Leetcode Hard :: 2203. Minimum Weighted Subgraph With the Required Paths
// https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/description/

#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
    public:
        /*
            Implementação do Algoritmo Dijkstra
            n : quantidade de vertices/nós
            adj: grafo invertido convertido em lista de adjacencia
            start: nó/vertice de partida
        */
        vector<long long> dijkstra(int n, const vector<vector<pair<int, int>>>& adj, int start) {
            vector<long long> dist(n, LLONG_MAX);  // Inicializa todas as distâncias como infinito
            dist[start] = 0;  // A distância do nó inicial para ele mesmo é 0

            // Min-heap: armazena pares (distância, nó), ordenados pela menor distância
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            pq.push({0, start});

            while (!pq.empty()) {
                long long current_dist = pq.top().first;  // Pega a menor distância atual
                int u = pq.top().second;  // Pega o nó correspondente
                pq.pop();

                // Se já encontramos um caminho melhor para 'u', ignoramos
                if (current_dist > dist[u]) continue;

                // Para cada vizinho de 'u'
                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;  // Nó vizinho
                    int w = neighbor.second; // Peso da aresta u->v

                    // Relaxamento: se encontrarmos um caminho mais curto para 'v', atualizamos
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        pq.push({dist[v], v});  // Adiciona à fila para processar depois
                    }
                }
            }
            return dist;  // Retorna o vetor de distâncias mínimas a partir de 'start'
        }

        long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
            // Construção dos grafos original (adj) e invertido (reversed_adj)
            vector<vector<pair<int, int>>> adj(n), reversed_adj(n);
            for (const auto& edge : edges) {
                int u = edge[0]; // Nó de partida
                int v = edge[1]; // Nó de chegada
                int w = edge[2]; // Peso
                adj[u].emplace_back(v, w);           // Grafo original: u -> v com peso w
                reversed_adj[v].emplace_back(u, w);  // Grafo invertido: v -> u com peso w
            }

            // Cálculo das distâncias mínimas usando Dijkstra
            vector<long long> dist_src1 = dijkstra(n, adj, src1);  // De src1 para todos
            vector<long long> dist_src2 = dijkstra(n, adj, src2);  // De src2 para todos
            vector<long long> dist_dest = dijkstra(n, reversed_adj, dest);  // De dest para todos (no grafo invertido)

            // Encontrar o peso mínimo do subgrafo
            long long min_weight = LLONG_MAX;

            // Para cada nó
            for (int x = 0; x < n; ++x) {
                // Se o nó x alcançar src1, src2 e dest
                if (dist_src1[x] != LLONG_MAX && dist_src2[x] != LLONG_MAX && dist_dest[x] != LLONG_MAX) {
                    min_weight = min(min_weight, dist_src1[x] + dist_src2[x] + dist_dest[x]);
                }
            }

            return (min_weight == LLONG_MAX) ? -1 : min_weight;
        }
};
