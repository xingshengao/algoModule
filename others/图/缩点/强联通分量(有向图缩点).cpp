// https://www.luogu.com.cn/problem/P3387
#include <bits/stdc++.h>

using namespace std;

struct Scc {

    int n;              // 点的数量
    int timestamp;      // 时间戳
    int sccCnt;         // 强连通分量个数
    vector<int> dfn;    // dfn[i]表示深度优先遍历时结点i被访问的时间
    vector<int> low;    // low[i]表示i的子树能够回溯到的最早时间
    vector<int> st;     // 用于计算强连通分量的栈
    vector<bool> inSt;  // inSt[i]为true表示结点i在栈中
    vector<int> id;     // id[i]表示结点i在编号为id[i]强连通分量中
    vector<int> size;   // size[i]表示结点i所在强连通分量里所含结点个数
    vector<vector<int>> g;  // 没有缩点前的有向图
    vector<vector<int>> ng; // 缩点后的有向无环图

    Scc() {}
    Scc(int n) {
        this->n = n;
        this->timestamp = 0;
        this->sccCnt = 0;
        dfn.resize(n + 5);
        low.resize(n + 5);
        st.resize(n + 5);
        inSt.resize(n + 5);
        id.resize(n + 5);
        size.resize(n + 5);
        g.resize(n + 5);
        ng.resize(n + 5);
    }

    void add(int a, int b) {    // 添加一条从a到b的有向边
        g[a].push_back(b);
    }

    void tarjan(int now) {

        dfn[now] = low[now] = ++timestamp;
        st.push_back(now);
        inSt[now] = true;

        for (int i = 0; i < g[now].size(); i++) {
            int nxt = g[now][i];
            if (!dfn[nxt]) {
                tarjan(nxt);
                low[now] = min(low[now], low[nxt]);
            } else if (inSt[nxt]) {
                low[now] = min(low[now], dfn[nxt]);
            }
        }

        if (dfn[now] == low[now]) {
            sccCnt++;
            int v;
            do {
                v = st.back();
                inSt[v] = false;
                st.pop_back();
                id[v] = sccCnt;
                size[sccCnt]++;
            } while (now != v);
        }
    }

    void getGccGraph() {    // 获取缩点后的有向无环图

        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i);
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                int nxt = g[i][j];
                int idNow = id[i], idNxt = id[nxt];
                if (idNow != idNxt) {
                    ng[idNow].push_back(idNxt);
                }
            }
        }
    }
};

int res = 0;
vector<int> sccw, dp;
int dfs(int now, Scc& s) {
    if (dp[now]) return dp[now];
    int nowres = sccw[now];
    int t = 0;
    for (int i = 0; i < s.ng[now].size(); i++) {
        int nxt = s.ng[now][i];
        t = max(t, dfs(nxt, s));
    }
    dp[now] = nowres + t;
    res = max(res, dp[now]);
    return dp[now];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    Scc S(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        S.add(a, b);
    }
    S.getGccGraph();

    sccw.resize(n + 1);
    dp.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        sccw[S.id[i]] += w[i];
    }
    for (int i = 1; i <= S.sccCnt; i++) {
        dfs(i, S);
    }
    cout << res << endl;
    return 0;
}
