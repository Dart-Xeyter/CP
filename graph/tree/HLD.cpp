struct DO {
    vector<int> do_arr, mod;
    int len;

    DO(vector<int> &a) {
        len = 1;
        while (len < a.size()) {
            len *= 2;
        }
        do_arr.assign(2*len, 0), mod.assign(2*len, 0);
        for (int q = len; q < len+a.size(); q++) {
            do_arr[q] = a[q-len];
        }
        for (int q = len-1; q > 0; q--) {
            do_arr[q] = do_arr[2*q]+do_arr[2*q+1];
        }
    }

    void push(int q, int length) {
        do_arr[2*q] += length/2*mod[q], do_arr[2*q+1] += length/2*mod[q];
        mod[2*q] += mod[q], mod[2*q+1] += mod[q], mod[q] = 0;
    }

    void update(int l, int r, int l1, int r1, int q, int x) {
        if (l1 >= r || l >= r1) {
            return;
        }
        if (l1 <= l && r <= r1) {
            do_arr[q] += x*(r-l), mod[q] += x;
            return;
        }
        push(q, r-l);
        int m = (l+r)/2;
        update(l, m, l1, r1, 2*q, x);
        update(m, r, l1, r1, 2*q+1, x);
        do_arr[q] = do_arr[2*q]+do_arr[2*q+1];
    }

    int ans(int l, int r, int l1, int r1, int q) {
        if (l1 >= r || l >= r1) {
            return 0;
        }
        if (l1 <= l && r <= r1) {
            return do_arr[q];
        }
        push(q, r-l);
        int m = (l+r)/2;
        return ans(l, m, l1, r1, 2*q)+ans(m, r, l1, r1, 2*q+1);
    }
};

vector<vector<int>> d;
vector<int> parent, sizes, tin, tout, height, order, up;
vector<int> a;

void for_HLD(int vertex, int p1) {
    int now = 1;
    for (int q : d[vertex]) {
        if (q != p1) {
            for_HLD(q, vertex);
            now += sizes[q];
        }
    }
    sizes[vertex] = now, parent[vertex] = p1;
    sort(d[vertex].begin(), d[vertex].end(), [](int x, int y) {return sizes[x] > sizes[y];});
}

void DFS_HLD(int vertex, int p1, int h) {
    tin[vertex] = order.size(), height[vertex] = h;
    up[vertex] = (p1 == -1 || d[p1][0] != vertex ? vertex : up[p1]);
    order.push_back(a[vertex]);
    for (int q : d[vertex]) {
        if (q != p1) {
            DFS_HLD(q, vertex, h+1);
        }
    }
    tout[vertex] = order.size();
}

DO make_HLD() {
    int n = d.size();
    sizes.assign(n, -1), parent.assign(n, -1), height.assign(n, -1);
    tin.assign(n, -1), tout.assign(n, -1), up.assign(n, -1);
    for_HLD(0, -1);
    DFS_HLD(0, -1, 0);
    return DO(order);
}

void update_way(int x, int y, int k, DO &do_arr) {
    if (height[up[x]] < height[up[y]]) {
        swap(x, y);
    }
    while (up[x] != up[y]) {
        do_arr.update(0, do_arr.len, tin[up[x]], tin[x]+1, 1, k);
        x = parent[up[x]];
        if (height[up[x]] < height[up[y]]) {
            swap(x, y);
        }
    }
    do_arr.update(0, do_arr.len, min(tin[x], tin[y]), max(tin[x], tin[y])+1, 1, k);
}

int ans_way(int x, int y, DO &do_arr) {
    if (height[up[x]] < height[up[y]]) {
        swap(x, y);
    }
    int ans = 0;
    while (up[x] != up[y]) {
        ans += do_arr.ans(0, do_arr.len, tin[up[x]], tin[x]+1, 1);
        x = parent[up[x]];
        if (height[up[x]] < height[up[y]]) {
            swap(x, y);
        }
    }
    ans += do_arr.ans(0, do_arr.len, min(tin[x], tin[y]), max(tin[x], tin[y])+1, 1);
    return ans;
}
