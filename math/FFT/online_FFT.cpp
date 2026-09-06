vector<int> online_FFT(vector<int> a, int b0, auto& func) {
    int n = (int)a.size();
    int log1 = get_degree(n), len = (1 << log1);
    a.resize(len, 0);
    vector<vector<int>> blocks(log1);
    for (int q = 0; q < log1; q++) {
        for (int q1 = (1 << q); q1 < (1 << (q+1)); q1++) {
            blocks[q].push_back(a[q1]);
        }
    }
    vector<int> b(2*len, 0), c(2*len, 0);
    b[0] = b0;
    for (int q = 0; q < n; q++) {
        c[q] += a[0]*b[q] % C, c[q] %= C;
        int deg = 1, ind = 0;
        while (q != 0 && q % deg == 0) {
            vector<int> b_i(b.begin()+q-deg, b.begin()+q);
            vector<int> now = multiply(blocks[ind], b_i);
            for (int q1 = 0; q1 < now.size(); q1++) {
                c[q+q1] += now[q1], c[q+q1] %= C;
            }
            deg *= 2, ind++;
        }
        func(q, b, c); // calc c[q] and get b[q+1]
    }
    return {c.begin(), c.begin()+n};
}

