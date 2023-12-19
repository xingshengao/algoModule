// https://www.luogu.com.cn/problem/P3812
// https://loj.ac/p/114
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Linear_basis {
    
    int MAXN = 63;
    vector<int> a, b;
    bool flag;

    Linear_basis() {
        flag = false;
        a = vector<int> (66);
        b = vector<int> (66);
    }

    void insert(int x) {    // 插入一个数x
        for (int i = MAXN; i >= 0; i--) {
            if(x & (1ll << i)) {
                if (!a[i]) {
                    a[i] = x;
                    return;
                } else {
                    x ^= a[i];
                }
            }
        }
        flag = true;
    }

    bool check(int x) {     // 判断能否通过原数列异或得到一个数x
        for(int i = MAXN; i >= 0; i--) {
            if (x & (1ll << i)) {
                if (!a[i]) return false;
                else x ^= a[i];
            }
        }
        return true;
    }

    int query_max() {       // 查询最大异或和
        int res = 0;
        for (int i = MAXN; i >= 0; i--) {
            res = max(res, res ^ a[i]);
        }
        return res;
    }

    int query_min() {        // 查询最小异或和
        if (flag) return 0;
        for (int i = 0; i <= MAXN; i++) {
            if (a[i]) return a[i];
        }
        return 0;
    }

    int query_kth(int k) {  // 查询第k小异或和
        int res = 0, cnt = 0;
        k -= flag;
        if (!k) return 0;
        for (int i = 0; i<= MAXN; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (a[i] & (1ll << j)) a[i] ^= a[j];
            }
            if (a[i]) b[cnt++] = a[i];
        }
        if (k >= (1ll << cnt)) return -1;
        for (int i = 0; i < cnt; i++) {
            if (k & (1ll << i)) res ^= b[i];
        }
        return res;
    }

};

signed main(){
    int n;
    cin >> n;
    Linear_basis L;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        L.insert(a);
    }
    int m;
    cin >> m;
    while (m--) {
        int k;
        cin >> k;
        cout << L.query_kth(k) << endl;
    }
    return 0;
}