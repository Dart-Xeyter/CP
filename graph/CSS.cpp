vector<vector<int>> d, d1, cond, comp;
vector<int> who, topsort;
vector<bool> was;

void top_sort(int vertex) {
    was[vertex] = true;
    for (int q : d[vertex]) {
        if (!was[q]) {
            top_sort(q);
        }
    }
    topsort.push_back(vertex);
}

void DFS_CSS(int vertex) {
    was[vertex] = true, who[vertex] = (int)comp.size()-1;
    comp.back().push_back(vertex);
    for (int q : d1[vertex]) {
        if (!was[q]) {
            DFS_CSS(q);
        } else if (who[q] != who[vertex]) {
            cond[who[q]].push_back(who[vertex]);
        }
    }
}

void CSS() {
    int n = d.size();
    d1.assign(n, {}), comp = {}, cond = {}, who.assign(n, -1), topsort = {}, was.assign(n, false);
    for (int q = 0; q < n; q++) {
        if (!was[q]) {
            top_sort(q);
        }
        for (int q1 : d[q]) {
            d1[q1].push_back(q);
        }
    }
    reverse(topsort.begin(), topsort.end());
    was.assign(n, false);
    for (int q : topsort) {
        if (!was[q]) {
            comp.emplace_back(), cond.emplace_back();
            DFS_CSS(q);
        }
    }
}

