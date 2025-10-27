vector<int> online_FFT(int a0, vector<int> b, int c0, auto& func) {
    int n = (int)b.size();
    int log1 = get_degree(n), len = (1 << log1);
    b.resize(len, 0);
    vector<vector<int>> blocks(log1);
    for (int q = 0; q < log1; q++) {
        for (int q1 = (1 << q); q1 < (1 << (q+1)); q1++) {
            blocks[q].push_back(b[q1]);
        }
    }
    vector<int> a(2*len, 0), c(2*len, 0);
    a[0] = a0, c[0] = c0;
    for (int q = 1; q < n; q++) {
        int deg = 1, ind = 0;
        while (q % deg == 0) {
            vector<int> a_i(a.begin()+q-deg, a.begin()+q);
            vector<int> now = multiply(a_i, blocks[ind]);
            for (int q1 = 0; q1 < now.size(); q1++) {
                c[q+q1] += now[q1], c[q+q1] %= C;
            }
            deg *= 2, ind++;
        }
        func(q, a, c);
    }
    return {c.begin(), c.begin()+n};
}

