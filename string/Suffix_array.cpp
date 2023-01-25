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
                    cls[will_suf[q-1]+deg-(will_suf[q-1]+deg >= n)*n] != cls[will_suf[q]+deg-(will_suf[q]+deg >= n)*n]);
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
        int is = (q == 0 || where[q-1] == n-1 ? 0 : max(0, lcp[where[q-1]]-1));
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
        int l1 = lower_bound(sufmas.begin()+l, sufmas.begin()+r, t[ind], [&s, ind](int x, char y) {return s[x+ind] < y;})-sufmas.begin();
        int r1 = lower_bound(sufmas.begin()+l, sufmas.begin()+r, t[ind], [&s, ind](int x, char y) {return s[x+ind] <= y;})-sufmas.begin();
        if (l1 == r1) {
            break;
        }
        l = l1, r = r1;
    }
    s.pop_back();
    return {{l, r}, ind};
}

vector<int> left_migration(vector<int> &a) {
    int n = a.size();
    vector<int> left(n, -1);
    vector<p> stack;
    for (int q = n-1; q > -1; q--) {
        while (!stack.empty() && stack.back().first > a[q]) {
            left[stack.back().second] = q;
            stack.pop_back();
        }
        stack.push_back({a[q], q});
    }
    return left;
}

vector<int> right_migration(vector<int> &a) {
    int n = a.size();
    vector<int> right(n, n);
    vector<p> stack;
    for (int q = 0; q < n; q++) {
        while (!stack.empty() && stack.back().first > a[q]) {
            right[stack.back().second] = q;
            stack.pop_back();
        }
        stack.push_back({a[q], q});
    }
    return right;
}

pair<p, int> del_end(pair<p, int> was, int m, vector<int> &lcp, vector<int> &left, vector<int> &right) {
    if (was.second < m) {
        return was;
    }
    int l = was.first.first, r = was.first.second-1;
    if (l > 0 && lcp[l-1] == m-1) {
        l = left[l-1]+1;
    }
    if (r < lcp.size() && lcp[r] == m-1) {
        r = right[r];
    }
    return {{l, r+1}, m-1};
}

map<char, vector<p>> beginnings(string &s, vector<int> &sufmas) {
    int n = sufmas.size();
    vector<int> where(n);
    for (int q = 0; q < n; q++) {
        where[sufmas[q]] = q;
    }
    map<char, vector<p>> begins;
    for (int q = 0; q < n-1; q++) {
        begins[s[q]].push_back({where[q+1], where[q]});
    }
    for (auto &q : begins) {
        sort(q.second.begin(), q.second.end());
    }
    return begins;
}

pair<p, int> add_begin(pair<p, int> was, char x, map<char, vector<p>> &begins, vector<int> &lcp, vector<int> &left, vector<int> &right) {
    if (begins.find(x) == begins.end()) {
        return {{0, lcp.size()+1}, 0};
    }
    while (true) {
        auto w1 = lower_bound(begins[x].begin(), begins[x].end(), p(was.first.first, -INF));
        if (w1 != begins[x].end() && w1->first < was.first.second) {
            break;
        }
        was = del_end(was, was.second, lcp, left, right);
    }
    int l = lower_bound(begins[x].begin(), begins[x].end(), p(was.first.first, -INF))->second;
    int r = (--lower_bound(begins[x].begin(), begins[x].end(), p(was.first.second, -INF)))->second;
    return {{l, r+1}, was.second+1};
}

