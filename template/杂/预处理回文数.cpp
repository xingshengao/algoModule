#include <bits/stdc++.h>
using namespace std;
using LL = long long;
vector<LL> A;
// 这种写法, 可以保证只执行一次
int init = []() {
    // 高效枚举1e9内的回文数
    for (LL i = 1; i <= 100000; i++) {
        // 第一部分 12345->123454321
        LL p = i;
        for (LL x = i / 10; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        if (p < 1e9) A.push_back(p);
        // 第二部分 12345->1234554321
        p = i;
        for (LL x = i; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        if (p < 1e9) A.push_back(p);
    }
    sort(A.begin(), A.end());
    return 0;
}();