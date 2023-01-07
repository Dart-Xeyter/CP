struct DSU {
    vector<int> size, parent;

    DSU(int n) {
        size.assign(n, 1), parent.assign(n, -1);
        iota(parent.begin(), parent.end(), 0);
    }

    int root(int x) {
        vector<int> a;
        while (x != parent[x]) {
            a.push_back(x);
            x = parent[x];
        }
        for (int q : a) {
            parent[q] = x;
        }
        return x;
    }

    bool merge(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        size[x] += size[y], parent[y] = x;
        return true;
    }
};

vector<vector<p>> d;

int Kruskal() {
    int n = (int)d.size();
    vector<pair<p, int>> edges;
    for (int q = 0; q < n; q++) {
        for (p q1 : d[q]) {
            edges.push_back({{q, q1.first}, q1.second});
        }
    }
    int ans = 0;
    sort(edges.begin(), edges.end(), [](pair<p, int> x, pair<p, int> y){return x.second < y.second;});
    DSU dsu = DSU(n);
    for (pair<p, int> q: edges) {
        int x = dsu.root(q.first.first), y = dsu.root(q.first.second);
        if (x != y) {
            dsu.merge(x, y);
            ans += q.second;
        }
    }
    int root = dsu.root(0);
    for (int q = 0; q < n; q++) {
        if (dsu.root(q) != root) {
            return INF;
        }
    }
    return ans;
}
