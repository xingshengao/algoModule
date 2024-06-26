// 质数筛
#include <bits/stdc++.h>
using namespace std;

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


// 质数筛
const int N = 1000100;
int isPrime[N];
int init = []() {
    for (int i = 0; i < N; ++i) isPrime[i] = 1;
    isPrime[1] = 0;
    isPrime[2] = 1;
    for (int i = 2; i * i < N; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < N; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    return 0;
}();

