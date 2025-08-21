template <typename T>
struct DO {
    vector<T> a;
    int n, len = 1;

    T func(T x, T y) {return max(x, y);}
    T I = -INF;

    DO(const vector<T>& init) {
        n = (int)init.size();
        while (len < n) {
            len *= 2;
        }
        a.assign(2*len, I);
        for (int q = len; q < len+n; q++) {
            a[q] = init[q-len];
        }
        for (int q = len-1; q > 0; q--) {
            a[q] = func(a[2*q], a[2*q+1]);
        }
    }

    void change(int q, T x) {
        a[q+len] = x;
        q = (q+len) >> 1;
        while (q > 0) {
            a[q] = func(a[2*q], a[2*q+1]);
            q >>= 1;
        }
    }

    T ans(int l, int r) {
        l += len-1, r += len;
        T res_l = I, res_r = I;
        while (r-l > 1) {
            if ((l & 1) ^ 1) {
                res_l = func(res_l, a[l ^ 1]);
            }
            if (r & 1) {
                res_r = func(a[r ^ 1], res_r);
            }
            l >>= 1, r >>= 1;
        }
        return func(res_l, res_r);
    }

    int right_more(int q, T x) {
        q += len;
        while (q > 0 && ((q & 1) || a[q ^ 1] <= x)) {
            q >>= 1;
        }
        q ^= 1;
        if (a[q] <= x) {
            return n;
        }
        while (q < len) {
            q <<= 1;
            q ^= (a[q] <= x);
        }
        return q-len;
    }
};

