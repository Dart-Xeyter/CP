struct Edge {
    int x, y, c, f;
};

struct Flow {
    vector<vector<int>> gf;
    vector<Edge> edges;

    explicit Flow(int n) {
        gf.assign(n, {});
    }

    void add_edge(int x, int y, int c, bool directed) {
        gf[x].push_back((int)edges.size());
        edges.emplace_back(x, y, c, 0);
        gf[y].push_back((int)edges.size());
        edges.emplace_back(y, x, (1-directed)*c, 0);
    }

    vector<int> layer, ind;

    bool build_layers(int x, int y) {
        layer.assign(gf.size(), -1);
        ind.assign(gf.size(), 0);
        queue<int> a;
        a.push(x);
        layer[x] = 0;
        while (!a.empty()) {
            int q = a.front();
            if (q == y) {
                return true;
            }
            a.pop();
            for (int q1_ : gf[q]) {
                Edge& q1 = edges[q1_];
                if (q1.c == q1.f) {
                    continue;
                }
                if (layer[q1.y] == -1) {
                    a.push(q1.y);
                    layer[q1.y] = layer[q1.x]+1;
                }
            }
        }
        return layer[y] != -1;
    }

    int push(int x, int y, int min1) {
        if (x == y) {
            return min1;
        }
        int ans = 0;
        for (; ind[x] < gf[x].size(); ind[x]++) {
            int num = gf[x][ind[x]];
            Edge& q = edges[num];
            if (layer[q.y] != layer[q.x]+1 || q.f == q.c) {
                continue;
            }
            int pushed = push(q.y, y, min(min1, q.c-q.f));
            edges[num].f += pushed;
            edges[num ^ 1].f -= pushed;
            ans += pushed, min1 -= pushed;
            if (min1 == 0) {
                return ans;
            }
        }
        return ans;
    }

    void build_flow(int x, int y) {
        while (build_layers(x, y)) {
            push(x, y, INF);
        }
    }

    int max_flow(int x, int y) {
        build_flow(x, y);
        int ans = 0;
        for (int q : gf[x]) {
            ans += edges[q].f;
        }
        return ans;
    }
};

