struct DO {
    vector<p> do_arr;
    int len;

    DO(vector<int> &a) {
        len = 1;
        while (len < a.size()) {
            len *= 2;
        }
        do_arr.assign(2*len, {INF, -1});
        for (int q = len; q < len+a.size(); q++) {
            do_arr[q] = {a[q-len], q-len};
        }
        for (int q = len-1; q > 0; q--) {
            do_arr[q] = min(do_arr[2*q], do_arr[2*q+1]);
        }
    }

    void change(int q, int x) {
        do_arr[q+len].first = x;
        q = (q+len)/2;
        while (q > 0) {
            do_arr[q] = min(do_arr[2*q], do_arr[2*q+1]);
            q /= 2;
        }
    }

    p ans(int l, int r, int l1, int r1, int q) {
        if (l >= r1 || l1 >= r) {
            return {INF, -1};
        }
        if (l1 <= l && r <= r1) {
            return do_arr[q];
        }
        int m = (l+r)/2;
        return min(ans(l, m, l1, r1, 2*q), ans(m, r, l1, r1, 2*q+1));
    }
};

