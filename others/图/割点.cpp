// https://www.luogu.com.cn/problem/P3388
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct CutPoint {

    int cnt, n;
    vector<int> dfsn;   // 记录每个点的时间戳
    vector<int> low;    // 能不经过父亲到达最小的编号
    vector<int> res;    // 存储所有割点
    vector<vector<int>> edges;

    CutPoint() {}
    CutPoint(int n) {
        cnt = 0;
        this->n = n;
        dfsn.resize(n + 5);
        low.resize(n + 5);
        edges.resize(n + 5);
    }

    void add(int a, int b) {    // 添加一条无向边
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    void tarjan(int p, bool root = true) {
        int tot = 0;
        low[p] = dfsn[p] = ++cnt;
        for (auto q : edges[p]) {
            if (!dfsn[q]) {
                tarjan(q, false);
                low[p] = min(low[p], low[q]);
                tot += (low[q] >= dfsn[p]); // 统计满足low[q] >= dfsn[p]的子节点数目
            } else {
                low[p] = min(low[p], dfsn[q]);
            }
        }
        if (tot > root) {// 如果是根，tot需要大于1；否则只需大于0
            res.push_back(p);
        }
    }

    vector<int> GetCutPoint() {
        for (int i = 0; i <= n; i++) {  // Tarjan 图不一定连通
            if (dfsn[i] == 0) {
                tarjan(i);
            }
        }
        return res;
    }
};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cout.tie(0);
	cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    CutPoint C(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        C.add(a, b);
    }
    vector<int> res = C.GetCutPoint();
    sort(res.begin(), res.end());
    cout << res.size() << endl;
    for (int x : res) {
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}
