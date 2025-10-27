struct Line {
    int k, b;
 
    int val(int x) {
        return k*x+b;
    }
};
 
struct Li_Chao {
    vector<Line> a;
    int len = 1;
 
    Li_Chao(int n) {
        while (len < n) {
            len *= 2;
        }
        a.assign(2*len, {0, INF});
    }
 
    void descent(int l, int r, int q, Line line) {
        while (q < 2*len) {
            int m = (l+r) >> 1;
            if (a[q].val(m) > line.val(m)) {
                swap(a[q], line);
            }
            if (a[q].val(l) > line.val(l)) {
                r = m;
            } else {
                l = m;
            }
            q *= 2, q += (l == m);
        }
    }
 
    void add(int l, int r, int L, int R, int q, Line line) {
        if (l >= R || L >= r) {
            return;
        }
        if (L <= l && r <= R) {
            descent(l, r, q, line);
            return;
        }
        int m = (l+r) >> 1;
        add(l, m, L, R, 2*q, line);
        add(m, r, L, R, 2*q+1, line);
    }
 
    void add(int l, int r, Line line) {
        add(0, len, l, r, 1, line);
    }
 
    int ans(int x) {
        int q = x+len, res = INF;
        while (q > 0) {
            res = min(res, a[q].val(x));
            q >>= 1;
        }
        return res;
    }
};

