#include <bits/stdc++.h>
using namespace std;
// 01前缀树
struct Node {
    array<Node*, 2> children{};
    int cnt = 0; // 子树大小
};
struct Trie {
   public:
    static const int HIGH_BIT = 19; // 30int 63LL
    Node* root = new Node();
    // 添加值
    void insert(int val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (cur->children[bit] == nullptr) cur->children[bit] = new Node();
            cur = cur->children[bit];
            cur->cnt += 1;
        }
    }
    // 删除val但不删除节点, 懒删除
    // 要求val必须在trie中
    void remove(int val) {
        Node* cur = root;
        for (int i = HIGH_BIT; i >= 0; --i) {
            int bit = (val >> i) & 1;
            cur = cur->children[bit];
            cur->cnt -= 1;  // 维护大小, cnt为0视为空节点
        }
    }
    // 返回val与trie中的其中一个元素的最大异或和, 要求01前缀树不能为空
    int max_xor(int val) {
        Node* cur = root;
        int ans = 0;
        for (int i = HIGH_BIT; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (cur->children[bit ^ 1] && cur->children[bit ^ 1]->cnt) {
                ans |= 1 << i;
                bit ^= 1;
            }
            cur = cur->children[bit];
        }
        return ans;
    }
};
// 初始化, Trie t{};
// 1
