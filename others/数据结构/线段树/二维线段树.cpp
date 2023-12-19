#include <bits/stdc++.h>

using namespace std;

struct SegTree {

    int n, m;
    vector<int> t;
 
    SegTree(vector<vector<int>>& matrix) {
        this->n = matrix.size(), this->m = matrix[0].size();
        t.resize(n * m * 4 * 4 + 20);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                change(1, 1, 1, n, m, i + 1, j + 1, matrix[i][j]);
            }
        }
    }

    void change(int p, int u, int l, int d, int r, int x, int y, int v) {
        if (u > x || d < x || l > y || r < y) {
            return;
        } else if (u == d && u == x && l == r && l == y) {
            t[p] = v;
            return;
        } else {
            int mx = u + d >> 1, my = l + r >> 1;
            change(p * 4, u, l, mx, my, x, y, v);
            change(p * 4 + 1, u, my + 1, mx, r, x, y, v);
            change(p * 4 + 2, mx + 1, l, d, my, x, y, v);
            change(p * 4 + 3, mx + 1, my + 1, d, r, x, y, v);
            t[p] = t[p * 4] + t[p * 4 + 1] + t[p * 4 + 2] + t[p * 4 + 3];
        }
    }
 
    int query(int p, int u, int l, int d, int r, int x1, int y1, int x2, int y2) {
        if (u > x2 || d < x1 || l > y2 || r < y1) {
            return 0;
        } else if (u >= x1 && d <= x2 && l >= y1 && r <= y2) {
            return t[p];
        } else {
            int mx = u + d >> 1, my = l + r >> 1;
            int s1 = query(p * 4, u, l, mx, my, x1, y1, x2, y2);
            int s2 = query(p * 4 + 1, u, my + 1, mx, r, x1, y1, x2, y2);
            int s3 = query(p * 4 + 2, mx + 1, l, d, my, x1, y1, x2, y2);
            int s4 = query(p * 4 + 3, mx + 1, my + 1, d, r, x1, y1, x2, y2);
            return s1 + s2 + s3 + s4;
        }
    }
    
    
    void change(int row, int col, int val) {
        change(1, 1, 1, n, m, row + 1, col + 1, val);
    }
    
    int query(int row1, int col1, int row2, int col2) {
        return query(1, 1, 1, n, m, row1 + 1, col1 + 1, row2 + 1, col2 + 1);
    }

};

signed main() {
    vector<vector<int>> a = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SegTree S(a);
    cout << S.query(0, 0, 2, 2) << endl;
}