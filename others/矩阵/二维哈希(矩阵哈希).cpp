// https://www.acwing.com/problem/content/description/158/
#include <bits/stdc++.h>

using namespace std;

struct Matrix_hash {
    
    #define ull unsigned long long
    
    int n, m;
    ull base1 = 131, base2 = 233;
    vector<vector<ull>> h;
    vector<ull> pbase1, pbase2;

    Matrix_hash(vector<vector<int>>& mat) {
        this->n = mat.size();
        this->m = mat[0].size();
        h = vector<vector<ull>> (n + 1, vector<ull> (m + 1));

        int maxLen = max(n, m);
        pbase1 = vector<ull> (maxLen + 1);
        pbase2 = vector<ull> (maxLen + 1);
        pbase1[0] = 1, pbase2[0] = 1;
        for (int i = 1; i <= maxLen; i++) {
            pbase1[i] = pbase1[i - 1] * base1;
            pbase2[i] = pbase2[i - 1] * base2;
        }
        
        // 行哈希
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                h[i][j] = h[i][j - 1] * base1 + mat[i - 1][j - 1];
            }
        }
        // 列哈希
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                h[i][j] = h[i][j] + h[i - 1][j] * base2;
            }
        }
    }

    ull get_hash(int x1, int y1, int x2, int y2) { // 查询矩阵(x1, y1)~(x2, y2)的哈希值, x1 <= x2 && y1 <= y2
        x1++, y1++, x2++, y2++;
        return h[x2][y2] - h[x2][y1 - 1] * pbase1[y2 - y1 + 1] - h[x1 - 1][y2] * pbase2[x2 - x1 + 1] + h[x1 - 1][y1 - 1] * pbase1[y2 - y1 + 1] * pbase2[x2 - x1 + 1];
    }

};


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<int>> mat(n, vector<int> (m));
    string t;
    for (int i = 0; i < n; i++) {
        cin >> t;
        for (int j = 0; j < m; j++) {
            mat[i][j] = t[j] - '0';
        }
    }
    Matrix_hash M(mat);
    set<ull> ok;
    for (int i = a - 1; i < n; i++) {
        for (int j = b - 1; j < m; j++) {
            ok.insert(M.get_hash(i - a + 1, j - b + 1, i, j));
        }
    }
    int q;
    cin >> q;
    while (q--) {
        vector<vector<int>> qmat(a, vector<int> (b));
        for (int i = 0; i < a; i++) {
            cin >> t;
            for (int j = 0; j < b; j++) {
                qmat[i][j] = t[j] - '0';
            }
        }
        Matrix_hash T(qmat);
        if (ok.count(T.get_hash(0, 0, a - 1, b - 1))) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    return 0;
}
