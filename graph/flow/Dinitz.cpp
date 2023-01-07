struct Edge {
    int x, y, c, f;

    Edge(int x1, int y1, int c1, int f1 = 0): x(x1), y(y1), c(c1), f(f1) {}
};

vector<vector<Edge>> d;
vector<vector<int>> gf;
vector<Edge> e;
vector<bool> was;

int push(int vertex, int x, int y) {
    if (vertex == y) {
        return x;
    }
    was[vertex] = true;
    for (int q : gf[vertex]) {
        Edge &q1 = e[q];
        if (!was[q1.y] && q1.c-q1.f > 0) {
            int x1 = push(q1.y, min(x, q1.c-q1.f), y);
            if (x1 != -1) {
                q1.f += x1, e[q ^ 1].f -= x1;
                return x1;
            }
        }
    }
    return -1;
}

int BFS(int x, int y) {
    int n = d.size();
    vector<int> dist(n, INF);
    queue<int> a;
    a.push(x);
    dist[x] = 0;
    while (!a.empty()) {
        int q = a.front();
        a.pop();
        if (q == y) {
            break;
        }
        for (int q2 : gf[q]) {
            Edge &q1 = e[q2];
            if (dist[q1.y] == INF && q1.c-q1.f > 0) {
                a.push(q1.y);
                dist[q1.y] = dist[q]+1;
            }
        }
    }
    vector<vector<int>> gf_const = gf;
    gf.assign(n, {});
    for (int q = 0; q < e.size(); q++) {
        if (dist[e[q].x]+1 == dist[e[q].y]) {
            gf[e[q].x].push_back(q);
        }
    }
    int ans = -(dist[y] == INF);
    while (true) {
        was.assign(n, false);
        int x1 = push(x, INF, y);
        if (x1 == -1) {
            break;
        }
        ans += x1;
    }
    gf = gf_const;
    return ans;
}

int flow(int x, int y) {
    int n = d.size();
    gf.assign(n, {}), e = {};
    for (int q = 0; q < n; q++) {
        for (Edge q1 : d[q]) {
            gf[q1.x].push_back(e.size());
            e.push_back(Edge(q1.x, q1.y, q1.c));
            gf[q1.y].push_back(e.size());
            e.push_back(Edge(q1.y, q1.x, 0));
        }
    }
    int ans = 0;
    while (true) {
        was.assign(n, false);
        int x1 = BFS(x, y);
        if (x1 == -1) {
            break;
        }
        ans += x1;
    }
    return ans;
}

