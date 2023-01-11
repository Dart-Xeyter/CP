void print(const vector<int> &a) {
    for (int q : a) {
        cout << q << ' ';
    }
    cout << endl;
}

int pow1(int x, int y) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2);
    }
    return pow1(x, y-1)*x % C;
}

void fix(vector<int> &c, int len = INF) {
    while (c.size() > len || c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }
    for (int &q : c) {
        q = (q % C+C) % C;
    }
}

void zfill(vector<int> &c, int len) {
    while (c.size() < len) {
        c.push_back(0);
    }
}

vector<int> add(const vector<int> &a, const vector<int> &b, int len = INF) {
    int n = a.size(), m = b.size();
    len = min(len, max(n, m));
    vector<int> c(len);
    for (int q = 0; q < len; q++) {
        c[q] = (q < n ? a[q] : 0)+(q < m ? b[q] : 0);
    }
    fix(c, len);
    return c;
}

vector<int> sub(const vector<int> &a, const vector<int> &b, int len = INF) {
    int n = a.size(), m = b.size();
    len = min(len, max(n, m));
    vector<int> c(len);
    for (int q = 0; q < len; q++) {
        c[q] = (q < n ? a[q] : 0)-(q < m ? b[q] : 0);
    }
    fix(c, len);
    return c;
}

vector<int> mul(const vector<int> &a, const vector<int> &b, int len = INF) {
    int n = a.size(), m = b.size();
    vector<int> c(n+m, 0);
    for (int q = 0; q < n; q++) {
        for (int q1 = 0; q1 < min(len-q, m); q1++) {
            c[q+q1] += a[q]*b[q1] % C;
        }
    }
    fix(c, len);
    return c;
}

vector<int> pow(const vector<int> &a, int n, int len = INF) {
    if (n == 0) {
        return {1};
    }
    if (n % 2 == 0) {
        return pow(mul(a, a, len), n/2, len);
    }
    return mul(pow(a, n-1, len), a, len);
}

vector<int> div(const vector<int> &a, const vector<int> &b, int len) {
    assert(("div failed", b[0] != 0));
    int n = a.size(), m = b.size();
    int rev = pow1(b[0], C-2);
    vector<int> ans = {a[0]*rev % C};
    for (int q = 1; q < len; q++) {
        int sum1 = (q < n ? a[q] : 0);
        for (int q1 = 1; q1 < min(q+1, m); q1++) {
            sum1 -= b[q1]*ans[q-q1] % C;
        }
        sum1 = (sum1 % C+C) % C;
        ans.push_back(sum1*rev % C);
    }
    return ans;
}

vector<int> sqrt(const vector<int> &a, int len) {
    assert(("sqrt failed", a[0] == 1));
    int n = a.size();
    vector<int> ans = {1};
    int rev = pow1(2*ans[0], C-2);
    for (int q = 1; q < len; q++) {
        int sum1 = (q < n ? a[q] : 0);
        for (int q1 = 1; q1 < q; q1++) {
            sum1 -= ans[q1]*ans[q-q1] % C;
        }
        sum1 = (sum1 % C+C) % C;
        ans.push_back(sum1*rev % C);
    }
    return ans;
}

vector<int> exp(const vector<int> &a, int len) {
    assert(("exp failed", a[0] == 0));
    vector<int> ans = {1};
    int fact = 1;
    vector<int> now = {1};
    for (int q = 1; q < len; q++) {
        now = mul(now, a, len);
        fact = fact*pow1(q, C-2) % C;
        ans = add(ans, mul({fact}, now, len), len);
    }
    return ans;
}

vector<int> ln(const vector<int> &a, int len) {
    assert(("ln failed", a[0] == 1));
    vector<int> x = sub(a, {1});
    vector<int> ans = {0};
    vector<int> now = {1};
    for (int q = 1; q < len; q++) {
        now = mul(now, x, len);
        vector<int> w = mul({pow1(q, C-2)}, now, len);
        ans = (q % 2 == 1 ? add(ans, w, len) : sub(ans, w, len));
    }
    return ans;
}

