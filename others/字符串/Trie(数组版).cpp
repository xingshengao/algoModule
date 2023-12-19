class Trie {
    int t[100000][26], cnt = 0, cnt_pre[100000], cnt_word[100000];
public:
    Trie() {
        memset(t, 0, sizeof t);
        memset(cnt_pre, 0, sizeof cnt_pre);
        memset(cnt_word, 0, sizeof cnt_word);
        cnt = 0;
    }
    
    void insert(string word) {  // 插入word
        int now = 0;
        for (int i = 0; i < word.size(); i++) {
            if (!t[now][word[i] - 'a']) t[now][word[i] - 'a'] = ++cnt;
            now = t[now][word[i] - 'a'];
            cnt_pre[now]++;
        }
        cnt_word[now]++;
    }
    
    int countWordsEqualTo(string word) {    // 求word个数
        int now = 0;
        for (int i = 0; i < word.size(); i++) {
            if (!t[now][word[i] - 'a']) t[now][word[i] - 'a'] = ++cnt;
            now = t[now][word[i] - 'a'];
        }
        return cnt_word[now];
    }
    
    int countWordsStartingWith(string word) {   // 求以word为前缀的个数
        int now = 0;
        for (int i = 0; i < word.size(); i++) {
            if (!t[now][word[i] - 'a']) t[now][word[i] - 'a'] = ++cnt;
            now = t[now][word[i] - 'a'];
        }
        return cnt_pre[now];
    }
    
    void erase(string word) {   // 删除一个word
        int now = 0;
        for (int i = 0; i < word.size(); i++) {
            if (!t[now][word[i] - 'a']) t[now][word[i] - 'a'] = ++cnt;
            now = t[now][word[i] - 'a'];
            cnt_pre[now]--;
        }
        cnt_word[now]--;
    }
};
