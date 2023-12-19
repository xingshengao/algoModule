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

    int C(int a, int b) {   // 求a个里面选b个的方案数, 单次查询时间复杂度O(b)
        if (a < b) return 0;
        int a1 = 1, a2 = 1;
        for (int i = a; i >= a - b + 1; i--) {
            a1 = a1 * i % mod;
        }
        for (int i = 2; i <= b; i++) {
            a2 = a2 * i % mod;
        }
        return a1 * pow(a2, mod - 2) % mod;
    }  

};

signed main() {
    int a = 1000000000, b = 100000;
    Combine C;
    cout << C.C(a, b) << endl;
    return 0;
}