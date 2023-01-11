struct DSU {
    vector<int> size, parent;

    DSU(int n) {
        size.assign(n, 1), parent.assign(n, -1);
        iota(parent.begin(), parent.end(), 0);
    }

    int root(int x) {
        vector<int> a;
        while (x != parent[x]) {
            a.push_back(x);
            x = parent[x];
        }
        for (int q : a) {
            parent[q] = x;
        }
        return x;
    }

    bool merge(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) {
            return false;
        }
        if (size[x] < size[y]) {
            swap(x, y);
        }
        size[x] += size[y], parent[y] = x;
        return true;
    }
};

