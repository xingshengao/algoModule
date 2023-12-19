struct Top_sort {
    
    unordered_map<int, unordered_set<int>> g;
    unordered_map<int, int> cnt;

    void add(int a, int b) {    // 添加一条从a指向b的有向边
        if (g[a].count(b)) return;
        g[a].insert(b);
        cnt[a] += 0;
        cnt[b] += 1;
    }

    vector<int> get_topsort() { // 获取任意的一条拓扑序列。若无法生成，则返回空数组
        vector<int> res;
        deque<int> q;
        for (auto [x, y] : cnt) {
            if (y == 0) q.push_back(x);
        }
        while (q.size()) {
            int now = q.front();
            q.pop_front();
            res.push_back(now);
            for (int nxt : g[now]) {
                cnt[nxt]--;
                if (cnt[nxt] == 0) q.push_back(nxt);
            }
        }
        if (res.size() != cnt.size()) return {};
        return res;
    }
};