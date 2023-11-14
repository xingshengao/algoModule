#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
class Solution {
   public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        vector<PII> vec;  // 存储以i为左端点的按位或的值 + 对应子数组右端点的最小值
        // 这样在遍历时ors值最大的元素对应的子数组右端点的最小值, 就是要求的最短子数组的右端点
        for (int i = n - 1; i >= 0; --i) {
            vec.emplace_back(0, i);                 // 小集合总是在后面插入的, 因此vec是递减的
            for (int j = 0; j < vec.size(); ++j) {  // 更新集合, 把nums[i]插入集合
                vec[j].first |= nums[i];
            }
            // 原地去重, 类似leetcode26题目
            int j = 0, k = 0;
            for (; j < vec.size(); ++j) {
                if (vec[k].first != vec[j].first) {  // 不重复, 先增加k
                    vec[++k] = vec[j];
                } else {  // 有重复, 只记录最小的下标, k不递增, 合并相同值, 下标取最小的
                    vec[k].second = vec[j].second;
                }
            }
            vec.resize(k + 1);  // k 是已去重的最后一个元素下标, 因此保留k+1个元素
            // 本题只用到了vec[0], 即最大的或值, 如果题目改为任意数字, 可以在vec中查找
            ans[i] = vec[0].second - i + 1;
        }
        return ans;
    }
};
// 模板