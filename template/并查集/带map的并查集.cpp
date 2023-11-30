#include<bits/stdc++.h>
using namespace std;
struct DSU {
    int cnt; // 连通分量的数目
    unordered_map<int, int> mp; // 连通分量大小, 数目
    vector<int> f, siz;
    DSU() {}
    DSU(int n) { init(n); }
    void init(int n) {
        f.resize(n);
        iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        cnt = n;
        mp[1] = n;
    }
    int find(int x) {
        while (x != f[x]) {
            x = f[x] = f[f[x]];
        }
        return x;
    }
    void merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        f[y] = x;
        mp[siz[y]]--;
        mp[siz[x]]--; // 之前的siz都没了
        siz[x] += siz[y];
        mp[siz[x]] += 1;
        cnt--;
    }
    int size(int x) { return siz[find(x)]; }
};