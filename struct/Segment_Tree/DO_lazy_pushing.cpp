struct DO {
    vector<int> do_arr, mod;
    int len;

    DO(vector<int> &a) {
        len = 1;
        while (len < a.size()) {
            len *= 2;
        }
        do_arr.assign(2*len, INF), mod.assign(2*len, 0);
        for (int q = len; q < len+a.size(); q++) {
            do_arr[q] = a[q-len];
        }
        for (int q = len-1; q > 0; q--) {
            do_arr[q] = min(do_arr[2*q], do_arr[2*q+1]);
        }
    }

    void push(int q) {
        do_arr[2*q] += mod[q], do_arr[2*q+1] += mod[q];
        mod[2*q] += mod[q], mod[2*q+1] += mod[q], mod[q] = 0;
    }

    void update(int l, int r, int l1, int r1, int q, int x) {
        if (l1 >= r || l >= r1) {
            return;
        }
        if (l1 <= l && r <= r1) {
            do_arr[q] += x, mod[q] += x;
            return;
        }
        push(q);
        int m = (l+r)/2;
        update(l, m, l1, r1, 2*q, x);
        update(m, r, l1, r1, 2*q+1, x);
        do_arr[q] = min(do_arr[2*q], do_arr[2*q+1]);
    }

    int ans(int l, int r, int l1, int r1, int q) {
        if (l1 >= r || l >= r1) {
            return INF;
        }
        if (l1 <= l && r <= r1) {
            return do_arr[q];
        }
        push(q);
        int m = (l+r)/2;
        return min(ans(l, m, l1, r1, 2*q), ans(m, r, l1, r1, 2*q+1));
    }
};

