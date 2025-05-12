class Solution {
    public:
        // Função principal que encontra as arestas críticas e pseudo-críticas
        vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
            // Calcula o peso do MST original (sem remover ou incluir arestas)
            int originalWeight = MSTWeight(n, edges);
            vector<int> critical, pseudo;  // Vetores para armazenar as arestas críticas e pseudo-críticas
    
            // Itera por todas as arestas para verificar quais são críticas ou pseudo-críticas
            for (int i = 0; i < (int)edges.size(); i++) {
                // Verifica se a aresta é crítica, ou seja, se sua remoção aumenta o peso do MST
                if (MSTWeight(n, edges, i) > originalWeight) {
                    critical.push_back(i);  // Aresta crítica
                } 
                // Verifica se a aresta é pseudo-crítica, ou seja, se sua inclusão mantém o peso do MST original
                else if (MSTWeight(n, edges, -1, i) == originalWeight) {
                    pseudo.push_back(i);  // Aresta pseudo-crítica
                }
            }
    
            // Retorna as listas de arestas críticas e pseudo-críticas
            return {critical, pseudo};
        }
    
    private:
        // Estrutura DSU (Disjoint Set Union) para manipular conjuntos disjuntos
        struct DSU {
            vector<int> parent;  // Vetor que guarda os pais dos elementos
            vector<int> rank;    // Vetor que guarda a altura (rank) das árvores
    
            // Construtor que inicializa os pais e ranks
            DSU(int n) : parent(n), rank(n, 0) {
                for(int i = 0; i < n; i++) parent[i] = i;  // Cada elemento é seu próprio pai inicialmente
            }
    
            // Função para encontrar o representante (root) de um elemento
            int find(int x) {
                if (parent[x] != x) parent[x] = find(parent[x]);  // Compressão de caminho
                return parent[x];
            }
    
            // Função para unir dois elementos em um único conjunto
            bool unite(int x, int y) {
                int rx = find(x), ry = find(y);  // Encontrar os representantes de x e y
                if (rx == ry) return false;  // Se já estão no mesmo conjunto, não faz nada
                // Une os conjuntos pelo rank para manter a árvore balanceada
                if (rank[rx] < rank[ry]) parent[rx] = ry;
                else if (rank[rx] > rank[ry]) parent[ry] = rx;
                else {
                    parent[ry] = rx;  // Se os ranks forem iguais, escolhe arbitrariamente
                    rank[rx]++;  // Aumenta o rank do novo representante
                }
                return true;
            }
        };
    
        // Função que calcula o peso do MST com a opção de pular ou incluir uma aresta específica
        int MSTWeight(int n, const vector<vector<int>>& edges, int skipEdge = -1, int includeEdge = -1) {
            DSU dsu(n);  // Inicializa a estrutura DSU para n elementos
            int weight = 0, count = 0;  // Variáveis para armazenar o peso do MST e o número de arestas

            // Se a aresta incluir for fornecida, tenta incluir ela no MST
            if (includeEdge != -1) {
                const auto& e = edges[includeEdge];
                if (dsu.unite(e[0], e[1])) {  // Tenta unir os conjuntos dos vértices da aresta
                    weight += e[2];  // Se conseguiu unir, adiciona o peso da aresta
                    count++;  // Incrementa o contador de arestas
                } else {
                    return INT_MAX;  // Se não conseguiu unir, retorna um valor grande (indicando falha)
                }
            }
    
            // Cria um vetor de pares (peso, índice da aresta) para ordenar as arestas por peso
            vector<pair<int,int>> sorted;
            for (int i = 0; i < (int)edges.size(); i++) {
                if (i == skipEdge) continue;  // Pula a aresta indicada para ser ignorada
                sorted.emplace_back(edges[i][2], i);  // Adiciona a aresta ao vetor com seu peso
            }
            sort(sorted.begin(), sorted.end());  // Ordena as arestas pelo peso
    
            // Processa as arestas ordenadas para construir o MST
            for (auto [w, i] : sorted) {
                const auto& e = edges[i];
                if (dsu.unite(e[0], e[1])) {  // Se a aresta conecta dois conjuntos, inclui ela no MST
                    weight += e[2];  // Adiciona o peso da aresta
                    count++;  // Incrementa o contador de arestas
                }
            }
    
            // Se o MST tem n-1 arestas, retorna o peso, caso contrário, retorna INT_MAX (indica que não é possível formar um MST)
            return count == n - 1 ? weight : INT_MAX;
        }
};
