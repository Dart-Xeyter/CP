int Boruvka(vector<int> &a, int m) {
    int n = a.size();
    vector<vector<int>> comp(n);
    set<p> s, all;
    vector<int> who(n);
    for (int q = 0; q < n; q++) {
        s.insert({1, q});
        all.insert({a[q], q});
        who[q] = q, comp[q] = {q};
    }
    int ans = 0;
    for (int q11 = 0; q11 < n-1; q11++) {
        p min1 = *s.begin();
        s.erase(min1);
        int x = who[min1.second];
        for (int q : comp[x]) {
            all.erase({a[q], q});
        }
        int now = INF, y;
        for (int q : comp[x]) {
            auto w = all.begin(), w1 = all.lower_bound({m-a[q], -INF});
            if (w->first+a[q] < now) {
                now = w->first+a[q], y = who[w->second];
            }
            if (w1 != all.end() && w1->first+a[q]-m < now) {
                now = w1->first+a[q]-m, y = who[w1->second];
            }
        }
        for (int q : comp[x]) {
            all.insert({a[q], q});
        }
        s.erase({comp[y].size(), y});
        for (int q : comp[x]) {
            comp[y].push_back(q);
            who[q] = y;
        }
        s.insert({comp[y].size(), y});
        ans += now;
    }
    return ans;
}
