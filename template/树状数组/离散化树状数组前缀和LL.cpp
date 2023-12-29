#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
class Solution {  // 力扣327题目
   public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        LL n = nums.size();
        vector<LL> s(n + 1, 0);
        for (int i = 0; i < n; ++i) s[i + 1] = s[i] + nums[i];
        vector<LL> arr;  // 要离散化的数组
        for (LL ps : s) {
            arr.push_back(ps);
            arr.push_back(ps - lower);
            arr.push_back(ps - upper);
        }
        /////////////////////////////////////////////////////////////////////////////////
        // 要进行树状数组前缀和的点去重
        auto Uni = [](vector<LL>& A) -> vector<LL> {
            vector<LL> ans(A);
            sort(ans.begin(), ans.end());
            ans.erase(unique(ans.begin(), ans.end()), ans.end());
            return ans;
        };
        // 要进行离散化的数组, 可以是x可以是y
        vector<LL> A = Uni(arr);
        // 离散化
        map<LL, LL> mp;
        for (int i = 0; i < A.size(); ++i) {
            mp[A[i]] = i + 1;
        }
        vector<LL> tr(A.size() + 1, 0);
        // 树状数组模板
        auto low_bit = [&](LL x) -> LL { return x & -x; };
        auto query = [&](LL x) -> LL {
            LL sum = 0;
            for (; x; x -= low_bit(x)) sum += tr[x];
            return sum;
        };
        auto update = [&](LL x, LL v) -> void {
            for (; x < tr.size(); x += low_bit(x)) tr[x] += v;
        };
        ////////////////////////////////////////////////////////////////////////////
        // 本题计算
        LL ans = 0;
        for (int i = 0; i < s.size(); ++i) {
            LL ps = s[i];
            // [ps - upper, ps - lower]
            ans += query(mp[ps - lower]) - query(mp[ps - upper] - 1);
            update(mp[ps], 1);
        }
        return ans;
    }
};