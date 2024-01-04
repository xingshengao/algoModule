#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void f() {
    vector<LL> arr;

    // 离散化
    auto Uni = [](vector<LL>& A) -> vector<LL> {
        vector<LL> ans(A);
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());
        return ans;
    };
    vector<LL> A = Uni(arr);
    map<LL, LL> mp;
    for (int i = 0; i < A.size(); ++i) {
        mp[A[i]] = i + 1;
    }
}