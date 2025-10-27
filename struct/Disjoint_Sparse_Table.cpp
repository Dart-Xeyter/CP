int C;

struct Disjoint_Table {
    vector<vector<int>> s;
    vector<int> level;
    int n, len = 1, log = 0;

    Disjoint_Table(vector<int> a): n(a.size()) {
        while (len <= n) {
            len *= 2, log++;
        }
        a.resize(len, 0);
        s.assign(log, vector<int>(len, 1));
        level = {log};
        for (int q = 1; q < len; q++) {
            level.push_back(level[q >> 1]-1);
        }
        build(0, len, a, 0);
    }

    void build(int l, int r, vector<int>& a, int h) {
        if (r-l == 1) {
            return;
        }
        int m = (l+r) >> 1;
        for (int q = m-1; q >= l; q--) {
            s[h][q] = s[h][q+1]*a[q] % C;
        }
        for (int q = m+1; q < r; q++) {
            s[h][q] = s[h][q-1]*a[q-1] % C;
        }
        build(l, m, a, h+1);
        build(m, r, a, h+1);
    }

    int ans(int l, int r) {
        if (l >= r) {
            return 1;
        }
        int h = level[l ^ r];
        return s[h][l]*s[h][r] % C;
    }
};

