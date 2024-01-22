#include <bits/stdc++.h>
using namespace std;
using LL = long long;

// C++对顶堆, 懒删除堆, 维护滑窗中位数, H代表维护的数据类型, 使用时DualHeap<int> dh(k);
template <typename H>
struct DualHeap {
    // 大根堆，维护较小的一半元素
    priority_queue<H> L;
    // 小根堆，维护较大的一半元素
    priority_queue<H, vector<H>, greater<H>> R;
    // 哈希表，记录「延迟删除」的元素，key 为元素，value 为需要删除的次数
    unordered_map<H, int> del_cnt;

    int k;
    // L 和 R 当前包含的元素个数，需要扣除被「延迟删除」的元素
    int LSize, RSize;

    DualHeap(int _k) : k(_k), LSize(0), RSize(0) {}

    // 不断地弹出 heap 的堆顶元素，并且更新哈希表
    template <typename T>
    void adjust(T& heap) {
        while (!heap.empty()) {
            H num = heap.top();
            if (del_cnt.count(num)) {
                --del_cnt[num];
                if (!del_cnt[num]) {
                    del_cnt.erase(num);
                }
                heap.pop();
            } else {
                break;
            }
        }
    }

    // 调整 L 和 R 中的元素个数，使得二者的元素个数满足要求
    void makeBalance() {
        if (LSize > RSize + 1) {
            // L 比 R 元素多 2 个
            R.push(L.top());
            L.pop();
            --LSize, ++RSize;
            // L 堆顶元素被移除，需要进行 adjust
            adjust(L);
        } else if (LSize < RSize) {
            // R 比 L 元素多 1 个
            L.push(R.top());
            R.pop();
            ++LSize, --RSize;
            // R 堆顶元素被移除，需要进行 adjust
            adjust(R);
        }
    }

    void insert(int num) {
        if (L.empty() || num <= L.top()) {
            L.push(num);
            ++LSize;
        } else {
            R.push(num);
            ++RSize;
        }
        makeBalance();
    }

    void erase(int num) {
        ++del_cnt[num];
        if (num <= L.top()) {
            --LSize;
            if (num == L.top()) {
                adjust(L);
            }
        } else {
            --RSize;
            if (num == R.top()) {
                adjust(R);
            }
        }
        makeBalance();
    }

    double getMedian() { return k & 1 ? L.top() : ((double)L.top() + R.top()) / 2; }
};

// 480. 滑动窗口中位数
// 困难
// 相关标签
// 相关企业
// 提示
// 中位数是有序序列最中间的那个数。如果序列的长度是偶数，则没有最中间的数；此时中位数是最中间的两个数的平均数。

class Solution {
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        DualHeap<int> dh(k);
        for (int i = 0; i < k; ++i) {
            dh.insert(nums[i]);
        }
        vector<double> ans = {dh.getMedian()};
        for (int i = k; i < nums.size(); ++i) {
            dh.insert(nums[i]);
            dh.erase(nums[i - k]);
            ans.push_back(dh.getMedian());
        }
        return ans;
    }
};