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
    s.pop_back();
    return suf;
}

vector<int> LCP(string &s, vector<int> &sufmas) {
    s += '#';
    int n = s.size();
    vector<int> where(n);
    for (int q = 0; q < n; q++) {
        where[sufmas[q]] = q;
    }
    vector<int> lcp(n-1, 0);
    for (int q = 0; q < n-1; q++) {
        if (where[q] == n-1) {
            continue;
        }
        int is = (q == 0 || where[q-1] == n-1 ? 0 : max(0LL, lcp[where[q-1]]-1));
        for (int q1 = is;; q1++) {
            if (s[q+q1] != s[sufmas[where[q]+1]+q1]) {
                lcp[where[q]] = q1;
                break;
            }
        }
    }
    s.pop_back();
    return lcp;
}

pair<p, int> find(string &s, string &t, vector<int> &sufmas) {
    s += '#';
    int n = sufmas.size(), m = t.size();
    int l = 0, r = n, ind = 0;
    for (; ind < m; ind++) {
        auto lambda_l = [&s, ind](int x, char y) {return s[x+ind] < y;};
        int l1 = lower_bound(sufmas.begin()+l, sufmas.begin()+r, t[ind], lambda_l)-sufmas.begin();
        auto lambda_r = [&s, ind](int x, char y) {return s[x+ind] <= y;};
        int r1 = lower_bound(sufmas.begin()+l, sufmas.begin()+r, t[ind], lambda_r)-sufmas.begin();
        if (l1 == r1) {
            break;
        }
        l = l1, r = r1;
    }
    s.pop_back();
    return {{l, r}, ind};
}

