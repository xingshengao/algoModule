#include <bits/stdc++.h>
using namespace std;

template<typename T>
void qsort(vector<T>& nums, int l, int r) {
    if (l >= r) return;
    T key = nums[l]; // 找到一个基准元素
    int i = l, j = r;
    while (i < j) {
        while (i < j && nums[j] >= key) --j; // 从右边开始找， 找到第一个<key的下标
        while (i < j && nums[i] <= key) ++i; // 从左向右找，找到第一个小于key的下标
        if (i < j) swap(nums[i], nums[j]);
    }
    // i和j相遇说明指针ij左边的数都小于等于key，右边都大于等于key
    swap(nums[i], nums[l]);
    qsort(nums, l, i - 1);
    qsort(nums, i + 1, r);
}