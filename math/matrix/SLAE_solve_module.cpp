const int C = 1000000007;

int pow1(int x, int y) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2);
    }
    return pow1(x, y-1)*x % C;
}

struct Matrix {
    vector<vector<int>> a;
    int n, m;

    Matrix(vector<vector<int>> &a1) {
        n = a1.size(), m = a1[0].size(), a = a1;
    }

    void subtract(int q, int q1) {
        int del = pow1(a[q][q1], C-2);
        vector<int> norm;
        for (int q3 = 0; q3 < m; q3++) {
            if (a[q][q3] != 0) {
                norm.push_back(q3);
            }
        }
        for (int q2 = q+1; q2 < n; q2++) {
            if (a[q2][q1] != 0) {
                int coef = a[q2][q1]*del % C;
                for (int q3 : norm) {
                    a[q2][q3] -= a[q][q3]*coef % C;
                    a[q2][q3] += (a[q2][q3] < 0)*C;
                }
            }
        }
    }

    void gauss() {
        int q = 0, q1 = 0;
        while (q < n && q1 < m) {
            for (int q2 = q; q2 < n; q2++) {
                if (a[q2][q1] != 0) {
                    swap(a[q], a[q2]);
                    break;
                }
            }
            if (a[q][q1] == 0) {
                q1++;
                continue;
            }
            subtract(q++, q1++);
        }
    }

    vector<int> solve() {
        gauss();
        int q = n;
        bool flag = true;
        while (flag && (q--) > 0) {
            for (int q1 : a[q]) {
                flag &= (abs(q1) == 0);
            }
        }
        if (q == -1) {
            return {C};
        }
        flag = true;
        for (int q1 = 0; q1 < m-1; q1++) {
            flag &= (a[q][q1] == 0);
        }
        if (flag) {
            return {};
        }
        if (q < n-1 || n != m-1) {
            return {C};
        }
        vector<int> ans(n);
        for (; q > -1; q--) {
            int sum1 = a[q][m-1];
            for (int q1 = q+1; q1 < m-1; q1++) {
                sum1 -= a[q][q1]*ans[q1] % C;
            }
            ans[q] = (sum1 % C+C) % C*pow1(a[q][q], C-2) % C;
        }
        return ans;
    }
};
