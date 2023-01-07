struct Edge {
    int x, y, c, t, f;

    Edge(int x1, int y1, int c1, int t1, int f1 = 0):
        x(x1), y(y1), c(c1), t(t1), f(f1) {}
};

vector<vector<Edge>> d;
vector<vector<int>> gf;
vector<Edge> e;
vector<int> topsort;
vector<bool> was;

void top_sort(int vertex) {
    was[vertex] = true;
    for (int q : gf[vertex]) {
        Edge q1 = e[q];
        if (!was[q1.y] && q1.c-q1.f > 0) {
            top_sort(q1.y);
        }
    }
    topsort.push_back(vertex);
}

pair<bool, int> Ford_Bellman(int x, int y) {
    int n = d.size();
    vector<int> dist(n, INF), parent_edge(n, -1), push(n, -1);
    dist[x] = 0, push[x] = INF;
    was.assign(n, false), topsort = {};
    top_sort(x);
    reverse(topsort.begin(), topsort.end());
    bool flag = true;
    while (flag) {
        flag = false;
        for (int q : topsort) {
            for (int q2 : gf[q]) {
                Edge q1 = e[q2];
                if (dist[q1.y] > dist[q1.x]+q1.t && q1.c-q1.f > 0) {
                    dist[q1.y] = dist[q1.x]+q1.t, parent_edge[q1.y] = q2;
                    push[q1.y] = min(push[q1.x], q1.c-q1.f);
                    flag = true;
                }
            }
        }
    }
    if (parent_edge[y] == -1) {
        return {false, -1};
    }
    int ans = 0, x1 = push[y];
    if (parent_edge[y] != -1) {
        int q2 = y;
        while (q2 != x) {
            Edge &q1 = e[parent_edge[q2]];
            q1.f += x1, e[parent_edge[q2] ^ 1].f -= x1, ans += q1.t*x1;
            q2 = q1.x;
        }
    }
    return {true, ans};
}

int min_cost(int x, int y) {
    int n = d.size();
    gf.assign(n, {}), e = {};
    for (int q = 0; q < n; q++) {
        for (Edge q1 : d[q]) {
            gf[q1.x].push_back(e.size());
            e.push_back(Edge(q1.x, q1.y, q1.c, q1.t));
            gf[q1.y].push_back(e.size());
            e.push_back(Edge(q1.y, q1.x, 0, -q1.t));
        }
    }
    int ans = 0;
    while (true) {
        pair<bool, int> x1 = Ford_Bellman(x, y);
        if (!x1.first) {
            break;
        }
        ans += x1.second;
    }
    return ans;
}
