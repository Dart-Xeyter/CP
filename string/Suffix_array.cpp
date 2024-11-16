vector<int> suf_mas(string &s) {
    s += '#';
    int n = (int)s.size();
    vector<int> suf(n);
    iota(suf.begin(), suf.end(), 0);
    sort(suf.begin(), suf.end(), [&s](int x, int y) {return s[x] < s[y];});
    vector<int> cls(n, 0);
    for (int q = 1; q < n; q++) {
        bool more = (s[suf[q-1]] < s[suf[q]]);
        cls[suf[q]] = cls[suf[q-1]]+more;
    }
    int deg = 1;
    while (cls[suf.back()] < n-1) {
        int num_cls = cls[suf.back()];
        vector<int> nums(num_cls+1, 0);
        for (int q : suf) {
            int ind1 = q-deg+(q < deg)*n;
            nums[cls[ind1]]++;
        }
        vector<int> ind(num_cls+1, 0);
        for (int q = 1; q <= num_cls; q++) {
            ind[q] = ind[q-1]+nums[q-1];
        }
        vector<int> will_suf(n);
        for (int q : suf) {
            int ind1 = q-deg+(q < deg)*n;
            will_suf[ind[cls[ind1]]++] = ind1;
        }
        vector<int> will_cls(n, 0);
        for (int q = 1; q < n; q++) {
            bool start_dif = (cls[will_suf[q-1]] != cls[will_suf[q]]);
            int ind_prev = will_suf[q-1]+deg;
            ind_prev -= (ind_prev >= n)*n;
            int ind_my = will_suf[q]+deg;
            ind_my -= (ind_my >= n)*n;
            bool end_dif = (cls[ind_prev] != cls[ind_my]);
            bool change = (start_dif || end_dif);
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
        lcp[q1] = (q == 0 ? 0 : max(0LL, lcp[pos[q-1]] - 1));
        while (s[q+lcp[q1]] == s[next_q+lcp[q1]]) {
            lcp[q1]++;
        }
    }
    lcp.pop_back();
    return lcp;
}

