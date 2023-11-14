#include <bits/stdc++.h>
using namespace std;
// 严格递增的LIS子序列, 二分+贪心
template <typename T>
int lis(vector<T> A) {
    vector<T> dp;
    for (auto x : A) {
        auto it = lower_bound(dp.begin(), dp.end(), x);
        if (it == dp.end())
            dp.push_back(x);
        else
            *it = x;
    }
    return dp.size();
}
// 非递减的LIS子序列, 二分+贪心
template <typename T>
int lis(vector<T> A) {
    vector<T> dp;
    for (auto x : A) {
        auto it = upper_bound(dp.begin(), dp.end(), x);
        if (it == dp.end())
            dp.push_back(x);
        else
            *it = x;
    }
    return dp.size();
}
int main() {}