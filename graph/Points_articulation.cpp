vector<vector<int>> d, comp;
vector<int> tin, up;
vector<pair<int, bool>> bypass;
int time1;

void build_comp(int vertex) {
    comp.push_back({vertex});
    while (bypass.back().first != vertex) {
        if (bypass.back().second) {
            comp.back().push_back(bypass.back().first);
        }
        bypass.pop_back();
    }
}

void DFS_articulation(int vertex, int parent) {
    tin[vertex] = up[vertex] = time1++;
    bypass.emplace_back(vertex, true);
    for (int q : d[vertex]) {
        if (tin[q] == -1) {
            bypass.emplace_back(vertex, false);
            DFS_articulation(q, vertex);
            if (up[q] >= tin[vertex]) {
                build_comp(vertex);
            }
            up[vertex] = min(up[vertex], up[q]);
        } else if (q != parent) {
            up[vertex] = min(up[vertex], tin[q]);
        }
    }
}

vector<vector<int>> g;

int make_articulation(int n) {
    tin.assign(n, -1), up.assign(n, -1);
    comp = {}, bypass = {}, time1 = 0;
    DFS_articulation(0, -1);
    int k = (int)comp.size();
    g.assign(n+k, {});
    for (int q = 0; q < k; q++) {
        for (int q1 : comp[q]) {
            g[q+n].push_back(q1);
            g[q1].push_back(q+n);
        }
    }
    return k;
}

