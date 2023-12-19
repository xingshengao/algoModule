// https://www.luogu.com.cn/problem/P4782
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct TwoSat {

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

    TwoSat() {}
    TwoSat(int n) {
        this->timestamp = 0;
        this->sccCnt = 0;
        dfn.resize(2 * n + 5);
        low.resize(2 * n + 5);
        st.resize(2 * n + 5);
        inSt.resize(2 * n + 5);
        id.resize(2 * n + 5);
        size.resize(2 * n + 5);
        g.resize(2 * n + 5);
        ng.resize(2 * n + 5);
        this->n = n;
    }

    // 如果a一定为1, 可以加一条 -a -> a 的边
    void add(int a, int va, int b, int vb) {    // 添加条件, 第a个数为va或第b个数为vb
        // a 表示 a 为 1, a + n 表示 a 为 0
        if (va == 0 && vb == 0) {        // "如果第a个数为0或第b个数为0"至少满足其一 
            g[a].push_back(b + n);       // a = 1 则 b = 0
            g[b].push_back(a + n);       // b = 1 则 a = 0 
        } else if (va == 0 && vb == 1) { // "如果第a个数为0或第b个数为1"至少满足其一 
            g[a].push_back(b);           // a = 1 则 b = 1
            g[b + n].push_back(a + n);   // b = 0 则 a = 0
        } else if (va == 1 && vb == 0) { // "如果第a个数为1或第b个数为0"至少满足其一 
            g[a + n].push_back(b + n);   // a = 0 则 b = 0 
            g[b].push_back(a);           // b = 1 则 a = 1 
        } else if (va == 1 && vb == 1) { // "如果第a个数为1或第b个数为1"至少满足其一        
            g[a + n].push_back(b);       // a = 0 则 b = 1
            g[b + n].push_back(a);       // b = 0 则 a = 1
        }
    }

    // 找环
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

    // 输出一组可行解
    bool twoSat() {
        for (int i = 1; i <= 2 * n; i++) {  // 对每个变量的每种取值进行tarjan
            if (!dfn[i]) {
                tarjan(i);
            }
        }
        for (int i = 1; i <= n; i++) {  // 判断无解的情况
            if (id[i] == id[i + n]) {   // 同一变量的两种取值在同一强联通分量里,说明无解 
                cout << "IMPOSSIBLE" << endl;
                return false;
            }
        }
        cout << "POSSIBLE" << endl;     // 有解的情况
        for (int i = 1; i <= n; i++) {
            if (id[i] < id[i + n]) {    // 强联通分量编号越小 -> 拓扑序越大 -> 越优
                cout << 1 << ' ';
            } else {
                cout << 0 << ' ';
            }
        }
        return true;
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    TwoSat T(n);
    while (m--) {
        int a, va, b, vb;
        cin >> a >> va >> b >> vb;
        T.add(a, va, b, vb);
    }
    T.twoSat();
}