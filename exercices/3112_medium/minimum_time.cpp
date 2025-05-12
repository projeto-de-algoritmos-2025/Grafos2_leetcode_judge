#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        // Criando um grafo representado como uma lista de adjacência, onde cada nó tem uma lista de pares (vértice adjacente, peso da aresta)
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        // Vetor dist que armazena o menor tempo para alcançar cada vértice a partir do vértice 0
        // Inicializamos com INT_MAX para representar que ainda não encontramos um caminho para o vértice
        vector<int> dist(n, INT_MAX);
        dist[0] = 0; // O tempo para alcançar o vértice 0 é 0

        // Fila de prioridade (min-heap) para processar os vértices com o menor tempo acumulado
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, 0); // Adicionamos o vértice 0 com tempo 0 à fila de prioridade

        // Algoritmo de Dijkstra modificado para garantir que não ultrapassamos o tempo limite de "desaparecimento"
        while (!pq.empty()) {
            auto [time, u] = pq.top(); pq.pop();
            
            // 💡 Essa linha é crítica para otimização
            // Se já encontramos um tempo melhor para o vértice u ou se o tempo já ultrapassou o limite de desaparecimento, ignoramos
            if (time > dist[u] || time >= disappear[u]) continue;

            // Iterando sobre os vizinhos do vértice u
            for (auto& [v, w] : graph[u]) {
                // Calculamos o novo tempo para o vértice v
                int new_time = time + w;
                // Se encontramos um caminho mais rápido para v e ainda está dentro do limite de desaparecimento, atualizamos a distância
                if (new_time < dist[v] && new_time < disappear[v]) {
                    dist[v] = new_time;
                    pq.emplace(new_time, v); // Adicionamos o vértice v à fila de prioridade com o novo tempo
                }
            }
        }

        // Se algum vértice não foi alcançado (distância permanece como INT_MAX), o tempo é -1
        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) dist[i] = -1;
        }

        // Retornamos o vetor de distâncias
        return dist;
    }
};
