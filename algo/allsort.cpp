#include <bits/stdc++.h>

using namespace std;
// 冒泡排序, 重复地遍历数组，比较相邻的元素，交换它们直到整个数组有序。
void bubble_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (nums[j] > nums[j + 1]) {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}
// 选择排序, 从数组中选择最小（或最大）元素，放置在已排序部分的末尾。
void select_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (nums[j] < nums[min_index]) min_index = j;
        }
        if (min_index != i) {
            swap(nums[i], nums[min_index]);
        }
    }
}
// 插入排序在待排序的元素中，假设前n-1个元素已有序，现将第n个元素插入到前面已经排好的序列中，使得前n个元素有序。按照此法对所有元素进行插入，直到整个序列有序。
void insert_sort(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n - 1; ++i) {
        // 记录有序序列最后一个元素的下标
        int end = i;
        // 待插入的元素
        int tmp = nums[end + 1];
        // 单趟排序
        while (end >= 0) {
            // 比插入的数大就向后移
            if (tmp < nums[end]) {
                nums[end + 1] = nums[end];
                end -= 1;
            } else {
                // 比插入的数字小, 跳出循环
                break;
            }
        }
        // 把tmp放到比插入的数小的数的后面
        nums[end + 1] = tmp;

        // 代码执行到此位置有两种情况:
        // 1.待插入元素找到应插入位置（break跳出循环到此）
        // 2.待插入元素比当前有序序列中的所有元素都小（while循环结束后到此）
    }
}
// 快速排序, 挖坑法
// 快排关键, 找到一个基准数, 大于它的放在右边, 小于它的放在左边, 然后递归分治解决左右两边的数组
template <typename T>
void quick_sort1(vector<T>& nums, int l, int r) {
    if (l >= r) return;  // 递归返回条件直至剩下一个数值
    srand((unsigned int)time(NULL) + 1);
    int pos = l;
    T key = nums[pos];
    int i = l, j = r;  // i 和 j 分别代表begin和end
    while (i < j) {
        // 选择一个数值key，左边放小于其的，右边放大于其的
        while (i < j && nums[j] >= key) {
            j--;
        }
        nums[pos] = nums[j];  // 把小的数放在坑中
        pos = j;              // 坑的位置变成了key数值右边的
        while (i < j && nums[i] <= key) {
            i++;
        }
        nums[pos] = nums[i];
        pos = i;
    }
    nums[pos] = key;  // 把key放在最终的坑中
    quick_sort1(nums, l, pos - 1);
    quick_sort1(nums, pos + 1, r);
}
// 快速排序, 左右指针法
template <typename T>
void quick_sort(vector<T>& nums, int l, int r) {
    if (l >= r) return;  // 递归返回条件直至剩下一个数值
    T key = nums[l];     // 选择一个数值key，左边放小于其的，右边放大于其的
    int i = l, j = r;    // 双指针
    while (i < j) {
        while (i < j && nums[j] >= key) {  // 从右往左找到第一个小于key的位置j
            j--;
        }
        while (i < j && nums[i] <= key) {  // 从左向右找到第一个大于p的位置i
            i++;
        }
        if (i < j) swap(nums[i], nums[j]);
    }
    // i和j相遇说明指针ij左边的数都小于等于key, 右边都大于等于key
    swap(nums[i], nums[l]);
    quick_sort(nums, l, i - 1);
    quick_sort(nums, i + 1, r);
}
void solve() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    // bubble_sort(arr);
    // select_sort(arr);
    // insert_sort(arr);
    quick_sort(arr, 0, 6);
}
signed main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}