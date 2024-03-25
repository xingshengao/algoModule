#include <bits/stdc++.h>
using namespace std;
/**
 * @link https://github.com/nealwu/competitive-programming/blob/master/strings/trie.cc
*/
template <char MIN_CHAR = 'a', int ALPHABET = 26>
struct array_trie {
    struct trie_node {
        array<int, ALPHABET> child;
        int words_here = 0, starting_with = 0;
        int id = 1000, length = 1e6; // id第几个字符串，length最短的长度
        trie_node() { memset(&child[0], -1, ALPHABET * sizeof(int)); }
    };

    static const int ROOT = 0;

    vector<trie_node> nodes = {trie_node()};

    array_trie(int total_length = -1) {
        if (total_length >= 0)
            nodes.reserve(total_length + 1);
    }

    int get_or_create_child(int node, int c) {
        if (nodes[node].child[c] < 0) {
            nodes[node].child[c] = int(nodes.size());
            nodes.emplace_back();
        }
        return nodes[node].child[c];
    }

    int build(const string& word, int delta, int now) {
        int node = ROOT;
        if (nodes[node].length > word.size()) {
            nodes[node].id = now;
            nodes[node].length = word.size();
        }
        for (char ch : word) {
            nodes[node].starting_with += delta;
            node = get_or_create_child(node, ch - MIN_CHAR);
            // 更新node信息
            if (nodes[node].length > word.size()) {
                nodes[node].id = now;
                nodes[node].length = word.size();
            }
        }

        nodes[node].starting_with += delta;
        return node;
    }

    int add(const string& word, int now) {
        int node = build(word, +1, now);
        nodes[node].words_here++;
        return node;
    }


    int find(const string& str) const {
        int node = ROOT;

        for (char ch : str) {
            if (nodes[node].child[ch - MIN_CHAR] < 0)
                break;
            node = nodes[node].child[ch - MIN_CHAR];
        }

        return node;
    }
};
class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        vector<int> ans;
        array_trie trie;
        for (int i = 0; i < wordsContainer.size(); i++) {
            reverse(wordsContainer[i].begin(), wordsContainer[i].end());
            trie.add(wordsContainer[i], i);
        }
        for (auto &w : wordsQuery) {
            reverse(w.begin(), w.end());
            int node = trie.find(w);
            // cout << w << endl;
            // cout << node << endl;
            ans.push_back(trie.nodes[node].id);
        }
        return ans;
    }
};