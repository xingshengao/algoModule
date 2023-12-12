#include <bits/stdc++.h>
typedef long long LL;
namespace Comb {
constexpr LL N = 1e5 + 50;
constexpr LL MOD = 1e9 + 7;
LL frac[N];  // 阶乘

void init() {
    frac[0] = frac[1] = 1;
    for (LL i = 2; i < N; ++i) frac[i] = frac[i - 1] * i % MOD;
}

LL fpow(LL x, LL exp) {  // 快速幂
    LL res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x % MOD;
        x = x * x % MOD;
    }
    return res;
}

/* C(n, k) means select k from n. */
LL C(LL n, LL k) {
    LL upper = frac[n];
    LL lower = (fpow(frac[k], MOD - 2) * fpow(frac[n - k], MOD - 2)) % MOD;  // 逆元

    return (upper * lower) % MOD;
}
};  // namespace Comb
using namespace Comb;
int main() {
    // 使用举例
    init();
    std::cout << C(4, 2) << std::endl;
}