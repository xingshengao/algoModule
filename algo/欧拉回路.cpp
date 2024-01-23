// 通过图中所有边恰好一次且行遍所有顶点的通路称为欧拉通路；
// 通过图中所有边恰好一次且行遍所有顶点的回路称为欧拉回路；
// 具有欧拉回路的无向图称为欧拉图；
// 具有欧拉通路但不具有欧拉回路的无向图称为半欧拉图

// Hierholzer 算法
// 也称逐步插入回路法。
// 算法流程为从一条回路开始，每次任取一条目前回路中的点，将其替换为一条简单回路，
// 以此寻找到一条欧拉回路。如果从路开始的话，就可以寻找到一条欧拉路。
// 过程:
// 从起点出发，进行深度优先搜索。
// 每次沿着某条边从某个顶点移动到另外一个顶点的时候，都需要删除这条边。
// 如果没有可移动的路径，则将所在节点加入到栈中，并返回
#include <bits/stdc++.h>
using namespace std;

// 给定一个有向图, 求出欧拉回路, 保证存在
template <typename T>
vector<T> Hierholzer(vector<vector<T>>& edges, T start) {
    // 建图, 边全职的小顶堆
    unordered_map<T, priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>>> G;
    vector<T> stk;
    for (auto& e : edges) {
        T u = e[0], v = e[1], w = e[2];
        G[u].emplace(w, v);  // 有一条u到v的权值为w的边
    }

    function<void(T)> dfs = [&](T node) {
        while (G.count(node) and G[node].size() > 0) {
            T tmp = G[node].top().second;
            G[node].pop();
            dfs(tmp);
        }
        stk.push_back(node);
    };

    // 假定起点了
    dfs(start);
    reverse(stk.begin(), stk.end());
    return stk;
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& obj) {
    out << "vector(";
    for (auto it = obj.begin(); it != obj.end(); it++) out << (it == obj.begin() ? "" : ", ") << *it;
    out << ")";
    return out;
}
// 使用举例子
int main() {
    // Solution so;
    vector<vector<int>> edges = {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}};
    vector<int> ans = Hierholzer(edges, 0);
    cout << ans << endl;
    return 0;
}

// 332. 重新安排行程

// 给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi] 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。

// 所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。

// 例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。
// 假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次
// 简化题意, 一笔画问题

class Solution_ {
   public:
    // 以小顶堆的形式建图
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> G;
    vector<string> st;

    void dfs(string cur) {
        while (G.count(cur) and G[cur].size() > 0) {
            string tmp = G[cur].top();
            G[cur].pop();
            dfs(tmp);
        }
        st.push_back(cur);
    }
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& e : tickets) {  // 建图
            G[e[0]].emplace(e[1]);
        }
        dfs("JFK");
        reverse(st.begin(), st.end());
        return st;
    }
};
