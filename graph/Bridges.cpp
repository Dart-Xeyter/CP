vector<vector<int>> d;
vector<int> tin, up;
vector<bool> was;
int time1;
set<p> bridges;

void DFS_bridges(int vertex, int parent) {
    was[vertex] = true;
    tin[vertex] = up[vertex] = time1++;
    for (int q : d[vertex]) {
        if (!was[q]) {
            DFS_bridges(q, vertex);
            up[vertex] = min(up[vertex], up[q]);
            if (up[q] > tin[vertex]) {
                bridges.emplace(vertex, q);
                bridges.emplace(q, vertex);
            }
        } else if (q != parent) {
            up[vertex] = min(up[vertex], tin[q]);
        }
    }
}

vector<vector<int>> g, comp;
vector<int> who;

void DFS_condancation(int vertex, int c) {
    was[vertex] = true, who[vertex] = c;
    comp[c].push_back(vertex);
    for (int q : d[vertex]) {
        if (!was[q] && !bridges.contains({vertex, q})) {
            DFS_condancation(q, c);
        } else if (!was[q]) {
            int new_c = (int)g.size();
            g[c].push_back(new_c);
            g.push_back({c});
            comp.emplace_back();
            DFS_condancation(q, new_c);
        }
    }
}

