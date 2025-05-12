class Solution {
    public:
        vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
            int originalWeight = MSTWeight(n, edges);
            vector<int> critical, pseudo;
    
            for (int i = 0; i < (int)edges.size(); i++) {
                if (MSTWeight(n, edges, i) > originalWeight) {
                    critical.push_back(i);
                } else if (MSTWeight(n, edges, -1, i) == originalWeight) {
                    pseudo.push_back(i);
                }
            }
    
            return {critical, pseudo};
        }
    
    private:
        struct DSU {
            vector<int> parent;
            vector<int> rank;
    
            DSU(int n) : parent(n), rank(n, 0) {
                for(int i = 0; i < n; i++) parent[i] = i;
            }
    
            int find(int x) {
                if (parent[x] != x) parent[x] = find(parent[x]);
                return parent[x];
            }
    
            bool unite(int x, int y) {
                int rx = find(x), ry = find(y);
                if (rx == ry) return false;
                if (rank[rx] < rank[ry]) parent[rx] = ry;
                else if (rank[rx] > rank[ry]) parent[ry] = rx;
                else {
                    parent[ry] = rx;
                    rank[rx]++;
                }
                return true;
            }
        };
    
        int MSTWeight(int n, const vector<vector<int>>& edges, int skipEdge = -1, int includeEdge = -1) {
            DSU dsu(n);
            int weight = 0, count = 0;
    
            if (includeEdge != -1) {
                const auto& e = edges[includeEdge];
                if (dsu.unite(e[0], e[1])) {
                    weight += e[2];
                    count++;
                } else {
                    return INT_MAX;
                }
            }
    
            vector<pair<int,int>> sorted;
            for (int i = 0; i < (int)edges.size(); i++) {
                if (i == skipEdge) continue;
                sorted.emplace_back(edges[i][2], i);
            }
            sort(sorted.begin(), sorted.end());
    
            for (auto [w, i] : sorted) {
                const auto& e = edges[i];
                if (dsu.unite(e[0], e[1])) {
                    weight += e[2];
                    count++;
                }
            }
    
            return count == n - 1 ? weight : INT_MAX;
        }
    };