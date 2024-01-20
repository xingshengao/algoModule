#include <bits/stdc++.h>
using namespace std;


using LL = long long;
// 预处理每个数的所有因子, 复杂度O(NlogN)
const int N = 100010;
vector<int> divisor[N];
int init = []() {
    for (int x = 1; x < N; ++x) {
        for (int d = x; d < N; d += x) {
            divisor[d].push_back(x);
        }
    }
    return 0;
}();