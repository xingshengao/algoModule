// 例题:https://loj.ac/p/103
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using PLL = pair<LL, LL>;

struct String_hash {
    vector<long long> pre1, p1;
    vector<long long> pre2, p2;
    long long base1 = 131, base2 = 29;
    long long mod1 = 1e9 + 7, mod2 = 1e9 + 9;

    String_hash(string s) {  // 构造函数
        long long n = s.size();
        pre1.resize(n + 1);
        pre2.resize(n + 1);
        p1.resize(n + 1);
        p2.resize(n + 1);
        p1[0] = 1;
        p2[0] = 1;
        for (long long i = 0; i < n; i++) {
            p1[i + 1] = (long long)p1[i] * base1 % mod1;
            p2[i + 1] = (long long)p2[i] * base2 % mod2;
            pre1[i + 1] = (((long long)pre1[i] * base1 % mod1 + s[i] - 'a' + 1) % mod1 + mod1) % mod1;
            pre2[i + 1] = (((long long)pre2[i] * base2 % mod2 + s[i] - 'a' + 1) % mod2 + mod2) % mod2;
        }
    }

    LL get_hash1(int l, int r) {
        l++, r++;
        return ((pre1[r] - (long long)pre1[l - 1] * p1[r - l + 1] % mod1) % mod1 + mod1) % mod1;
    }

    LL get_hash2(int l, int r) {
        l++, r++;
        return ((pre2[r] - (long long)pre2[l - 1] * p2[r - l + 1] % mod2) % mod2 + mod2) % mod2;
    }
    PLL get_hash(int l, int r) { return PLL(get_hash1(l, r), get_hash2(l, r)); }
};
bool is_equal(string a, string b) {
    String_hash A(a), B(b);
    return (A.get_hash1(0, a.size() - 1) == B.get_hash1(0, b.size() - 1) && A.get_hash2(0, a.size() - 1) == B.get_hash2(0, b.size() - 1));
}

// 例题
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
