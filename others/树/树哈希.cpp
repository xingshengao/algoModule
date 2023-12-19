// https://uoj.ac/problem/763
#include <bits/stdc++.h>

using namespace std;

struct treeHash {
    #define ull unsigned long long 
    unordered_map<int, vector<int>> g;  // 树
    unordered_map<int, ull> hash;   // key = 根节点的值，value = 该子树哈希值

    treeHash() {}

    void add(int a, int b) {    // 添加一条无向边
        g[a].push_back(b);
        g[b].push_back(a);
    }

    ull calc(ull x) {  // 哈希函数
        return x * x * x + 7;
    }

    void dfs(int now, int fa) { // 获取哈希值
        hash[now] = 1;
        for (int i = 0; i < g[now].size(); i++) {
            int nxt = g[now][i];
            if (nxt == fa) continue;
            dfs(nxt, now);
            hash[now] += hash[nxt];
        }
        hash[now] = calc(hash[now]);
    }

};

signed main() {
    int n;
    cin >> n;
    treeHash H;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        H.add(a, b);
    }
    H.dfs(1, -1);
    set<ull> s;
    for (auto [x, u] : H.hash) {
        s.insert(u);
    }
    cout << s.size() << endl;
}