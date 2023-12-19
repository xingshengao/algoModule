// 例题:https://www.luogu.com.cn/problem/P3381
#include <bits/stdc++.h>

using namespace std;

struct MCMF {
    int n, m, tot, INF, min_cost;
    vector<bool> vis;
    vector<int> lnk, cur, ter, nxt, cap, cost, dis;
    MCMF() {}
    MCMF(int _n, int _m) {  // 初始化, 输入点数和边数
        n = _n + 5;
        m = _m * 2 + 5;
        tot = 1;
        INF = INT_MAX;
        min_cost = 0;
        vis.resize(n);
        lnk.resize(n);
        cur.resize(n);
        ter.resize(m);
        nxt.resize(m);
        cap.resize(m);
        cost.resize(m);
        dis.resize(n);
    }
        
    void add(int u, int v, int w, int c) {
        ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, cap[tot] = w, cost[tot] = c;
    }
    
    void addedge(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
    
    bool spfa(int s, int t) {
        fill(dis.begin(), dis.end(), INF);
        cur = lnk;
        queue<int> q;
        q.push(s), dis[s] = 0, vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop(), vis[u] = 0;
            for (int i = lnk[u]; i; i = nxt[i]) {
                int v = ter[i];
                if (cap[i] && dis[v] > dis[u] + cost[i]) {
                    dis[v] = dis[u] + cost[i];
                    if (!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        return dis[t] != INF;
    }
    
    int dfs(int u, int t, int flow) {
        if (u == t) return flow;
        vis[u] = 1;
        int ans = 0;
        for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
            int v = ter[i];
            if (!vis[v] && cap[i] && dis[v] == dis[u] + cost[i]) {
                int x = dfs(v, t, min(cap[i], flow - ans));
                if (x) min_cost += x * cost[i], cap[i] -= x, cap[i ^ 1] += x, ans += x;
            }
        }
        vis[u] = 0;
        return ans;
    }
    
    int mcmf(int s, int t) {
        int ans = 0;
        while (spfa(s, t)) {
            int x;
            while ((x = dfs(s, t, INF))) ans += x;
        }
        return ans;
    }
};

 
int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MCMF S(n, m);
    while (m--) {
        int u, v, w, c;
        // 输入起点，终点，流量限制，单位流量费用
        cin >> u >> v >> w >> c;
        S.addedge(u, v, w, c);
    }
    int max_flow = S.mcmf(s, t);
    cout << max_flow << ' ' << S.min_cost << endl;
    return 0;
}
