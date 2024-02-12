vector<vector<int>> d;
vector<int> up, tin;
vector<bool> was;
int time1 = 0;

vector<vector<int>> comp, tree;
vector<int> who, stack1;

void make_comp(int vertex, int q) {
    int ind = (int)comp.size();
    comp.emplace_back();
    tree.emplace_back();
    int now = -1;
    while (now != q) {
        now = stack1.back();
        comp.back().push_back(now);
        if (who[now] != -1) {
            tree[who[now]].push_back(ind);
            tree[ind].push_back(who[now]);
        }
        stack1.pop_back();
    }
    comp.back().push_back(vertex);
    if (who[vertex] == -1) {
        comp.push_back({vertex});
        tree.emplace_back();
        who[vertex] = ind+1;
    }
    tree[who[vertex]].push_back(ind);
    tree[ind].push_back(who[vertex]);
}

void DFS(int vertex, int parent) {
    tin[vertex] = up[vertex] = time1++, was[vertex] = true;
    stack1.push_back(vertex);
    for (int q : d[vertex]) {
        if (!was[q]) {
            DFS(q, vertex);
            up[vertex] = min(up[vertex], up[q]);
            if (up[q] >= tin[vertex]) {
                make_comp(vertex, q);
            }
            up[vertex] = min(up[vertex], up[q]);
        } else if (q != parent) {
            up[vertex] = min(up[vertex], tin[q]);
        }
    }
    if (parent == -1 && who[vertex] == (int)comp.size()-1) {
        tree[tree.back()[0]].pop_back();
        tree.pop_back();
        comp.pop_back();
        who[vertex] = -1;
    }
}

