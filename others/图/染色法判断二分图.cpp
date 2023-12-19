// https://leetcode.cn/problems/is-graph-bipartite/
struct bipartiteGraph {

    
    unordered_map<int, int> color;  // 0表示未染色, 1表示染白色, 2表示染黑色
    unordered_map<int, vector<int>> g;

    bipartiteGraph() {}

    void add(int a, int b) {    // 添加一条a-b的无向边
        g[a].push_back(b);
        g[b].push_back(a);
    }

    bool dfs(int now, int c) {
        color[now] = c;
        for (int i = 0; i < g[now].size(); i++) {
            int nxt = g[now][i];
            if (color[nxt]) {
                if (color[nxt] == c) return false;
            } else if (!dfs(nxt, 3 - c)) {
                return false;
            }
        }
        return true;
    }

    bool isBipartite() {
        for (auto it = g.begin(); it != g.end(); it++) {
            int i = it->first;
            if (color[i] == 0) {
                if (!dfs(i, 1)) return false;
            }
        }
        return true;
    }
};

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        bipartiteGraph B;
        int n = graph.size();
        for (int i = 0; i < n; i++) {
            for (int j : graph[i]) {
                B.add(i, j);
            }
        }
        return B.isBipartite();
    }
};