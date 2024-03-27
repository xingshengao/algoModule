#include <bits/stdc++.h>
using LL = long long;
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 前序
class Solution1 {  // 前序遍历, 迭代法
   public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return {};
        stack<TreeNode*> st;
        st.push(root);
        while (st.size()) {
            auto node = st.top();
            st.pop();
            ans.push_back(node->val);
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
        return ans;
    }
};

// 中序
class Solution {  // 中序遍历迭代法, 尽可能把左子树存进去
   public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) return {};
        stack<TreeNode*> st;
        auto cur = root;
        while (st.size() or cur != nullptr) {
            while (cur != nullptr) {
                st.push(cur);
                cur = cur->left;
            }
            auto node = st.top();
            st.pop();
            ans.push_back(node->val);
            if (node->right) cur = node->right;
        }
        return ans;
    }
};

// 后序
class Solution {  // 后序遍历迭代法
   public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr) return {};
        vector<int> ans;
        // 后序就是类似前序倒过来, RL -> LR
        stack<TreeNode*> st;
        st.push(root);
        while (st.size()) {
            auto node = st.top();
            st.pop();
            ans.push_back(node->val);
            if (node->left) st.push(node->left);
            if (node->right) st.push(node->right);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};