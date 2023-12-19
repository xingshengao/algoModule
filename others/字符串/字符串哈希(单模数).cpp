// 例题:https://loj.ac/p/103
#include <bits/stdc++.h>

using namespace std;

#define ull unsigned long long

struct String_hash {

    vector<ull> pre, p;

    String_hash(string s) { // 构造函数
        int n = s.size();
        pre.resize(n + 1);
        p.resize(n + 1);
        p[0] = 1;
        ull base = 131;
        for (int i = 0; i < n; i++) {
            p[i + 1] = p[i] * base;
            pre[i + 1] = pre[i] * base + s[i] - 'a' + 1;
        }
    }

    ull get_hash(int l, int r) {
        l++, r++;
        return pre[r] - pre[l - 1] * p[r - l + 1];
    }
};

int main() {
    string a, b;
    cin >> a >> b;
    String_hash A(a), B(b);
    int n = a.size(), m = b.size(), res = 0;
    for (int i = 0; i + m - 1 < n; i++) {
        if (A.get_hash(i, i + m - 1) == B.get_hash(0, m - 1)) res++;
    }
    cout << res << endl;
    return 0;
}
