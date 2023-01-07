vector<vector<int>> d, up;
vector<int> tin, tout, height;
int time1 = 0, log1 = 20;

void make_LCA(int vertex, int parent, int h) {
    tin[vertex] = time1++, height[vertex] = h;
    up[vertex].push_back((parent == -1 ? vertex : parent));
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

vector<vector<int>> tree;

int make_compressed_tree(vector<int> &a) {
    int n = a.size();
    sort(a.begin(), a.end(), [](int x, int y) {return tin[x] < tin[y];});
    for (int q = 1; q < n; q++) {
        a.push_back(LCA(a[q-1], a[q]));
    }
    sort(a.begin(), a.end(), [](int x, int y) {return tin[x] < tin[y];});
    for (int q : a) {
        tree[q] = {};
    }
    n = a.size();
    vector<int> stack = {a[0]};
    for (int q = 1; q < n; q++) {
        while (tout[stack.back()] < tin[a[q]]) {
            stack.pop_back();
        }
        if (stack.back() != a[q]) {
            tree[stack.back()].push_back(a[q]);
            stack.push_back(a[q]);
        }
    }
    return a[0];
}
