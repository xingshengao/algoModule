// https://www.acwing.com/problem/content/description/180/
#include <bits/stdc++.h>

using namespace std;

struct KthPath {

    int n, inf = 2e9;
    vector<int> H;
    vector<vector<vector<int>>> g1, g2;
    
    struct Q {
        int eval, real, pos;
        bool operator < (const Q x) const {
            return eval < x.eval;
        };
    };
    

    KthPath() {}
    KthPath(int n) {
        this->n = n;
        H.resize(n + 5);
        g1.resize(n + 5);
        g2.resize(n + 5);
    }

    void add(int a, int b, int c) { // 添加一条从a->b的有向边
        g1[b].push_back({a, c});
        g2[a].push_back({b, c});
    }

    int GetKthPath(int start, int end, int k) { // 求start->end的第k短路径长度
        if (start == end) k++;
        fill(H.begin(), H.end(), inf);
        set<pair<int, int>> s;
        s.insert({0, end});
        vector<bool> used(n + 5);
        while (s.size()) {
            pair<int, int> now = *s.begin();
            s.erase(s.begin());
            int val = now.first, pos = now.second;
            if (used[pos]) continue;
            used[pos] = 1;
            H[pos] = val;
            for (int i = 0; i < g1[pos].size(); i++) {
                int nxt = g1[pos][i][0], w = g1[pos][i][1];
                s.insert({w + val, nxt});
            }
        }
        multiset<Q> s1;
        s1.insert({H[start], 0, start});
        vector<int> cnt(n + 5);
        while (s1.size()) {
            Q now = *s1.begin();
            s1.erase(s1.begin());
            int eval = now.eval, real = now.real, pos = now.pos;
            cnt[pos]++;
            if (pos == end && cnt[pos] == k) {
                return real;
            }
            if (cnt[pos] > k) continue;
            for (int i = 0; i < g2[pos].size(); i++) {
                int nxt = g2[pos][i][0], val = g2[pos][i][1];
                s1.insert({real + val + H[nxt], real + val, nxt});
            }
        }
        return -1;
    }
    

};

signed main() {
    int n, m;
    cin >> n >> m;
    KthPath K(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        K.add(a, b, c);
    }
    int start, end, k;
    cin >> start >> end >> k;
    cout << K.GetKthPath(start, end, k) << endl;
}