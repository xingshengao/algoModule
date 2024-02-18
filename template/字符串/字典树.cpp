#include <bits/stdc++.h>
using namespace std;
// 字典树
// 数组存储
struct trie {
    int nex[100000][26], cnt;
    bool exist[100000];  // 该结点结尾的字符串是否存在

    void insert(char* s, int l) {  // 插入字符串
        int p = 0;
        for (int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            if (!nex[p][c]) nex[p][c] = ++cnt;  // 如果没有，就添加结点
            p = nex[p][c];
        }
        exist[p] = 1;
    }

    bool find(char* s, int l) {  // 查找字符串
        int p = 0;
        for (int i = 0; i < l; i++) {
            int c = s[i] - 'a';
            if (!nex[p][c]) return 0;
            p = nex[p][c];
        }
        return exist[p];
    }
};

// 指针实现
class Trie {
   public:
    Trie* son[26];
    bool isEnd;
    Trie() {
        memset(son, 0, sizeof(son));
        isEnd = false;
    }

    void insert(string word) {
        auto cur = this;
        for (auto c : word) {
            int i = c - 'a';
            if (!cur->son[i]) {
                cur->son[i] = new Trie();
            }
            cur = cur->son[i];
        }
        cur->isEnd = true;
    }

    bool search(string word) {
        auto cur = this;
        for (auto c : word) {
            int i = c - 'a';
            if (cur->son[i] == nullptr) {
                return false;
            }
            cur = cur->son[i];
        }
        return cur->isEnd;
    }

    bool startsWith(string prefix) {
        auto cur = this;
        for (char c : prefix) {
            int i = c - 'a';
            if (!cur->son[i]) return false;
            cur = cur->son[i];
        }
        return true;
    }
};

int main() {
    Trie tr;
    int t;
    cout << "input the number of strings:\n";
    cin >> t;
    while (t--) {
        cout << "input the string:\t";
        string str;
        cin >> str;
        tr.insert(str);
    }
    string input;
    cout << "input the string you want to input:\n";
    cin >> input;
    cout << tr.search(input);
    return 0;
}