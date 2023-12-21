vector<int> suf_mas(string &s) {
    s += '#';
    int n = s.size();
    vector<int> suf(n);
    iota(suf.begin(), suf.end(), 0);
    sort(suf.begin(), suf.end(), [&s](int x, int y) {return s[x] < s[y];});
    vector<int> cls(n, 0);
    for (int q = 1; q < n; q++) {
        cls[suf[q]] = cls[suf[q-1]]+(s[suf[q-1]] < s[suf[q]]);
    }
    int deg = 1;
    while (cls[suf.back()] < n-1) {
        vector<int> nums(cls[suf.back()]+1, 0);
        for (int q : suf) {
            nums[cls[q-deg+(q < deg)*n]]++;
        }
        vector<int> ind(cls[suf.back()]+1, 0);
        for (int q = 1; q <= cls[suf.back()]; q++) {
            ind[q] = ind[q-1]+nums[q-1];
        }
        vector<int> will_suf(n);
        for (int q : suf) {
            will_suf[ind[cls[q-deg+(q < deg)*n]]++] = q-deg+(q < deg)*n;
        }
        vector<int> will_cls(n, 0);
        for (int q = 1; q < n; q++) {
            bool change = (cls[will_suf[q-1]] != cls[will_suf[q]] ||
                           cls[will_suf[q-1]+deg-(will_suf[q-1]+deg >= n)*n] !=
                           cls[will_suf[q]+deg-(will_suf[q]+deg >= n)*n]);
            will_cls[will_suf[q]] = will_cls[will_suf[q-1]]+change;
        }
        suf = will_suf, cls = will_cls, deg *= 2;
    }
    return suf;
}

vector<int> LCP(const string& s, const vector<int>& sufmas) {
    int n = (int)s.size()-1; // '#' in the end
    vector<int> pos(n+1), lcp(n+1, 0);
    for (int q = 0; q <= n; q++) {
        pos[sufmas[q]] = q;
    }
    for (int q = 0; q <= n; q++) {
        int q1 = pos[q];
        if (q1 == n) {
            continue;
        }
        int next_q = sufmas[q1+1];
        lcp[q1] = (q == 0 ? 0 : max(0LL, lcp[pos[q-1]]-1));
        while (s[q+lcp[q1]] == s[next_q+lcp[q1]]) {
            lcp[q1]++;
        }
    }
    lcp.pop_back();
    return lcp;
}

