const int C = 1e9+7;

struct Matrix {
    vector<vector<int>> a;
    int n, m;

    Matrix(vector<vector<int>> a1) {
        n = a1.size(), m = a1[0].size();
        a.assign(n, vector<int>(m));
        for (int q = 0; q < n; q++) {
            for (int q1 = 0; q1 < m; q1++) {
                a[q][q1] = (a1[q][q1] % C+C) % C;
            }
        }
    }

    Matrix operator+(Matrix b) {
        vector<vector<int>> ans(n, vector<int>(m));
        for (int q = 0; q < n; q++) {
            for (int q1 = 0; q1 < m; q1++) {
                ans[q][q1] = (a[q][q1]+b.a[q][q1]) % C;
            }
        }
        return ans;
    }

    Matrix operator-() {
        vector<vector<int>> ans(n, vector<int>(m));
        for (int q = 0; q < n; q++) {
            for (int q1 = 0; q1 < m; q1++) {
                ans[q][q1] = (C-a[q][q1]) % C;
            }
        }
        return ans;
    }

    Matrix operator-(Matrix b) {
        return *this+(-b);
    }

    Matrix operator*(Matrix b) {
        vector<vector<int>> ans(n, vector<int>(b.m, 0));
        for (int q = 0; q < n; q++) {
            for (int q1 = 0; q1 < b.m; q1++) {
                for (int q2 = 0; q2 < m; q2++) {
                    ans[q][q1] += a[q][q2]*b.a[q2][q1] % C;
                }
                ans[q][q1] %= C;
            }
        }
        return ans;
    }
};

Matrix E(int n) {
    vector<vector<int>> ans(n, vector<int>(n, 0));
    for (int q = 0; q < n; q++) {
        ans[q][q] = 1;
    }
    return ans;
}

Matrix pow(Matrix a, int k) {
    if (k == 0) {
        return E(a.n);
    }
    if (k % 2 == 0) {
        return pow(a*a, k/2);
    }
    return pow(a, k-1)*a;
}

