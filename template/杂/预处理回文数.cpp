#include <bits/stdc++.h>
using namespace std;

using LL = long long;
vector<LL> A;
int init = []() {  // 预处理1e9内的所有回文数字, 这种写法, 可以保证只执行一次
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

// 1e11内的所有回文数字
namespace EE11 {
using LL = long long;
vector<LL> A;
int init = []() {  // 预处理1e13内的所有回文数字, 这种写法, 可以保证只执行一次
    // 高效枚举1e11内的回文数
    for (LL i = 1; i <= 1000000; i++) {
        // 第一部分 12345->123454321
        LL p = i;
        for (LL x = i / 10; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        if (p < 1e11) A.push_back(p);
        // 第二部分 12345->1234554321
        p = i;
        for (LL x = i; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        if (p < 1e11) A.push_back(p);
    }
    sort(A.begin(), A.end());
    return 0;
}();
};  // namespace EE11

// 1e13内的所有回文数
namespace EE13 {
using LL = long long;
vector<LL> A;
int init = []() {  // 预处理1e13内的所有回文数字, 这种写法, 可以保证只执行一次
    for (LL i = 1; i <= 10000000; i++) {
        // 第一部分 12345->123454321
        LL p = i;
        for (LL x = i / 10; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        if (p < 1e13) A.push_back(p);
        // 第二部分 12345->1234554321
        p = i;
        for (LL x = i; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        if (p < 1e13) A.push_back(p);
    }
    sort(A.begin(), A.end());
    return 0;
}();
};  // namespace EE13
