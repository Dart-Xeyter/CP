struct SAT {
    vector<vector<int>> d;
    int n, m;

    SAT(int n, int m): n(n), m(m) {
        d.assign(2*n+2*m, {});
    }

    void add_edges(int x, int y) {
        d[x].push_back(y);
        d[y ^ 1].push_back(x ^ 1);
    }

    vector<vector<int>> d_rev;
    vector<int> who, topsort;
    vector<bool> was;

    void top_sort(int vertex) {
        was[vertex] = true;
        for (int q : d[vertex]) {
            if (!was[q]) {
                top_sort(q);
            }
        }
        topsort.push_back(vertex);
    }

    void find_component(int vertex, int c) {
        who[vertex] = c;
        for (int q : d_rev[vertex]) {
            if (who[q] == -1) {
                find_component(q, c);
            }
        }
    }

    void build_CSS(int N) {
        d_rev.assign(N, {}), was.assign(N, false);
        for (int q = 0; q < N; q++) {
            for (int q1 : d[q]) {
                d_rev[q1].push_back(q);
            }
        }
        who.assign(N, -1), topsort = {};
        for (int q = 0; q < N; q++) {
            if (!was[q]) {
                top_sort(q);
            }
        }
        reverse(topsort.begin(), topsort.end());
        int ind = 0;
        for (int q : topsort) {
            if (who[q] == -1) {
                find_component(q, ind++);
            }
        }
    }

    vector<int> ans;

    bool solve() {
        build_CSS(2*n+2*m);
        ans.assign(n, -1);
        for (int q = 0; q < n; q++) {
            if (who[2*q] == who[2*q+1]) {
                return false;
            }
            ans[q] = (who[2*q] < who[2*q+1]);
        }
        return true;
    }
};

