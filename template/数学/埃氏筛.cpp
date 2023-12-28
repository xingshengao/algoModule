// 质数筛
#include <bits/stdc++.h>
using namespace std;
// 预处理所有质因子
const int N = 100010;
vector<int> fac[N + 10];
// 预处理每个数的质因子
int init = []() {
    for (int i = 2; i <= N; ++i) {
        if (fac[i].size() == 0) {
            for (int j = i; j <= N; j += i) fac[j].push_back(i);
        }
    }
    return 0;
}();
// 质数筛
void solve() {
    const int N = 1e5 + 1;
    bool isPrime[N];
    memset(isPrime, true, sizeof(isPrime));
    isPrime[1] = false;
    isPrime[0] = false;
    // 埃氏筛
    for (int i = 2; i * i < N; ++i) {
        if (isPrime[i]) {  // 如果是质数, 就从i * i 开始把i的倍数标记为合数
            for (int j = i * i; j < N; j += i) {
                isPrime[j] = false;
            }
        }
    }
}
int main() {
    return 0;
}