struct Edge {
    int x, y, c, f, v;
};

struct Flow {
    vector<vector<int>> gf;
    vector<Edge> edges;

    explicit Flow(int n) {
        gf.assign(n, {});
    }

    void add_edge(int x, int y, int c, int v) {
        gf[x].push_back((int)edges.size());
        edges.emplace_back(x, y, c, 0, v);
        gf[y].push_back((int)edges.size());
        edges.emplace_back(y, x, 0, 0, -v);
    }

    vector<int> dists;

    void build_dists(int x) {
        int n = (int)gf.size();
        dists.assign(n, INF);
        vector<bool> taken(n, false);
        queue<int> a;
        dists[x] = 0, taken[x] = true;
        a.push(x);
        while (!a.empty()) {
            int q = a.front();
            a.pop();
            taken[q] = false;
            for (int q1 : gf[q]) {
                Edge& e = edges[q1];
                if (e.f != e.c && dists[e.y] > dists[q]+e.v) {
                    dists[e.y] = dists[q]+e.v;
                    if (!taken[e.y]) {
                        taken[e.y] = true;
                        a.push(e.y);
                    }
                }
            }
        }
    }

    bool push(int x, int y) {
        int n = (int)gf.size();
        vector<int> will(n, INF), parents(n, -1);
        priority_queue<p> a;
        will[x] = 0;
        a.emplace(0, x);
        while (!a.empty()) {
            int len = -a.top().first, q = a.top().second;
            a.pop();
            if (len != will[q]) {
                continue;
            }
            for (int q1 : gf[q]) {
                Edge& e = edges[q1];
                int will_dist = len+e.v+dists[e.x]-dists[e.y];
                if (e.f != e.c && will[e.y] > will_dist) {
                    will[e.y] = will_dist, parents[e.y] = q1;
                    a.emplace(-will_dist, e.y);
                }
            }
        }
        if (will[y] == INF) {
            return false;
        }
        while (x != y) {
            edges[parents[y]].f++;
            edges[parents[y] ^ 1].f--;
            y = edges[parents[y]].x;
        }
        for (int q = 0; q < n; q++) {
            will[q] -= dists[x]-dists[q];
        }
        dists = will;
        return true;
    }

    void build_flow(int x, int y, int k) {
        build_dists(x);
        for (int q = 0; q < k && push(x, y); q++);
    }

    int min_cost(int x, int y, int k = INF) {
        build_flow(x, y, k);
        int ans = 0;
        for (int q = 0; q < edges.size(); q += 2) {
            ans += edges[q].f*edges[q].v;
        }
        return ans;
    }

    vector<vector<int>> ways;

    void find_way(int x, int y) {
        if (x == y) {
            return;
        }
        for (int q1 : gf[x]) {
            Edge& q = edges[q1];
            if (q.f > 0) {
                find_way(q.y, y);
                edges[q1].f--, edges[q1 ^ 1].f++;
                ways.back().push_back(q1);
                return;
            }
        }
    }

    void decompose(int x, int y) {
        ways = {};
        vector<Edge> was_edges = edges;
        int k = 0;
        for (int q : gf[x]) {
            k += edges[q].f;
        }
        for (int q = 0; q < k; q++) {
            ways.emplace_back();
            find_way(x, y);
            reverse(ways.back().begin(), ways.back().end());
        }
        edges = was_edges;
    }
};

