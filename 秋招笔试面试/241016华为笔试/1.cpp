#include <bits/stdc++.h>
#define int long long
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* makeBST(vector<int>& nums, int left, int right) {
    if (left  > right) return  NULL;
    
    int mid = left  + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    
    root->left = makeBST(nums, left, mid -  1);
    root->right = makeBST(nums, mid + 1, right);
    
    return root;
}

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) cin >> arr[i];
    
    int k; // 个数
    int L, R;
    cin >> k >> L >> R;
    sort(arr.begin(), arr.end());
    TreeNode* root = makeBST(arr, 0, arr.size() - 1);
    
    int mx = root->val;
    int ans = 0;
    
    function<void(TreeNode*)> dfs = [&](TreeNode* node) -> void {
        if (node == nullptr) return ;
        if (!node->left && !node->right) {
            mx = max(mx, node->val);
            if (node->val >= L && node->val <= R) ans += node->val;
        }
        dfs(node->left);
        dfs(node->right);
    };
    dfs(root);
    
    if (ans == 0) cout << mx << endl;
    else cout << ans <<endl;
}

signed main() {
    std::ios::sync_with_stdio(0), std::cout.tie(0), std::cin.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}