#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// 开区间线段树
template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;

    Fenwick(int n = 0) { init(n); }

    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }

    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }

    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }

    T rangeSum(int l, int r) { return sum(r) - sum(l); }

    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

// 重载MAX树状数组
struct Info {
    LL x;
    Info() { x = -1e18; }
    Info(LL val) { x = val; }
    Info operator+=(Info& rhs) {
        this->x = max(this->x, rhs.x);
        return *this;
    }
};

void LiSanHua() {  // 离散化的代码
    vector<LL> arr;
    // 要进行树状数组前缀和的点去重
    auto Uni = [](vector<LL>& A) -> vector<LL> {
        vector<LL> ans(A);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    };
    // 要进行离散化的数组, 可以是x可以是y
    vector<LL> A = Uni(arr);
    // 离散化
    map<LL, LL> mp;
    for (int i = 0; i < A.size(); ++i) {
        mp[A[i]] = i + 1;
    }
    Fenwick<LL> fen(A.size() + 1);
}