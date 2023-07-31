vector<vector<int>> d, up;
vector<int> tin, tout, height;
int time1 = 0, log1 = 20;

void make_LCA(int vertex, int parent, int h) {
    height[vertex] = h, tin[vertex] = time1++;
    up[vertex].push_back(parent == -1 ? vertex : parent);
    for (int q = 1; q < log1; q++) {
        up[vertex].push_back(up[up[vertex][q-1]][q-1]);
    }
    for (int q : d[vertex]) {
        if (q != parent) {
            make_LCA(q, vertex, h+1);
        }
    }
    tout[vertex] = time1++;
}

bool is_ancestor(int x, int y) {
    return tin[x] <= tin[y] && tout[y] <= tout[x];
}

int ancestor(int x, int k) {
    for (int q = log1-1; q > -1; q--) {
        if ((1 << q) <= k) {
            x = up[x][q], k -= (1 << q);
        }
    }
    return x;
}

int LCA(int x, int y) {
    if (is_ancestor(x, y)) {
        return x;
    }
    for (int q = log1-1; q > -1; q--) {
        if (!is_ancestor(up[x][q], y)) {
            x = up[x][q];
        }
    }
    return up[x][0];
}

