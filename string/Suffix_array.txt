vector<int> suf_mas(string &s) {
    s += '#';
    int n = s.size();
    vector<int> pos(n);
    iota(pos.begin(), pos.end(), 0);
    sort(pos.begin(), pos.end(), [&s](int x, int y) {return s[x] < s[y];});
    vector<int> cls(n, 0);
    for (int q = 1; q < n; q++) {
        cls[pos[q]] = cls[pos[q-1]]+(s[pos[q]] != s[pos[q-1]]);
    }
    int q2 = 1;
    while (cls[pos.back()] != n-1) {
        vector<vector<int>> d(cls[pos.back()]+1);
        for (int q = 0; q < n; q++) {
            d[cls[(pos[q]-q2+n) % n]].push_back((pos[q]-q2+n) % n);
        }
        int now = 0;
        for (auto &q : d) {
            for (int q1 : q) {
                pos[now++] = q1;
            }
        }
        vector<int> cls1(n, 0);
        for (int q = 1; q < n; q++) {
            cls1[pos[q]] = cls1[pos[q-1]]+(cls[pos[q]] != cls[pos[q-1]] || cls[(pos[q]+q2) % n] != cls[(pos[q-1]+q2) % n]);
        }
        cls = cls1, q2 *= 2;
    }
    return pos;
}

vector<int> LCP(vector<int> &sufmas, string &s) {
    int n = s.size();
    vector<int> ind(n, -1);
    for (int q = 0; q < n; q++) {
        ind[sufmas[q]] = q;
    }
    vector<int> lcp(n, 0);
    for (int q = 0; q < n; q++) {
        if (ind[q] == n-1) {
            continue;
        }
        if (q != 0) {
            lcp[ind[q]] = max(0LL, lcp[ind[q-1]]-1);
        }
        while (s[q+lcp[ind[q]]] == s[sufmas[ind[q]+1]+lcp[ind[q]]]) {
            lcp[ind[q]]++;
        }
    }
    lcp.pop_back();
    return lcp;
}
