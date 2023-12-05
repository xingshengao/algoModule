#include <bits/stdc++.h>
typedef long long LL;
using namespace std;
static constexpr long long mod = 1e9 + 7;
class Solution {
   public:
    LL fpow(LL x, LL n) {
        LL res = 1;
        for (; n; n /= 2) {
            if (n & 1) res = res * x % mod;
            x = x * x % mod;
        }
        return res;
    }
    LL frac[100010]{0};  // 阶乘
    void init() {        // 计算好阶乘
        frac[0] = frac[1] = 1LL;
        for (int i = 2; i < 100010; ++i) frac[i] = frac[i - 1] * i % mod;
    }
    // a乘b的逆元 <=> a除b, 而b的逆元就是fpow(b, mod - 2)
};