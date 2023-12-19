#include <bits/stdc++.h>

using namespace std;

signed main() {

    // 生成随机数
    mt19937 rand(time(0));
    cout << rand() << endl;

    // 随机打乱数组
    vector<int> a = {1, 2, 3};
    random_shuffle(a.begin(), a.end());
    random_shuffle(a.begin(), a.end());
    random_shuffle(a.begin(), a.end());
    for (int x : a) {
        cout << x << ' ';
    }
    cout << endl;


}
