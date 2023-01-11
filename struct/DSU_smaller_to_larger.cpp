struct DSU {
    vector<int> size, root;
    vector<vector<int>> comp;

    DSU(int n) {
        root.assign(n, -1), size.assign(n, 1), comp.assign(n, {});
        for (int q = 0; q < n; q++) {
            root[q] = q, comp[q] = {q};
        }
    }

    void merge(int x, int y) {
        x = root[x], y = root[y];
        if (x == y) {
            return;
        }
        if (size[x] > size[y]) {
            swap(x, y);
        }
        size[y] += size[x];
        for (int q : comp[x]) {
            comp[y].push_back(q);
            root[q] = y;
        }
        size[x] = -1, comp[x] = {};
    }
};

