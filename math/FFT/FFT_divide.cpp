int pow1(int x, int y, int C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2, C);
    }
    return pow1(x, y-1, C)*x % C;
}

#define ld double
const ld PI = acosl(-1);

int reverse_bits(int x, int len) {
    int y = 0;
    for (int q = 0; q < len; q++) {
        y |= (((x >> q) & 1) << (len-q-1));
    }
    return y;
}

void FFT(vector<complex<ld>> &a) {
    int n = a.size(), len = 1;
    while ((1 << len) < n) {
        len++;
    }
    for (int q = 0; q < n; q++) {
        int q1 = reverse_bits(q, len);
        if (q < q1) {
            swap(a[q], a[q1]);
        }
    }
    for (int q = 1; q < n; q <<= 1) {
        complex<ld> root(cosl(PI/q), sinl(PI/q));
        for (int q1 = 0; q1 < n; q1 += (q << 1)) {
            complex<ld> now = 1;
            for (int q2 = q1; q2 < q1+q; q2++) {
                complex<ld> x = a[q2], y = a[q2+q]*now;
                a[q2] = x+y, a[q2+q] = x-y;
                now *= root;
            }
        }
    }
}

void IFFT(vector<complex<ld>> &a) {
    int n = a.size();
    FFT(a);
    reverse(a.begin()+1, a.end());
    for (complex<ld> &q : a) {
        q /= n;
    }
}

vector<complex<ld>> to_FFT_form(const vector<int> &a, int deg) {
    vector<complex<ld>> A;
    for (int q : a) {
        A.push_back(q);
    }
    while (A.size() < deg) {
        A.push_back(0);
    }
    return A;
}

vector<int> from_FFT_form(const vector<complex<ld>> &A) {
    vector<int> a;
    for (const complex<ld> &q : A) {
        a.push_back(roundl(q.real()));
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return a;
}

vector<int> multiply(const vector<int> &a, const vector<int> &b, int MOD) {
    int deg = 1;
    while (deg < a.size()+b.size()) {
        deg <<= 1;
    }
    vector<complex<ld>> A = to_FFT_form(a, deg);
    vector<complex<ld>> B = to_FFT_form(b, deg);
    FFT(A), FFT(B);
    vector<complex<ld>> C(deg);
    for (int q = 0; q < deg; q++) {
        C[q] = A[q]*B[q];
    }
    IFFT(C);
    vector<int> c = from_FFT_form(C);
    for (int &q : c) {
        q %= MOD;
    }
    return c;
}

void fix_zeros(vector<int> &a, int n) {
    while (a.size() < n) {
        a.push_back(0);
    }
    while (a.size() > n && a.back() == 0) {
        a.pop_back();
    }
}

void modulo_x_n(vector<int> &a, int n) {
    while (a.size() < n) {
        a.push_back(0);
    }
    while (a.size() > n) {
        a.pop_back();
    }
}

int get_degree(int n) {
    int deg = 1;
    while (deg < n) {
        deg <<= 1;
    }
    return deg;
}

vector<int> opposite(vector<int> a, int MOD) {
    for (int &q : a) {
        q = (MOD-q) % MOD;
    }
    return a;
}

vector<int> find_reversed(vector<int> &a, int n, int MOD) {
    if (n == 1) {
        if (a[0] == 0) {
            exit(179);
        }
        return {pow1(a[0], MOD-2, MOD)};
    }
    vector<int> a0, a1;
    for (int q = 0; q < n/2; q++) {
        a0.push_back(a[q]);
    }
    for (int q = n/2; q < n; q++) {
        a1.push_back(a[q]);
    }
    vector<int> rev_a0 = find_reversed(a0, n/2, MOD);
    vector<int> Q = multiply(a0, rev_a0, MOD);
    fix_zeros(Q, n);
    reverse(Q.begin(), Q.end());
    modulo_x_n(Q, n/2);
    reverse(Q.begin(), Q.end());
    vector<int> rev_a0_by_a1 = multiply(rev_a0, a1, MOD);
    modulo_x_n(rev_a0_by_a1, n/2);
    for (int q = 0; q < n/2; q++) {
        Q[q] += rev_a0_by_a1[q];
    }
    vector<int> E = multiply(rev_a0, Q, MOD);
    modulo_x_n(E, n/2);
    E = opposite(E, MOD);
    for (int q : E) {
        rev_a0.push_back(q);
    }
    return rev_a0;
}

vector<int> reverse(vector<int> a, int n, int MOD) {
    int deg = get_degree(n);
    fix_zeros(a, deg);
    vector<int> rev = find_reversed(a, deg, MOD);
    modulo_x_n(rev, n);
    return rev;
}

vector<int> divide(vector<int> a, vector<int> b, int MOD) {
    if (a.size() < b.size() || a.size() == 1 && a[0] == 0) {
        return {0};
    }
    if (b.size() == 1 && b[0] == 0) {
        exit(179);
    }
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int> rev = reverse(b, (int)a.size()-(int)b.size()+1, MOD);
    vector<int> c = multiply(a, rev, MOD);
    modulo_x_n(c, (int)a.size()-(int)b.size()+1);
    reverse(c.begin(), c.end());
    return c;
}

vector<int> add(const vector<int> &a, const vector<int> &b, int MOD) {
    int n = a.size(), m = b.size();
    vector<int> c(max(n, m));
    for (int q = 0; q < max(n, m); q++) {
        c[q] = ((q < n ? a[q] : 0)+(q < m ? b[q] : 0)) % MOD;
    }
    fix_zeros(c, 1);
    return c;
}

vector<int> subtract(const vector<int> &a, const vector<int> &b, int MOD) {
    return add(a, opposite(b, MOD), MOD);
}

vector<int> take_remainder(const vector<int> &a, const vector<int> &b, int MOD) {
    vector<int> divider = divide(a, b, MOD);
    return subtract(a, multiply(b, divider, MOD), MOD);
}

vector<int> pow(vector<int> P, vector<int> mod, int n, int MOD) {
    if (n == 0) {
        return {1};
    }
    if (n % 2 == 0) {
        return pow(take_remainder(multiply(P, P, MOD), mod, MOD), mod, n/2, MOD);
    }
    return take_remainder(multiply(pow(P, mod, n-1, MOD), P, MOD), mod, MOD);
}

