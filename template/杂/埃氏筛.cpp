// 质数筛
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 1;
int main() {
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
    return 0;
}