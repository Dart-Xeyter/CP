vector<vector<int>> d;
vector<p> order_num;
vector<int> num_vertex, right_num;
vector<bool> s_renum;

void DFS_num(int vertex) {
    s_renum[vertex] = false;
    order_num.emplace_back(order_num.size(), vertex);
    for (int q : d[vertex]) {
        if (s_renum[q]) {
            DFS_num(q);
        }
    }
}

void renumbering() {
    int n = d.size();
    s_renum.assign(n, true);
    for (int q = 0; q < n; q++) {
        if (s_renum[q]) {
            DFS_num(0);
        }
    }
    num_vertex.assign(n, -1), right_num.assign(n, -1);
    for (int q = 0; q < n; q++) {
        num_vertex[order_num[q].second] = q;
        right_num[q] = order_num[q].second;
    }
    vector<vector<int>> d1_renum(n);
    for (int q = 0; q < n; q++) {
        for (int q1 : d[q]) {
            d1_renum[num_vertex[q]].push_back(num_vertex[q1]);
        }
    }
    d = d1_renum;
}
