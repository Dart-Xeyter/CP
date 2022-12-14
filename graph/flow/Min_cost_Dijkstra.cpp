struct Edge {
    int x, y, c, t, f;

    Edge(int x1, int y1, int c1, int t1, int f1 = 0):
        x(x1), y(y1), c(c1), t(t1), f(f1) {}
};

vector<vector<Edge>> d;
vector<vector<int>> gf;
vector<Edge> e;
vector<int> potential;

void Dijkstra(int x) {
    int n = d.size();
    vector<int> dist(n, INF);
    vector<bool> was(n, false);
    priority_queue<p> a;
    a.push({0, x});
    dist[x] = 0;
    while (!a.empty()) {
        p q = a.top();
        swap(q.first, q.second);
        a.pop();
        if (!was[q.first]) {
            was[q.first] = true;
            for (int q2 : gf[q.first]) {
                Edge &q1 = e[q2];
                if (q1.c-q1.f > 0 && dist[q1.y] > dist[q1.x]+q1.t+potential[q1.x]-potential[q1.y]) {
                    dist[q1.y] = dist[q1.x]+q1.t+potential[q1.x]-potential[q1.y];
                    a.push({-dist[q1.y], q1.y});
                }
            }
        }
    }
    for (int q = 0; q < n; q++) {
        dist[q] -= potential[x]-potential[q];
    }
    potential = dist;
}

void Ford_Bellman(int x) {
    int n = d.size();
    vector<int> dist(n, INF);
    dist[x] = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int q = 0; q < n; q++) {
            for (int q2 : gf[q]) {
                Edge &q1 = e[q2];
                if (q1.c-q1.f > 0 && dist[q1.y] > dist[q1.x]+q1.t) {
                    dist[q1.y] = dist[q1.x]+q1.t;
                    flag = true;
                }
            }
        }
    }
    potential = dist;
}

vector<bool> was;

pair<bool, int> DFS(int vertex, int y) {
    if (vertex == y) {
        return {true, 0};
    }
    was[vertex] = true;
    for (int q2 : gf[vertex]) {
        Edge &q1 = e[q2];
        if (q1.c-q1.f > 0 && !was[q1.y] && q1.t+potential[q1.x]-potential[q1.y] == 0) {
            pair<bool, int> k = DFS(q1.y, y);
            if (k.first) {
                q1.f++, e[q2 ^ 1].f--;
                return {true, k.second+q1.t};
            }
        }
    }
    return {false, 0};
}

int min_cost(int x, int y) {
    int n = d.size();
    gf.assign(n, {}), e = {};
    for (int q = 0; q < n; q++) {
        for (Edge &q1 : d[q]) {
            gf[q1.x].push_back(e.size());
            e.push_back(Edge(q1.x, q1.y, q1.c, q1.t));
            gf[q1.y].push_back(e.size());
            e.push_back(Edge(q1.y, q1.x, 0, -q1.t));
        }
    }
    Ford_Bellman(x);
    int ans = 0;
    while (true) {
        was.assign(n, false);
        pair<bool, int> x1 = DFS(x, y);
        if (!x1.first) {
            break;
        }
        Dijkstra(x);
        ans += x1.second;
    }
    return ans;
}

