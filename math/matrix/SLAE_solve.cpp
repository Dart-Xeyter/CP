const ld E = 1e-8;

struct Matrix {
    vector<vector<ld>> a;
    int n, m;

    Matrix(auto& a_): n(a_.size()), m(a_[0].size()) {
        a.assign(n, vector<ld>(m));
        for (int q = 0; q < n; q++) {
            for (int q1 = 0; q1 < m; q1++) {
                a[q][q1] = a_[q][q1];
            }
        }
    }

    Matrix(Matrix&) = default;

    int find_leader(int q) {
        int q1 = 0;
        while (q1 < m && abs(a[q][q1]) < E) {
            q1++;
        }
        return q1;
    }

    void subtract(int q, int q1) {
        ld val = a[q][q1];
        for (int q2 = 0; q2 < n; q2++) {
            if (q == q2 || abs(a[q2][q1]) < E) {
                continue;
            }
            ld coef = a[q2][q1]/val;
            for (int q3 = 0; q3 < m; q3++) {
                a[q2][q3] -= a[q][q3]*coef;
            }
        }
    }

    void gauss() {
        for (int q = 0; q < n; q++) {
            int q1 = find_leader(q);
            if (q1 != m) {
                subtract(q, q1);
            }
        }
    }
};

vector<ld> solve_SLAE(Matrix a, vector<ld>& s) {
    a.m++;
    for (int q = 0; q < a.n; q++) {
        a.a[q].push_back(s[q]);
    }
    a.gauss();
    vector<ld> ans(a.m-1, 0);
    for (int q = 0; q < a.n; q++) {
        int q1 = a.find_leader(q);
        if (q1 == a.m-1) {
            return {};
        }
        if (q1 != a.m) {
            ld val = a.a[q][q1];
            ld need = a.a[q].back();
            ans[q1] = need/val;
        }
    }
    return ans;
}

