struct Edge {
    int x, y, c, f = 0;
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

bool cancel_way(int vertex, int y) {
    if (vertex == y) {
        return true;
    }
    was[vertex] = true;
    for (int q : gf[vertex]) {
        Edge &q1 = e[q];
        if (!was[q1.y] && q1.f > 0 && cancel_way(q1.y, y)) {
            q1.f--, e[q ^ 1].f++;
            return true;
        }
    }
    return false;
}

void cancel(int ind, int x, int y) {
    if (e[ind].f == 0) {
        return;
    }
    e[ind].c--, e[ind].f--;
    was.assign(d.size(), false);
    assert(cancel_way(x, e[ind].x));
    was.assign(d.size(), false);
    assert(cancel_way(e[ind].y, y));
}

void build_flow() {
    int n = (int)d.size();
    gf.assign(n, {}), e = {};
    for (int q = 0; q < n; q++) {
        for (Edge q1 : d[q]) {
            gf[q1.x].push_back((int)e.size());
            e.emplace_back(q1.x, q1.y, q1.c);
            gf[q1.y].push_back((int)e.size());
            e.emplace_back(q1.y, q1.x, 0);
        }
    }
}

int max_flow(int x, int y) {
    int n = (int)d.size();
    int size = 0;
    while (size != -1) {
        was.assign(n, false);
        size = push(x, INF, y);
    }
    int ans = 0;
    for (int q : gf[x]) {
        ans += e[q].f;
    }
    return ans;
}

