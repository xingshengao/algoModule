#include <bits/stdc++.h>
using namespace std;
vector<int> f() {
    vector<int> A;  // 高效枚举40000内的回文数
    for (int i = 1; i < 400; i++) {
        int p = i;
        for (int x = i / 10; x > 0; x /= 10) {
            p = p * 10 + x % 10;
        }
        A.push_back(p);
        if (i < 100) {
            p = i;
            for (int x = i; x > 0; x /= 10) {
                p = p * 10 + x % 10;
            }
            A.push_back(p);
        }
    }
    return A;
}