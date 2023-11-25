#include <bits/stdc++.h>
using namespace std;

struct DSU {
   public:
    vector<int> fa;
    vector<int> ranker;
    DSU(int n) {
        fa.resize(n);
        ranker.resize(n);
        for (int i = 0; i < n; ++i) {
            fa[i] = i;
            ranker[i] = 1;
        }
    }
    int find(int x) {
        if (fa[x] == x) return x;
        fa[x] = find(fa[x]);
        return fa[x];
    }
    bool merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (ranker[fx] < ranker[fy]) swap(fx, fy);
        fa[fy] = fx;
        if (ranker[fx] == ranker[fy]) ++ranker[fx];
        return true;
    }
    bool isConnected(int x, int y) {
        int fx = find(x), fy = find(y);
        return fx == fy;
    }
    bool disConnect(int x) {
        fa[x] = x;
        return true;
    }
};
