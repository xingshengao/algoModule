#include <bits/stdc++.h>
using namespace std;
using LL = long long;

template <class Info, class Tag>
struct LazySegmentTree {
    const int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n) : n(n), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void apply(int p, const Tag& v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info& v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info& v) { modify(1, 0, n, p, v); }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) { return rangeQuery(1, 0, n, l, r); }
    void rangeApply(int p, int l, int r, int x, int y, const Tag& v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag& v) { return rangeApply(1, 0, n, l, r, v); }

    int search(int p, int l, int r, int x, int y, LL v) {
        if (l >= y || r <= x) return y;
        if (info[p].min >= v) return y;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        push(p);
        int res = search(2 * p, l, m, x, y, v);
        if (res == y) res = search(2 * p + 1, m, r, x, y, v);
        return res;
    }

    int search(int l, int r, LL v) { return search(1, 0, n, l, r, v); }
};

struct Tag {
    LL x;

    Tag(int _x = 0) : x{_x} {}

    void apply(const Tag& t) { x += t.x; }
};

struct Info {
    int l = 0;
    int r = 0;
    LL sum = 0;

    void apply(const Tag& t) { sum += t.x * (r - l); }
};

Info operator+(const Info& a, const Info& b) { return Info{min(a.l, b.l), max(a.r, b.r), a.sum + b.sum}; }

// 区间求改和区间查询
void solve() {
    int n, m;
    cin >> n >> m;
    vector<Info> infos(n);
    for (int i = 0; i < n; ++i) {
        LL x;
        cin >> x;
        infos[i] = Info{i, i + 1, x};
    }
    LazySegmentTree<Info, Tag> seg(infos);
    for (int _ = 0; _ < m; ++_) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            seg.rangeApply(x - 1, y, k);  // 区间修改左闭右开区间
        } else {
            int x, y;
            cin >> x >> y;
            cout << seg.rangeQuery(x - 1, y).sum << endl;  // 区间查询, 左闭右开区间
        }
    }
}

int main() {
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}