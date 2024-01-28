#include <bits/stdc++.h>
using namespace std;

using LL = long long;
template <class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) { init(std::vector(n_, v_)); }
    template <class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
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
    template <class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template <class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template <class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Tag {
    LL k = 0;
    LL b = 0;

    void apply(const Tag& t) {
        if (t.k < 0) {
            k = t.k;
            b = t.b;
        }
    }
};

struct Info {
    LL cnt = 0;
    LL sid = 0;
    LL sum = 0;

    void apply(const Tag& t) {
        if (t.k < 0) {
            sum = sid * t.k + cnt * t.b;
        }
    }
};

Info operator+(const Info& a, const Info& b) { return {a.cnt + b.cnt, a.sid + b.sid, a.sum + b.sum}; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<int> X(m), V(m);
    for (int i = 0; i < m; i++) {
        std::cin >> X[i];
        X[i]--;
    }
    for (int i = 0; i < m; i++) {
        std::cin >> V[i];
    }

    std::map<int, int> s;
    for (int i = 0; i < m; i++) {
        s[X[i]] = V[i];
    }

    LazySegmentTree<Info, Tag> seg(n);
    for (int i = 0; i < n; i++) {
        seg.modify(i, {1, i, 0});
    }
    auto work = [&](auto it) {
        auto nxt = std::next(it);
        seg.rangeApply(it->first + 1, nxt->first + 1, {-it->second, 1LL * it->second * nxt->first});
    };
    for (auto it = s.begin(); it->first != n - 1; it++) {
        work(it);
    }

    while (q--) {
        int t, x, y;
        std::cin >> t >> x >> y;

        if (t == 1) {
            x--;
            s[x] = y;
            auto it = s.find(x);
            work(it);
            work(std::prev(it));
        } else {
            x--;
            LL ans = seg.rangeQuery(x, y).sum;
            std::cout << ans << "\n";
        }
    }

    return 0;
}