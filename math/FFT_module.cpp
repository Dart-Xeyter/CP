const int C = 998244353, C_2 = C*C;

int pow1(int x, int y) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2);
    }
    return pow1(x, y-1)*x % C;
}

vector<int> factor(int n) {
    int sqrt1 = sqrt(n);
    vector<int> ans;
    for (int q = 2; q <= sqrt1; q++) {
        if (n % q == 0) {
            ans.push_back(q);
        }
        while (n % q == 0) {
            n /= q;
        }
    }
    if (n > 1) {
        ans.push_back(n);
    }
    return ans;
}

int find_g() {
    int q1 = 1;
    vector<int> fact = factor(C-1);
    bool flag = false;
    while (!flag) {
        q1++, flag = true;
        for (int q : fact) {
            if (pow1(q1, (C-1)/q) == 1) {
                flag = false;
                break;
            }
        }
    }
    return q1;
}

vector<int> deg, rev;

vector<int> FFT(vector<int> &a) {
    int n = a.size();
    vector<int> a1(n);
    for (int q = 0; q < n; q++) {
        a1[rev[q]] = a[q];
    }
    a = a1;
    for (int q = 2; q <= n; q *= 2) {
        int w = q/2, len = n/q;
        for (int q1 = 0; q1 < n; q1 += q) {
            int q3 = 0, w1 = q1+w;
            for (int q2 = q1; q2 < w1; q2++, q3 += len) {
                int x = a[q2], y = a[q2+w];
                a[q2] = (x+deg[q3]*y) % C;
                a[q2+w] = (x-deg[q3]*y+C_2) % C;
            }
        }
    }
    return a;
}

vector<int> IFFT(vector<int> &a) {
    a = FFT(a);
    int rev_n = pow1(a.size(), C-2);
    reverse(a.begin()+1, a.end());
    for (int &q : a) {
        q = q*rev_n % C;
    }
    return a;
}

void preculc(int n) {
    int g = find_g(), w = pow1(g, (C-1)/n);
    deg = {1};
    for (int q = 1; q < n; q++) {
        deg.push_back(deg.back()*w % C);
    }
    int now = 0, q2 = 1, q3 = 0;
    while (q2 < n) {
        q2 *= 2, q3++;
    }
    rev.assign(n, 0);
    for (int q = 1; q < n; q++) {
        if (q == (1 << (now+1))) {
            now++;
        }
        rev[q] = rev[q-(1 << now)]+(1 << (q3-now-1));
    }
}

void to_norm(vector<int> &a, int n) {
    reverse(a.begin(), a.end());
    while (a.size() < n) {
        a.push_back(0);
    }
}

void from_norm(vector<int> &a) {
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    reverse(a.begin(), a.end());
}

vector<int> mul(vector<int> a, vector<int> b) {
    int q2 = 1;
    while (q2 < max(a.size(), b.size())) {
        q2 *= 2;
    }
    q2 *= 2;
    preculc(q2);
    to_norm(a, q2), to_norm(b, q2);
    a = FFT(a), b = FFT(b);
    vector<int> ans(q2);
    for (int q = 0; q < q2; q++) {
        ans[q] = a[q]*b[q];
    }
    ans = IFFT(ans);
    from_norm(ans);
    return ans;
}

void to_number(vector<int> &a) {
    to_norm(a, a.size()+20);
    int plus1 = 0;
    for (int &q : a) {
        q += plus1 % 10;
        plus1 /= 10, plus1 += q/10;
        q %= 10;
    }
    from_norm(a);
}
