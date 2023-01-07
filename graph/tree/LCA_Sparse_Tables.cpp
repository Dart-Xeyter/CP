struct Sparse {
    vector<vector<p>> up;
    vector<int> deg;
    int log1 = 20;

    Sparse(vector<p> &a) {
        int n = a.size();
        up.assign(n, vector<p>(log1)), deg.assign(n+1, 0);
        for (int q = 2; q <= n; q++) {
            deg[q] = deg[q/2]+1;
        }
        for (int q = 0; q < n; q++) {
            up[q][0] = a[q];
        }
        for (int q = 1; q < log1; q++) {
            int w = (1 << (q-1));
            for (int q1 = 0; q1 < n-w; q1++) {
                up[q1][q] = min(up[q1][q-1], up[q1+w][q-1]);
            }
            for (int q1 = max(0LL, n-w); q1 < n; q1++) {
                up[q1][q] = up[q1][q-1];
            }
        }
    }

    p ans(int l, int r) {
        int w = deg[r-l];
        return min(up[l][w], up[r-(1 << w)][w]);
    }
};

vector<vector<int>> d;
vector<int> tin, tout, height;
vector<p> order;

void make_LCA(int vertex, int parent, int h) {
    tin[vertex] = order.size(), height[vertex] = h;
    order.push_back({tin[vertex], vertex});
    for (int q : d[vertex]) {
        if (q != parent) {
            make_LCA(q, vertex, h+1);
            order.push_back({tin[vertex], vertex});
        }
    }
    tout[vertex] = order.size();
}

bool is_ancestor(int x, int y) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int LCA(int x, int y, Sparse &sparse) {
    return sparse.ans(min(tin[x], tin[y]), max(tout[x], tout[y])).second;
}

