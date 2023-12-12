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
class Solution {
   public:
    int maxPerformance(int n, vector<int>& s, vector<int>& e, int k) {  // 速度, 效率
        LL ans = 0;
        typedef pair<LL, LL> PLL;
        // 优先队列
        priority_queue<PLL, vector<PLL>, greater<PLL>> pq;  // 小顶堆, 维护最大的k个速度
        // 效率降序排序
        vector<PLL> vec(n);
        for (int i = 0; i < n; ++i) {
            vec[i] = PLL(s[i], e[i]);
        }
        LL sum = 0;  // 速度和
        sort(vec.begin(), vec.end(), [&](const auto& a, const auto& b) { return a.second > b.second; });
        for (int i = 0; i < n; ++i) {
            // 当前节点为最小效率
            pq.push(vec[i]);
            sum += vec[i].first;
            if (pq.size() > k) {
                sum -= pq.top().first;
                pq.pop();
            }
            if (pq.size() <= k) {
                ans = max(ans, sum * vec[i].second);
            }
        }
        return ans;
    }
};
int main() {
    // Solotion so;
    return 0;
}