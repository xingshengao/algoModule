// 作者：Nreyog
// 题目链接：https://leetcode.cn/problems/number-of-islands/

struct dsu {

    vector<vector<pair<int, int>>> fa;      // fa[i][j] 表示i, j这个点的祖先坐标, 用一个 pair<int, int> 存储

    dsu() {}
    dsu(int n, int m) {     // 初始化并查集
        fa.resize(n + 5, vector<pair<int, int>> (m + 5));
        for (int i = 0; i < n + 5; i++) {
            for (int j = 0; j < m + 5; j++) {
                fa[i][j].first = i;
                fa[i][j].second = j;
            }
        }
    }

    pair<int, int> find(pair<int, int> p) {   // 找到祖先结点的位置
        return fa[p.first][p.second] == p ? p : fa[p.first][p.second] = find(fa[p.first][p.second]);
    }

    void merge(int x1, int y1, int x2, int y2) {    // 合并两个二维点
        pair<int, int> p1(x1, y1);
        pair<int, int> p2(x2, y2);
        p1 = find(p1);
        p2 = find(p2);
        if (p1 == p2) return;
        fa[p1.first][p1.second] = p2;
    }

    bool same(int x1, int y1, int x2, int y2) {   // 判断两个二维点是否是同一集合
        return find({x1, y1}) == find({x2, y2});
    }

};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        dsu D(n, m);
        vector<vector<int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < 4; k++) {
                    int nx = i + dir[k][0], ny = j + dir[k][1];
                    if (0 <= nx && nx < n && 0 <= ny && ny < m && grid[i][j] == '1' && grid[nx][ny] == '1') {
                        D.merge(i, j, nx, ny);
                    }
                }
            }
        }
        set<pair<int, int>> s;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    s.insert(D.find({i, j}));
                }
            }
        }
        return s.size();
    }
};
