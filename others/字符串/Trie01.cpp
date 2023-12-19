// https://leetcode.cn/problems/maximum-xor-of-two-numbers-in-an-array/
// https://www.luogu.com.cn/problem/CF817E
#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

struct Trie01 {

    // 左子树指向表示 0 的子节点
    Trie01* left = NULL;
    // 右子树指向表示 1 的子节点
    Trie01* right = NULL;
    // 最高位的二进制位编号为 30
    static constexpr int HIGH_BIT = 30;
    // 当前节点的个数
    int cnt = 0;

    Trie01() {}

    void insert(int x) {  // 插入x
        Trie01* cur = this;
        for (int k = HIGH_BIT; k >= 0; k--) {
            int b = x >> k & 1;
            if (b == 0) {
                if (!cur->left) {
                    cur->left = new Trie01();
                }
                cur->left->cnt++;
                cur = cur->left;
            } else {
                if (!cur->right) {
                    cur->right = new Trie01();
                }
                cur->right->cnt++;
                cur = cur->right;
            }
        }
    }

    void del(int x) {   // 删除一个x
        Trie01* cur = this;
        for (int k = HIGH_BIT; k >= 0; k--) {
            int b = x >> k & 1;
            if (b == 0) {
                cur->left->cnt--;
                cur = cur->left;
            } else {
                cur->right->cnt--;
                cur = cur->right;
            }
        }
    }

    int query_xor_max(int x) {    // 计算字典树中和x异或后最大的值(询问前字典树中必须存在数, 不然会报空指针)
        Trie01* cur = this;
        int res = 0;
        for (int k = HIGH_BIT; k >= 0; k--) {
            int bit = x >> k & 1;
            if (bit == 0) {
                // a_i 的第 k 个二进制位为 0，应当往表示 1 的子节点 right 走
                if (cur->right && cur->right->cnt) {
                    cur = cur->right;
                    res = res * 2 + 1;
                } else {
                    cur = cur->left;
                    res = res * 2;
                }
            } else {
                // a_i 的第 k 个二进制位为 1，应当往表示 0 的子节点 left 走
                if (cur->left && cur->left->cnt) {
                    cur = cur->left;
                    res = res * 2 + 1;
                } else {
                    cur = cur->right;
                    res = res * 2;
                }
            }
        }
        return res;
    }

    int query_xor_less(int x, int y) {    // 计算字典树中和x异或后小于y的数有几个
        Trie01* cur = this;
        int res = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int xx = x >> i & 1, yy = y >> i & 1;
            if (yy == 0) {
                if (xx == 0) {
                    if (cur->left == NULL) break;
                    cur = cur->left;
                } else {
                    if (cur->right == NULL) break;
                    cur = cur->right;
                }
            } else {
                if (xx == 0) {
                    if (cur->left) res += cur->left->cnt;
                    if (cur->right == NULL) break;
                    cur = cur->right;
                } else {
                    if (cur->right) res += cur->right->cnt;
                    if (cur->left == NULL) break;
                    cur = cur->left;
                }
            }
        }
        return res;
    }

    int query_xor_kth(int x, int k) {    // 计算字典树中和x异或后第k大的值
        Trie01* cur = this;
        int res = 0;
        for (int i = HIGH_BIT; i >= 0; i--) {
            int b = x >> i & 1;
            if (b == 1) {
                if (cur->left) {
                    if (k <= cur->left->cnt) {
                        res |= 1LL << i;
                        cur = cur->left;
                    } else {
                        k -= cur->left->cnt;
                        cur = cur->right;
                    }
                } else {
                    cur = cur->right;
                }
            } else {
                if (cur->right) {
                    if (k <= cur->right->cnt) {
                        res |= 1LL << i;
                        cur = cur->right;
                    } else {
                        k -= cur->right->cnt;
                        cur = cur->left;
                    }
                } else {
                    cur = cur->left;
                }
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
    int q;
    cin >> q;
    Trie01 T;
    while (q--) {
        int op, p, l;
        cin >> op;
        if (op == 1) {
            cin >> p;
            T.insert(p);
        } else if (op == 2) {
            cin >> p;
            T.del(p);
        } else {
            cin >> p >> l;
            cout << T.query_xor_less(p, l) << endl;
        }
    }
    return 0;
}
