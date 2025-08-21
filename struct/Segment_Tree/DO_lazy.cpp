struct DO {
    vector<int> a, mod;
    int n, len = 1;

    DO(const vector<int>& init) {
        n = (int)init.size();
        while (len < n) {
            len *= 2;
        }
        a.assign(2*len, -INF), mod.assign(2*len, 0);
        for (int q = len; q < len+n; q++) {
            a[q] = init[q-len];
        }
        for (int q = len-1; q > 0; q--) {
            a[q] = max(a[2*q], a[2*q+1]);
        }
    }

    void push(int q) {
        a[2*q] += mod[q], a[2*q+1] += mod[q];
        mod[2*q] += mod[q], mod[2*q+1] += mod[q];
        mod[q] = 0;
    }

    void update(int l, int r, int L, int R, int q, int x) {
        if (L >= r || l >= R) {
            return;
        }
        if (L <= l && r <= R) {
            a[q] += x, mod[q] += x;
            return;
        }
        push(q);
        int m = (l+r) >> 1;
        update(l, m, L, R, 2*q, x);
        update(m, r, L, R, 2*q+1, x);
        a[q] = max(a[2*q], a[2*q+1]);
    }

    void update(int l, int r, int x) {
        update(0, len, l, r, 1, x);
    }

    int ans(int l, int r, int L, int R, int q) {
        if (L >= r || l >= R) {
            return -INF;
        }
        if (L <= l && r <= R) {
            return a[q];
        }
        push(q);
        int m = (l+r) >> 1;
        int ans_l = ans(l, m, L, R, 2*q);
        int ans_r = ans(m, r, L, R, 2*q+1);
        return max(ans_l, ans_r);
    }

    int ans(int l, int r) {
        return ans(0, len, l, r, 1);
    }

    vector<int> segs;

    void cut(int l, int r, int L, int R, int q) {
        if (L >= r || l >= R) {
            return;
        }
        if (L <= l && r <= R) {
            segs.push_back(q);
            return;
        }
        push(q);
        int m = (l+r) >> 1;
        cut(l, m, L, R, 2*q);
        cut(m, r, L, R, 2*q+1);
    }

    int descent_right(int q, int x) {
        while (q < len) {
            push(q);
            q <<= 1;
            q ^= (a[q] <= x);
        }
        return q-len;
    }

    int right_more(int pos, int x) {
        segs = {};
        cut(0, len, pos+1, n, 1);
        for (int q : segs) {
            if (a[q] > x) {
                return descent_right(q, x);
            }
        }
        return n;
    }
};

