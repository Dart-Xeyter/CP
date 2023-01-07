struct SQRT {
    vector<vector<int>> d, f;
    vector<int> mod;
    int sqrt1 = 700;

    SQRT(vector<int> &a) {
        int n = a.size();
        for (int q = 0; q < n; q++) {
            if (q % sqrt1 == 0) {
                d.emplace_back();
                f.emplace_back();
                mod.push_back(0);
            }
            d.back().push_back(a[q]);
            f.back().push_back(a[q]);
            if (q == n-1 || q % sqrt1 == sqrt1-1) {
                sort(f.back().begin(), f.back().end());
            }
        }
    }

    void rebuild(int q, int l, int r, int x) {
        for (int q1 = l; q1 <= r; q1++) {
            d[q][q1] += x;
        }
        f[q] = d[q];
        sort(f[q].begin(), f[q].end());
    }

    void update(int l, int r, int x) {
        int start = l/sqrt1, end = r/sqrt1;
        if (l/sqrt1 == r/sqrt1) {
            rebuild(start, l % sqrt1, r % sqrt1, x);
            return;
        }
        rebuild(start, l % sqrt1, (int)d[start].size()-1, x);
        for (int q = start+1; q < end; q++) {
            mod[q] += x;
        }
        rebuild(end, 0, r % sqrt1, x);
    }

    bool is(int q, int l, int r, int x) {
        for (int q1 = l; q1 <= r; q1++) {
            if (d[q][q1]+mod[q] == x) {
                return true;
            }
        }
        return false;
    }

    bool ans(int l, int r, int x) {
        int start = l/sqrt1, end = r/sqrt1;
        if (l/sqrt1 == r/sqrt1) {
            return is(start, l % sqrt1, r % sqrt1, x);
        }
        bool flag = false;
        flag |= is(start, l % sqrt1, (int)d[start].size()-1, x);
        for (int q = start+1; q < end; q++) {
            auto w = lower_bound(f[q].begin(), f[q].end(), x-mod[q]);
            flag |= (w != f[q].end() && *w == x-mod[q]);
        }
        flag |= is(end, 0, r % sqrt1, x);
        return flag;
    }
};

