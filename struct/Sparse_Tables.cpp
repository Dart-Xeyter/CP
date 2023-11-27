struct Sparse {
    vector<vector<int>> mins;
    vector<int> logs;

    Sparse(vector<int> &a) {
        int n = a.size();
        logs = {-1};
        for (int q = 1; q <= n; q++) {
            logs.push_back(logs[q/2]+1);
        }
        mins.assign(n, vector<int>(logs.back()+1, INF));
        for (int q = 0; q < n; q++) {
            mins[q][0] = a[q];
        }
        for (int q = 1; q <= logs.back(); q++) {
            for (int q1 = 0; q1 < n; q1++) {
                int value = (q1 < n-(1 << (q-1)) ? mins[q1+(1 << (q-1))][q-1] : INF);
                mins[q1][q] = min(mins[q1][q-1], value);
            }
        }
    }

    int ans(int l, int r) {
        if (l == r) {
            return INF;
        }
        return min(mins[l][logs[r-l]], mins[r-(1 << logs[r-l])][logs[r-l]]);
    }
};

