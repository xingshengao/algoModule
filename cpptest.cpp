#include <bits/stdc++.h>

using namespace std;
using LL = long long;
const double PI = acos(-1);
#define all(c) c.begin(), c.end()
typedef pair<long long, long long> PLL;
typedef pair<int, int> PII;
vector<pair<int, int>> dirs8 = {{-1, -1}, {-1, 1}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {1, 0}};
long long fpow(long long x, long long exp) {  // 快速幂
    long long res = 1;
    for (; exp; exp /= 2) {
        if (exp & 1) res = res * x % mod;
        x = x * x % mod;
    }
    return res;
}
string to_string(string s) { return '"' + s + '"'; }

string to_string(const char* s) { return to_string((string)s); }

string to_string(bool b) { return (b ? "true" : "false"); }

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto& x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

void debug_out() { cout << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cout << " " << to_string(H);
    debug_out(T...);
}

template <typename T>
void mydebug(const char* format, T t) {
    cout << format << "=" << to_string(t) << endl;
}

template <typename Head, typename... Tail>
void mydebug(const char* format, Head H, Tail... T) {
    while (*format != ',') cout << *format++;
    cout << "=" << to_string(H) << ",";
    mydebug(format + 1, T...);
}
#define debug(...) mydebug(#__VA_ARGS__, __VA_ARGS__)

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
typedef pair<int, int> PII;
static constexpr long long mod = 1e9 + 7;
using LL = long long;
// Tarjan算法求无向图中的强连通分量
class Solution {
   public:
    int time;                 // 时间戳
    vector<vector<int>> adj;  // 邻接表
    vector<int> dfn;          // 节点的时间戳
    vector<int> low;          // 节点的追溯值
    vector<bool> vis;         // 是否遍历过节点
    int cnt;                  // 强连通分量的数量
    vector<vector<int>> ans;  //  存强连通分量
    void tarjan(int u, int fa) {
        time++;
        dfn[u] = time;
        low[u] = time;
        vis[u] = 1;

        for (int v : adj[u]) {
            if (v == fa) continue;
            if (!vis[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                // 说明找到了一条强连通分量
                if (low[v] > dfn[u]) {
                    ans.push_back({u, v});
                    cnt += 1;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // 初始化工具人数组
        time = 0;
        adj = vector<vector<int>>(n);
        dfn = vector<int>(n, 0);
        low = vector<int>(n, 0);
        vis = vector<bool>(n, false);
        cnt = 0;
        // 建图
        for (auto& e : connections) {
            int x = e[0], y = e[1];
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        tarjan(0, -1);
        return ans;
    }
};
int main() {
    // Solotion so;
    return 0;
}