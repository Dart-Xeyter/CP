vector<vector<int>> d;
vector<bool> was;
vector<int> mat, parent, height;

DSU dsu(0);
vector<int> who;
queue<int> s;

int lca(int x) {
    return who[dsu.root(x)];
}

void mark_blossom(int x, int y) {
    int prev_x = y, prev_y = x;
    vector<int> comp;
    while (lca(x) != lca(y)) {
        if (height[lca(x)] < height[lca(y)]) {
            swap(x, y), swap(prev_x, prev_y);
        }
        parent[x] = prev_x;
        int par = mat[x];
        prev_x = par, x = parent[par];
        comp.push_back(par);
    }
    x = lca(x);
    for (int q : comp) {
        dsu.merge(q, x);
        dsu.merge(mat[q], x);
        if (!was[q]) {
            s.push(q);
            was[q] = true;
        }
    }
    who[dsu.root(x)] = x;
}

void decompress_way(int vertex, int q) {
    int x = mat[vertex];
    mat[q] = vertex, mat[vertex] = q;
    while (x != -1) {
        int y = exchange(x, mat[parent[x]]);
        mat[y] = parent[y], mat[parent[y]] = y;
    }
}

bool process_vertex(int vertex, int q) {
    if (q == mat[vertex] || dsu.root(vertex) == dsu.root(q)) {
        return false;
    }
    if (was[q]) {
        mark_blossom(vertex, q);
        return false;
    }
    if (mat[q] == -1) {
        decompress_way(vertex, q);
        return true;
    }
    if (was[mat[q]]) {
        return false;
    }
    s.push(mat[q]);
    was[mat[q]] = true, parent[q] = vertex;
    height[mat[q]] = height[lca(vertex)]+1;
    return false;
}

bool BFS(int vertex) {
    s.push(vertex);
    was[vertex] = true, height[vertex] = 0;
    while (!s.empty()) {
        vertex = s.front();
        s.pop();
        for (int q : d[vertex]) {
            if (process_vertex(vertex, q)) {
                return true;
            }
        }
    }
    return false;
}

int max_matching(int n) {
    mat.assign(n, -1);
    bool flag = true;
    while (flag) {
        was.assign(n, false), parent.assign(n, -1);
        height.assign(n, -1), dsu = DSU(n);
        who = dsu.parent, s = {}, flag = false;
        for (int q = 0; q < n; q++) {
            if (mat[q] == -1 && BFS(q)) {
                flag = true;
                break;
            }
        }
    }
    return (n-ranges::count(mat, -1))/2;
}

