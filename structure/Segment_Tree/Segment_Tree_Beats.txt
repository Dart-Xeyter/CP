struct DO {
    vector<int> do_arr, max1, cnt_max, max2, push_min;
    int len;

    DO(vector<int> &a) {
        len = 1;
        while (len < a.size()) {
            len *= 2;
        }
        do_arr.assign(2*len, 0), max1.assign(2*len, -INF-1), cnt_max.assign(2*len, 0);
        max2.assign(2*len, -INF), push_min.assign(2*len, INF);
        for (int q = len; q < len+a.size(); q++) {
            do_arr[q] = max1[q] = a[q-len], cnt_max[q] = 1;
        }
        for (int q = len-1; q > 0; q--) {
            update(q);
        }
    }

    void upd_min(int q, int x) {
        do_arr[q] -= max(0LL, cnt_max[q]*(max1[q]-x));
        push_min[q] = min(push_min[q], x);
        max1[q] = min(max1[q], x);
    }

    void push(int q) {
        int x = push_min[q];
        upd_min(2*q, x);
        upd_min(2*q+1, x);
    }

    void update(int q) {
        if (max1[2*q] == max1[2*q+1]) {
            max1[q] = max1[2*q], cnt_max[q] = cnt_max[2*q]+cnt_max[2*q+1];
            max2[q] = max(max2[2*q], max2[2*q+1]);
        } else if (max1[2*q] > max1[2*q+1]) {
            max1[q] = max1[2*q], cnt_max[q] = cnt_max[2*q];
            max2[q] = max(max2[2*q], max1[2*q+1]);
        } else {
            max1[q] = max1[2*q+1], cnt_max[q] = cnt_max[2*q+1];
            max2[q] = max(max1[2*q], max2[2*q+1]);
        }
        do_arr[q] = do_arr[2*q]+do_arr[2*q+1];
    }

    void update_min(int l, int r, int l1, int r1, int q, int x) {
        if (l >= r1 || l1 >= r || max1[q] <= x) {
            return;
        }
        if (l1 <= l && r <= r1 && max2[q] < x) {
            upd_min(q, x);
            return;
        }
        push(q);
        int m = (l+r)/2;
        update_min(l, m, l1, r1, 2*q, x);
        update_min(m, r, l1, r1, 2*q+1, x);
        update(q);
    }

    int ans(int l, int r, int l1, int r1, int q) {
        if (l >= r1 || l1 >= r) {
            return 0;
        }
        if (l1 <= l && r <= r1) {
            return do_arr[q];
        }
        push(q);
        int m = (l+r)/2;
        return ans(l, m, l1, r1, 2*q)+ans(m, r, l1, r1, 2*q+1);
    }
};
