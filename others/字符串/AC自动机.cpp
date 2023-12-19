// https://www.luogu.com.cn/problem/P3808
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Automaton {

    int tot;
    vector<vector<int>> tr;
    vector<int> e, fail;

    Automaton() {}
    Automaton(int n) {  // n为字符总数
        tot = 0;
        tr.resize(n + 30, vector<int> (26));
        e.resize(n + 30);
        fail.resize(n + 30);
    }

    void insert(string& s) {    // 插入一条模式串s
        int u = 0;
        for (int i = 0; i < s.size(); i++) {
            if (!tr[u][s[i] - 'a']) tr[u][s[i] - 'a'] = ++tot;
            u = tr[u][s[i] - 'a'];
        }
        e[u]++;
    }

    void build() {  // 构建AC自动机
        deque<int> q;
        for (int i = 0; i < 26; i++) {
            if (tr[0][i]) q.push_back(tr[0][i]);
        }
        while (q.size()) {
            int u = q.front();
            q.pop_front();
            for (int i = 0; i < 26; i++) {
                if (tr[u][i]) {
                    fail[tr[u][i]] = tr[fail[u]][i];
                    q.push_back(tr[u][i]);
                } else {
                    tr[u][i] = tr[fail[u]][i];
                }
            }
        }
    }

    int query(string& t) {  // 询问有多少个不同的模式串s在文本串t里出现过
        int u = 0, res = 0;
        for (int i = 0; i < t.size(); i++) {
            u = tr[u][t[i] - 'a'];
            for (int j = u; j && e[j] != -1; j = fail[j]) {
                res += e[j], e[j] = -1;
            }
        }
        return res;
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    Automaton A(1000000);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        A.insert(s);
    }
    A.build();
    string t;
    cin >> t;
    cout << A.query(t) << endl;
    return 0;
}
