struct DO {
    vector<int> do_arr;
    int len;

    DO(vector<int> a) {
        len = 1;
        while (len < a.size()) {
            len *= 2;
        }
        do_arr.assign(2*len, 0);
        for (int q = len; q < a.size()+len; q++) {
            do_arr[q] = a[q-len];
        }
        for (int q = len-1; q > 0; q--) {
            do_arr[q] = __gcd(do_arr[2*q], do_arr[2*q+1]);
        }
    }

    void change(int q, int x) {
        do_arr[q+len] = x;
        q = (q+len)/2;
        while (q > 0) {
            do_arr[q] = __gcd(do_arr[2*q], do_arr[2*q+1]);
            q /= 2;
        }
    }

    vector<int> f;

    void cut(int l, int r, int l1, int r1, int q) {
        if (l1 >= r || l >= r1 || l1 >= r1) {
            return;
        }
        if (l1 <= l && r <= r1) {
            f.push_back(q);
            return;
        }
        int m = (l+r)/2;
        cut(l, m, l1, r1, 2*q);
        cut(m, r, l1, r1, 2*q+1);
    }

    int descent(int q, int x) {
        if (q >= len) {
            return q-len;
        }
        if (do_arr[2*q] % x != 0) {
            return descent(2*q, x);
        }
        return descent(2*q+1, x);
    }

    int ans(int q, int x) {
        f = {};
        cut(0, len, q, len, 1);
        for (int q2 : f) {
            if (do_arr[q2] % x != 0) {
                return descent(q2, x);
            }
        }
        return -1;
    }
};
