// 例题:https://loj.ac/p/6277
#include <bits/stdc++.h>

using namespace std;

struct Block {
    
    int n, m;
    vector<int> d, pos, l, r, lazy;
    // n为元素个数，m为分成几个块
    // d为原始数组，下标从1开始
    // l[i]表示第i块的最左边元素的位置
    // r[i]表示第i块的最右边元素的位置
    // pos[i]表示第i个元素在第几个块内
    
    Block() {}
    Block(vector<int> a) {  // 数组a的下标从0开始
        n = a.size(), m = sqrt(n);
        d.resize(n + 1);
        pos.resize(n + 1);
        l.resize(m + 1);
        r.resize(m + 1);
        lazy.resize(m + 1);
        for (int i = 0; i < n; i++) {   // 将下标转化为从1开始
            d[i + 1] = a[i];
        }
        for (int i = 1; i <= m; i++) {
            l[i] = m * (i - 1) + 1;
            r[i] = m * i;
        }
        r[m] = n;
        for (int i = 1; i <= m; i++) {
            for (int j = l[i]; j <= r[i]; j++) {
                pos[j] = i;
            }
        }
    }

    void change(int left, int right, int c) {
        for (int i = pos[left]; i <= pos[right]; i++) {
            if (left <= l[i] && r[i] <= right) {
                lazy[i] += c;
            } else {
                for (int j = max(l[i], left); j <= min(r[i], right); j++) {
                    d[j] += c;
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Block B(a);
    while (n--) {
        int opt, l, r, c;
        cin >> opt >> l >> r >> c;
        if (opt == 0) {
            B.change(l, r, c);
        } else {
            cout << B.d[r] + B.lazy[B.pos[r]] << endl;
        }
    }
}