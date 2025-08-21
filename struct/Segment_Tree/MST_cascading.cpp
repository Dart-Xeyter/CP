struct MST {
    struct Item {
        int x, l, r;

        bool operator<(Item other) {
            return x < other.x;
        }
    };

    vector<vector<Item>> a;
    int len = 1;

    MST(vector<int>& init) {
        int n = (int)init.size();
        while (len < n) {
            len *= 2;
        }
        a.assign(2*len, {});
        for (int q = len; q < len+n; q++) {
            a[q].emplace_back(init[q-len], -1, -1);
        }
        for (int q = len; q < 2*len; q++) {
            a[q].emplace_back(INF, -1, -1);
        }
        for (int q = len-1; q > 0; q--) {
            merge_children(q);
        }
        for (int q = 1; q < 2*len; q++) {
            a[q].pop_back();
        }
    }

    void merge_children(int q) {
        int n = (int)a[2*q].size();
        int q2 = 0;
        for (int q1 = 0; q1 < n; q1++) {
            while (a[2*q+1][q2].x < a[2*q][q1].x) {
                a[q].emplace_back(a[2*q+1][q2].x, q1, q2);
                q2++;
            }
            a[q].emplace_back(a[2*q][q1].x, q1, q2);
        }
    }

    int ans(int l, int r, int L, int R, int q, int ind) {
        int size = (int)a[q].size();
        if (l >= R || L >= r || ind == size) {
            return 0;
        }
        if (L <= l && r <= R) {
            return size-ind;
        }
        int m = (l+r) >> 1;
        int ans_l = ans(l, m, L, R, 2*q, a[q][ind].l);
        int ans_r = ans(m, r, L, R, 2*q+1, a[q][ind].r);
        return ans_l+ans_r;
    }

    int more_equal(int l, int r, int x) {
        auto w = lower_bound(a[1].begin(), a[1].end(), Item{x, -1, -1});
        return ans(0, len, l, r, 1, w-a[1].begin());
    }
};

