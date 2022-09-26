struct Matrix {
    vector<vector<ld>> a;
    int n, m;

    Matrix(vector<vector<ld>> &a1) {
        n = a1.size(), m = a1[0].size();
        a.assign(n, vector<ld>(m));
        for (int q = 0; q < n; q++) {
            for (int q1 = 0; q1 < m; q1++) {
                a[q][q1] = a1[q][q1];
            }
        }
    }

    void subtract(int q, int q1) {
        vector<int> norm;
        for (int q3 = 0; q3 < m; q3++) {
            if (abs(a[q][q3]) > E) {
                norm.push_back(q3);
            }
        }
        for (int q2 = q+1; q2 < n; q2++) {
            if (abs(a[q2][q1]) > E) {
                ld coef = a[q2][q1]/a[q][q1];
                for (int q3 : norm) {
                    a[q2][q3] -= a[q][q3]*coef;
                }
            }
        }
    }

    void gauss() {
        int q = 0, q1 = 0;
        while (q < n && q1 < m) {
            for (int q2 = q; q2 < n; q2++) {
                if (abs(a[q2][q1]) > E) {
                    swap(a[q], a[q2]);
                    break;
                }
            }
            if (abs(a[q][q1]) < E) {
                q1++;
                continue;
            }
            subtract(q++, q1++);
        }
    }

    vector<ld> solve() {
        gauss();
        int q = n;
        bool flag = true;
        while (flag && (q--) > 0) {
            for (ld q1 : a[q]) {
                flag &= (abs(q1) < E);
            }
        }
        if (q == -1) {
            return {INF};
        }
        flag = true;
        for (int q1 = 0; q1 < m-1; q1++) {
            flag &= (abs(a[q][q1]) < E);
        }
        if (flag) {
            return {};
        }
        if (q < n-1 || n != m-1) {
            return {INF};
        }
        vector<ld> ans(n);
        for (; q > -1; q--) {
            ld sum1 = a[q][m-1];
            for (int q1 = q+1; q1 < m-1; q1++) {
                sum1 -= a[q][q1]*ans[q1];
            }
            ans[q] = sum1/a[q][q];
        }
        return ans;
    }
};
