// 例题:https://loj.ac/p/103
#include <bits/stdc++.h>

using namespace std;

struct String_hash {

    vector<int> pre1, p1;
    vector<int> pre2, p2;
    int base1 = 131, base2 = 29;
    int mod1 = 1e9 + 7, mod2 = 1e9 + 9;

    String_hash(string s) { // 构造函数
        int n = s.size();
        pre1.resize(n + 1);
        pre2.resize(n + 1);
        p1.resize(n + 1);
        p2.resize(n + 1);
        p1[0] = 1;
        p2[0] = 1;
        for (int i = 0; i < n; i++) {
            p1[i + 1] = (long long)p1[i] * base1 % mod1;
            p2[i + 1] = (long long)p2[i] * base2 % mod2;
            pre1[i + 1] = (((long long)pre1[i] * base1 % mod1 + s[i] - 'a' + 1) % mod1 + mod1) % mod1;
            pre2[i + 1] = (((long long)pre2[i] * base2 % mod2 + s[i] - 'a' + 1) % mod2 + mod2) % mod2;
        }
    }

    int get_hash1(int l, int r) {
        l++, r++;
        return ((pre1[r] - (long long)pre1[l - 1] * p1[r - l + 1] % mod1) % mod1 + mod1) % mod1;
    }

    int get_hash2(int l, int r) {
        l++, r++;
        return ((pre2[r] - (long long)pre2[l - 1] * p2[r - l + 1] % mod2) % mod2 + mod2) % mod2;
    }
};

int main() {
    string a, b;
    cin >> a >> b;
    String_hash A(a), B(b);
    int n = a.size(), m = b.size(), res = 0;
    for (int i = 0; i + m - 1 < n; i++) {
        // 两个模数的哈希值都要相等
        if (A.get_hash1(i, i + m - 1) == B.get_hash1(0, m - 1) && A.get_hash2(i, i + m - 1) == B.get_hash2(0, m - 1)) res++;
    }
    cout << res << endl;
    return 0;
}
