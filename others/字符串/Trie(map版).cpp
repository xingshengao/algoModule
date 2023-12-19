// https://www.luogu.com.cn/problem/P8306
#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct Trie {

    map<char, Trie*> son;
    map<char, int> cnt_pre;
    map<char, int> cnt_word;

    Trie() {}

    void insert(string word) {  // 插入word
        char c;
        Trie* now = this;
        for (int i = 0; i < word.size(); i++) {
            c = word[i];
            if (now->son.count(c) == 0) {
                now->son[c] = new Trie();
            }
            now = now->son[c];
            now->cnt_pre[c]++;
        }
        now->cnt_word[c]++;
    }

    int countWordsEqualTo(string word) {    // 求word个数
        char c;
        Trie* now = this;
        for (int i = 0; i < word.size(); i++) {
            c = word[i];
            if (now->son.count(c) == 0) {
                now->son[c] = new Trie();
            }
            now = now->son[c];
        }
        return now->cnt_word[c];
    }

    int countWordsStartingWith(string word) {   // 求以word为前缀的个数
        char c;
        Trie* now = this;
        for (int i = 0; i < word.size(); i++) {
            c = word[i];
            if (now->son.count(c) == 0) {
                now->son[c] = new Trie();
            }
            now = now->son[c];
        }
        return now->cnt_pre[c];
    }

    void erase(string word) {   // 删除一个word
        char c;
        Trie* now = this;
        for (int i = 0; i < word.size(); i++) {
            c = word[i];
            if (now->son.count(c) == 0) {
                now->son[c] = new Trie();
            }
            now = now->son[c];
            now->cnt_pre[c]--;
        }
        now->cnt_word[c]--;
    }

};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        Trie T;
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            T.insert(s);
        }
        for (int i = 0; i < q; i++) {
            string s;
            cin >> s;
            cout << T.countWordsStartingWith(s) << endl;
        }
    }
}