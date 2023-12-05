#include <bits/stdc++.h>
typedef long long LL;
namespace Comb {
constexpr LL N = 1e5 + 50;
constexpr LL mod = 1e9 + 7;
LL frac[N];  // 阶乘

void init() {
    frac[0] = frac[1] = 1;
    for (LL i = 2; i < N; ++i) frac[i] = frac[i - 1] * i % mod;
}

LL fpow(LL x, LL exp) {  // 快速幂
    LL res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}

/* C(n, k) means select k from n. */
LL C(LL n, LL k) {
    LL upper = frac[n];
    LL lower = (fpow(frac[k], mod - 2) * fpow(frac[n - k], mod - 2)) % mod;  // 逆元

    return (upper * lower) % mod;
}
};  // namespace Comb
using namespace Comb;
int main() {
    // 使用举例
    init();
    std::cout << C(4, 2) << std::endl;
}