struct Edge {
    int x, y, num;

    Edge(int x1, int y1, int num1): x(x1), y(y1), num(num1) {}
};

bool operator<(Edge edge, Edge edge1) {
    return edge.num < edge1.num;
}

vector<vector<Edge>> d;
vector<int> tin, up;
vector<bool> was;
int time1 = 0;
set<Edge> bridge;

void bridges(int vertex, int num) {
    tin[vertex] = up[vertex] = time1++, was[vertex] = true;
    for (Edge q : d[vertex]) {
        if (!was[q.y]) {
            bridges(q.y, q.num);
            up[vertex] = min(up[vertex], up[q.y]);
            if (up[q.y] > tin[vertex]) {
                bridge.insert(q);
            }
        } else if (q.num != num) {
            up[vertex] = min(up[vertex], tin[q.y]);
        }
    }
}

vector<vector<pair<int, p>>> d1;
vector<vector<int>> comp;
vector<p> num;

void cond(int vertex, int now) {
    was[vertex] = false, num[vertex] = {now, comp[now].size()};
    comp[now].push_back(vertex);
    for (Edge q: d[vertex]) {
        if (!was[q.y] && bridge.find(q) != bridge.end()) {
            cond(q.y, now);
        } else if (!was[q.y]) {
            d1.emplace_back();
            d1[now].push_back({comp.size(), {q.x, q.y}});
            d1[comp.size()].push_back({now, {q.y, q.x}});
            comp.emplace_back();
            cond(q.y, (int)comp.size()-1);
        }
    }
}
