// https://www.luogu.com.cn/problem/P3807
#include <bits/stdc++.h>

using namespace std;

#define int long long
struct Combine {

    int mod;
    vector<int> f;

    int pow(int a, int b) { // 快速幂
        int res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res % mod;
    }

    Combine() {}
    Combine(int mod) {    // 构造函数, 传入最大模数mod
        this->mod = mod;
        f.resize(mod + 1);
        f[0] = 1;
        for (int i = 1; i <= mod; i++) {
            f[i] = f[i - 1] * i % mod;
        }
    }

    int get(int a, int b) {
        if (b > a) return 0;
        return f[a] * pow(f[b], mod - 2) % mod * pow(f[a - b], mod - 2) % mod;
    }

    int C(int a, int b) {   // 求a个里面选b个的方案数, 单次查询时间复杂度O(logn)
        if (b == 0) return 1;
        return C(a / mod, b / mod) * get(a % mod, b % mod) % mod;
    }  

};

signed main() {
    int q, n, m, p;
    cin >> q;
    while (q--) {
        int n, m, mod;
        cin >> n >> m >> mod;
        Combine C(mod);
        cout << C.C(n + m, n) << endl;
    }
    return 0;
}