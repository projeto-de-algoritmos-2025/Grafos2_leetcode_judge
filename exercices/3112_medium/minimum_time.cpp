#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Solution {
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }

        vector<int> dist(n, INT_MAX);
        dist[0] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, 0);

        while (!pq.empty()) {
            auto [time, u] = pq.top(); pq.pop();
            if (time >= disappear[u]) continue;

            for (auto& [v, w] : graph[u]) {
                int new_time = time + w;
                if (new_time < dist[v] && new_time < disappear[v]) {
                    dist[v] = new_time;
                    pq.emplace(new_time, v);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (dist[i] == INT_MAX) dist[i] = -1;
        }

        return dist;
    }
};