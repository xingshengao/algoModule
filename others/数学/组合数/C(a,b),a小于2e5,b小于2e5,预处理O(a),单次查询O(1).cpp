// 例题:https://vjudge.net/problem/%E8%AE%A1%E8%92%9C%E5%AE%A2-T1984
#include <bits/stdc++.h>

using namespace std;

#define int long long
struct Combine {

    int mod = 1e9 + 7;
    vector<int> f, invf;

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
    Combine(int n) {    // 构造函数
        f.resize(n + 1), invf.resize(n + 1);
        f[0] = 1, invf[0] = 1;
        for (int i = 1; i <= n; i++) {
            f[i] = f[i - 1] * i % mod;
            invf[i] = pow(f[i], mod - 2);
        }
    }

    int C(int a, int b) {   // 求a个里面选b个的方案数
        if (a < b) return 0;
        return f[a] * invf[a - b] % mod * invf[b] % mod;
    }  

};

signed main() {
    int n, m;
    cin >> n >> m;
    Combine C(n);
    cout << C.C(n, m) << endl;
    return 0;
}
