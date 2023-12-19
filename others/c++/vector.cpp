vector<int> v;      // 初始化

vector<int> v(n);   // 初始化v的长度为n

v.push_back(x);     // 向v的尾部插入x

v.pop_back();       // 弹出v的最后一个元素

v.insert(v.begin() + i, x);     // 在第i个位置插入x

v.erase(v.begin() + i);         // 删除第i个位置的元素

v.erase(v.begin() + i, v.begin() + j);  // 删除区间[i:j)里的元素

v.size();           // 返回v中元素个数

v.clear();          // 清空

v.empty();          // 判空

v.back();           // 返回最后一个元素

v.front();          // 返回第一个元素

v.resize(n);        // 调整v的长度为n，多删少补

v.resize(n, 0);     // 调整v的长度为n，多删少用0补

reverse(v.begin(), v.end());    // 翻转

sort(v.begin(), v.end());       // 排序

lower_bound(v.begin(), v.end(), x) - v.begin(); // 二分出第一个大于等于x元素的位置

upper_bound(v.begin(), v.end(), x) - v.begin(); // 二分出第一个大于x元素的位置

for (auto x : v) cout << x << ' ';      // 遍历

for (int i = 0; i < v.size(); i++) {    // 遍历
    cout << v[i] << ' ';
}
