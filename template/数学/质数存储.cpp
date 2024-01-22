#include <bits/stdc++.h>
using namespace std;
using LL = long long;
// 质数筛
const int N = 1000100;
int isPrime[N];
vector<LL> P;
int init = []() {
    for (int i = 0; i < N; ++i) isPrime[i] = 1;
    isPrime[1] = 1;
    isPrime[2] = 1;
    for (int i = 2; i * i < N; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j < N; j += i) {
                isPrime[j] = 0;
            }
        }
    }
    for (int i = 2; i < N; ++i) {
        if (isPrime[i]) {
            P.push_back(i);
        }
    }
    return 0;
}();