struct Sparse {
    vector<vector<int>> up;
    vector<int> deg;
    int log1 = 20;

    Sparse(vector<int> &a) {
        int n = a.size();
        up.assign(n, vector<int>(log1)), deg.assign(n+1, 0);
        for (int q = 2; q <= n; q++) {
            deg[q] = deg[q/2]+1;
        }
        for (int q = 0; q < n; q++) {
            up[q][0] = a[q];
        }
        for (int q = 1; q < log1; q++) {
            int w = (1 << (q-1));
            for (int q1 = 0; q1 < n-w; q1++) {
                up[q1][q] = min(up[q1][q-1], up[q1+w][q-1]);
            }
            for (int q1 = max(0LL, n-w); q1 < n; q1++) {
                up[q1][q] = up[q1][q-1];
            }
        }
    }

    int ans(int l, int r) {
        int w = deg[r-l];
        return min(up[l][w], up[r-(1 << w)][w]);
    }
};
