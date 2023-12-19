// 例题: 1.https://loj.ac/p/111
// 2.https://www.luogu.com.cn/problem/P2408
#include <bits/stdc++.h>
#define int long long

using namespace std;

// sa[i]: 排名第i的后缀的开始位置
// rk[i]: 从i开始的后缀的排名
// height[i]: 第i名的后缀与它前一名的后缀的最长公共前缀长度

struct Suffix_array {
    
    int n;
    string s;
    vector<int> sa, rk, oldrk, height;
    
    Suffix_array() {}
    Suffix_array(string s) {
        this->n = s.size();
        this->s = ' ' + s;    // 将字符串s转换成下标从1开始
        sa.resize(n + 1);
        rk.resize((n + 1) * 2);
        oldrk.resize((n + 1) * 2);
        height.resize(n + 1);
    }

    void get_sa() { // 倍增法求sa、rk
        for (int i = 1; i <= n; i++) {
            sa[i] = i;
            rk[i] = s[i];
        }
        for (int w = 1; w < n; w <<= 1) {
            sort(sa.begin() + 1, sa.begin() + n + 1, [&](auto x, auto y) {
                return rk[x] != rk[y] ? rk[x] < rk[y] : rk[x + w] < rk[y + w];
            });
            oldrk = rk;
            for (int i = 1, p = 0; i <= n; i++) {
                if (oldrk[sa[i]] == oldrk[sa[i - 1]] && oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                    rk[sa[i]] = p;
                } else {
                    rk[sa[i]] = ++p;
                }
            }
        }
    }

    void get_height() { // 求height数组, 需要先求sa、rk数组
        for (int i = 1, k = 0; i <= n; i++) {
            if (rk[i] == 0) continue;
            if (k) k--;
            while (s[i + k] == s[sa[rk[i] - 1] + k]) k++;
            height[rk[i]] = k;
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    Suffix_array T(s);
    T.get_sa();
    T.get_height();
    int res = n * (n + 1) / 2;
    for (int i = 1; i <= n; i++) {
        res -= T.height[i];
    }
    cout << res << endl;
    return 0;
}
