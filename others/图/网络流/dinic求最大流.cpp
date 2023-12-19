// https://www.luogu.com.cn/problem/P3376
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Dinic {

    struct Edge {
        int from, to, cap, flow;
    
        Edge(int u, int v, int c, int f) : from(u), to(v), cap(c), flow(f) {}
    };

    int n, m, s, t, INF = 0x3f3f3f3f;
    vector<Edge> edges;
    vector<vector<int>> G;
    vector<int> d, cur;
    vector<bool> vis;

    Dinic() {}
    Dinic(int n) {
        G.resize(n + 5);
        d.resize(n + 5);
        cur.resize(n + 5);
        vis.resize(n + 5);
    }
 
    void AddEdge(int from, int to, int cap) {
        edges.push_back(Edge(from, to, cap, 0));
        edges.push_back(Edge(to, from, 0, 0));
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
 
    bool BFS() {
        fill(vis.begin(), vis.end(), 0);
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!Q.empty()) {
            int x = Q.front();
            Q.pop();
            for (int i = 0; i < G[x].size(); i++) {
                Edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow) {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
 
    int DFS(int x, int a) {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++) {
            Edge& e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
 
    int Maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (BFS()) {
            fill(cur.begin(), cur.end(), 0);
            flow += DFS(s, INF);
        }
        return flow;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(15);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    Dinic D(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        D.AddEdge(u, v, w);
    }
    cout << D.Maxflow(s, t) << endl;
    return 0;
}