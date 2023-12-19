// https://www.luogu.com.cn/problem/P7771
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 欧拉路径判定(是否存在)：
// 有向图欧拉路径 : 图中恰好存在1个点出度比入度多1(这个点即为起点S), 1个点入度比出度多1(这个点即为终点T), 其余节点出度=入度
// 有向图欧拉回路 ：所有点的入度=出度(起点S和终点T可以为任意点)
// 无向图欧拉路径 : 图中恰好存在2个点的度数是奇数, 其余节点的度数为偶数, 这两个度数为奇数的点即为欧拉路径的起点S和终点T
// 无向图欧拉回路 ：所有点的度数都是偶数(起点S和终点T可以为任意点)

int n, m;
vector<int> indeg, outdeg, idx;
vector<vector<int>> g;
vector<int> st;

void dfs(int now) {
    for (int i = idx[now]; i < g[now].size(); i = idx[now]) {
        idx[now] = i + 1;
        dfs(g[now][i]);
    }
    st.push_back(now);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    cin >> n >> m;
    indeg = vector<int> (n + 1);
    outdeg = vector<int> (n + 1);
    idx = vector<int> (n + 1);
    g = vector<vector<int>> (n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        outdeg[a]++;
        indeg[b]++;
    }
    for (int i = 1; i <= n; i++) {
        sort(g[i].begin(), g[i].end());
    }
    int cnt1 = 0, cnt2 = 0, start = 1;
    bool flag = 1;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] != outdeg[i]) flag = 0;
        if (outdeg[i] == indeg[i] + 1) cnt1++, start = i;
        if (outdeg[i] == indeg[i] - 1) cnt2++;
    }
    // 判无解
    if (flag == 0 && (cnt1 != 1 || cnt2 != 1)) {
        cout << "No" << endl;
        return 0;
    }
    dfs(start);
    while (st.size()) {
        cout << st.back() << ' ';
        st.pop_back();
    }
    cout << endl;
    return 0;
}
