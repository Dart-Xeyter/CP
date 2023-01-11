const int C = 1791179179;

int pow1(int x, int y) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2);
    }
    return pow1(x, y-1)*x % C;
}

vector<int> Berlekamp(vector<int> &rec) {
    int n = rec.size(), q1 = 0;
    while (q1 < n && rec[q1] == 0) {
        q1++;
    }
    if (q1 == n) {
        return {};
    }
    int t = rec[q1] % C, q2 = q1++;
    vector<int> was, now = vector<int>(q1, 0);
    for (; q1 < n; q1++) {
        int d = -rec[q1] % C;
        for (int q = 1; q <= now.size(); q++) {
            d = (d+now[q-1]*rec[q1-q]) % C;
        }
        if (d == 0) {
            continue;
        }
        vector<int> will = now;
        while (will.size() < q1-q2+(int)was.size()) {
            will.push_back(0);
        }
        int mul = d*pow1(t, C-2) % C;
        will[q1-q2-1] = (will[q1-q2-1]+mul) % C;
        for (int q = 0; q < was.size(); q++) {
            will[q1-q2+q] = (will[q1-q2+q]-was[q]*mul) % C;
        }
        was = now, now = will, t = d, q2 = q1;
    }
    for (int& q : now) {
        q = (q+C) % C, q -= (q > C/2)*C;
    }
    while (!now.empty() && now.back() == 0) {
        now.pop_back();
    }
    return now;
}

int stupid(int n) {
    //to do
}

int find_n(int n, bool flag = false) {
    int k = 57;
    vector<int> a = {0};
    for (int q = 1; q < (flag ? n+1 : k); q++) {
        a.push_back(stupid(q));
    }
    vector<int> rec = Berlekamp(a);
    if (flag) {
        for (int q : rec) {
            cout << q << ' ';
        }
        cout << endl;
    }
    for (int q = k; q <= n; q++) {
        a.push_back(0);
        for (int q1 = 1; q1 <= rec.size(); q1++) {
            a.back() += a[q-q1]*rec[q1-1] % C;
        }
        a.back() = (a.back() % C+C) % C;
    }
    return a[n];
}

