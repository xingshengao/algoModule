// https://www.luogu.com.cn/problem/P3377
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

// 一开始有 n 个小根堆，每个堆包含且仅包含一个数。接下来需要支持两种操作：

// 1 x y: 将第 x 个数和第 y 个数所在的小根堆合并（若第 x 或第 y 个数已经被删除或第 x 和第 y 个数在用一个堆内，则无视此操作）。

// 2 x: 输出第 x 个数所在的堆最小数，并将这个最小数删除（若有多个最小数，优先删除先输入的；若第 x 个数已经被删除，则输出 -1 并无视删除操作）。

struct Heap {

    struct Q {  // 堆中元素结构体
        int val, idx;
        bool operator < (const Q& a) const {
            if (val != a.val) return val > a.val;
            return idx > a.idx;
        };
    };

    vector<bool> del;
    vector<int> fa;
    vector<priority_queue<Q>> q;

    Heap() {}
    Heap(int n) {   // 输入初始堆的个数
        fa = vector<int> (n + 5);
        del = vector<bool> (n + 5);
        q = vector<priority_queue<Q>> (n + 5);
        for (int i = 0; i < n + 5; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    void merge(int x, int y) {  // 合并下标x和下标y所在的堆
        if (del[x] || del[y]) return;
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (q[x].size() < q[y].size()) swap(x, y);
        fa[y] = x;
        while (q[y].size()) {
            q[x].push(q[y].top());
            q[y].pop();
        }
    }

    int pop(int x) {    // 删除下标x所在堆的堆顶, 并返回
        x = find(x);
        Q t = q[x].top();
        q[x].pop();
        del[t.idx] = 1;
        return t.val;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m;
    cin >> n >> m;
    Heap H(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        H.q[i].push({a, i});
    }
    while (m--) {
        int op, x, y;
        cin >> op;
        if (op == 1) {
            cin >> x >> y;
            H.merge(x, y);
        } else {
            cin >> x;
            if (H.del[x]) {
                cout << -1 << endl;
            } else {
                cout << H.pop(x) << endl;
            }
        }
    }
    return 0;
}
