vector<vector<int>> d;
vector<int> parent, height, jump;

void make_LCA(int vertex, int p1, int h) {
    parent[vertex] = p1, height[vertex] = h;
    if (p1 != -1 && height[jump[p1]]-height[p1] == height[jump[jump[p1]]]-height[jump[p1]]) {
        jump[vertex] = jump[jump[p1]];
    } else {
        jump[vertex] = (p1 == -1 ? vertex : p1);
    }
    for (int q : d[vertex]) {
        if (q != p1) {
            make_LCA(q, vertex, h+1);
        }
    }
}

int k_ancestor(int vertex, int k) {
    int h = height[vertex]-k;
    while (height[vertex] > h) {
        vertex = (height[jump[vertex]] >= h ? jump[vertex] : parent[vertex]);
    }
    return vertex;
}

int LCA(int x, int y) {
    if (height[x] < height[y]) {
        swap(x, y);
    }
    x = k_ancestor(x, height[x]-height[y]);
    while (x != y) {
        if (jump[x] != jump[y]) {
            x = jump[x], y = jump[y];
        } else {
            x = parent[x], y = parent[y];
        }
    }
    return x;
}

