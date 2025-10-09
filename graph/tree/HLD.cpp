vector<vector<int>> d;
vector<int> parents, sizes, height;

void DFS_sizes(int vertex, int parent, int h) {
    parents[vertex] = parent;
    sizes[vertex] = 1, height[vertex] = h;
    for (int q : d[vertex]) {
        if (q != parent) {
            DFS_sizes(q, vertex, h+1);
            sizes[vertex] += sizes[q];
        }
    }
    ranges::sort(d[vertex], {}, [](int x) {return -sizes[x];});
}

vector<int> up, tin, tout;
vector<int> order;

void DFS_create(int vertex, int parent, bool first) {
    tin[vertex] = (int)order.size();
    order.push_back(vertex);
    up[vertex] = (first ? up[parent] : vertex);
    first = true;
    for (int q : d[vertex]) {
        if (q != parent) {
            DFS_create(q, vertex, first);
            first = false;
        }
    }
    tout[vertex] = (int)order.size();
}

DO do_arr({});

void build_HLD(int vertex, vector<int>& a) {
    int n = (int)a.size();
    parents.assign(n, -1), sizes.assign(n, -1), height.assign(n, -1);
    DFS_sizes(vertex, -1, 0);
    up.assign(n, -1), tin.assign(n, -1), tout.assign(n, -1), order = {};
    DFS_create(vertex, -1, false);
    vector<int> for_do(n);
    for (int q = 0; q < n; q++) {
        for_do[q] = a[order[q]];
    }
    do_arr = DO(for_do);
}

int process_way(int x, int y, auto& func) {
    while (up[x] != up[y]) {
        if (height[up[x]] < height[up[y]]) {
            swap(x, y);
        }
        int z = up[x];
        func(tin[z], tin[x]+1);
        x = parents[z];
    }
    if (height[x] < height[y]) {
        swap(x, y);
    }
    func(tin[y], tin[x]+1);
    return y;
}

