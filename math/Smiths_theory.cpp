vector<vector<int>> get_graph() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d(n);
    for (int q = 0; q < m; q++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        d[x].push_back(y);
    }
    return d;
}

vector<int> get_smith(vector<vector<int>> &d) {
    int n = (int)d.size();
    vector<vector<int>> d1(n);
    for (int q = 0; q < n; q++) {
        for (int q1 : d[q]) {
            d1[q1].push_back(q);
        }
    }
    vector<int> smith(n, -1), all(n);
    iota(all.begin(), all.end(), 0);
    bool continue1 = true;
    for (int nim = 0; continue1; nim++) {
        continue1 = false;
        vector<int> num(n, 0);
        for (int q : all) {
            for (int q1 : d[q]) {
                num[q] += (smith[q1] == -1);
            }
        }
        vector<p> is;
        vector<bool> is_move(n, false), is_now(n, false);
        for (int q : all) {
            is.emplace_back(num[q], q);
            is_now[q] = true;
        }
        sort(is.rbegin(), is.rend());
        vector<int> ind(n);
        for (int q = 0; q < is.size(); q++) {
            ind[is[q].second] = q;
        }
        all = {};
        while (!is.empty() && is.back().first == 0) {
            continue1 = true;
            int vertex = is.back().second;
            is.pop_back();
            if (!is_now[vertex]) {
                continue;
            }
            is_now[vertex] = false, smith[vertex] = nim;
            for (int q : d1[vertex]) {
                if (is_move[q] || smith[q] != -1) {
                    continue;
                }
                if (is_now[q]) {
                    all.push_back(q);
                    is_now[q] = false;
                }
                is_move[q] = true;
                for (int q1 : d1[q]) {
                    if (!is_now[q1]) {
                        continue;
                    }
                    auto w = lower_bound(is.rbegin(), is.rend(), p(num[q1], -INF));
                    auto w1 = is.rbegin()+(int)is.size()-ind[q1]-1;
                    w1->first--, num[q1]--;
                    swap(*w, *w1);
                    swap(ind[w->second], ind[w1->second]);
                }
            }
        }
    }
    return smith;
}

int sum_games_result(vector<vector<int>> &d1, vector<vector<int>> &d2, vector<int> &smith1, vector<int> &smith2, int x, int y) {
    if (smith1[x] == -1 && smith2[y] == -1) {
        return -1;
    }
    if (smith1[x] != -1 && smith2[y] != -1) {
        return (smith1[x] ^ smith2[y]) == 0;
    }
    bool was_swap = false;
    if (smith1[x] != -1) {
        swap(d1, d2);
        swap(smith1, smith2);
        was_swap = true;
        swap(x, y);
    }
    bool flag = false;
    for (int q : d1[x]) {
        flag |= (smith1[q] == smith2[y]);
    }
    if (was_swap) {
        swap(d1, d2);
        swap(smith1, smith2);
    }
    return flag-1;
}

