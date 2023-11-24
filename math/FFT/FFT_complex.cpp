#define ld long double
const ld PI = numbers::pi_v<ld>;

int reverse_bits(int x, int len) {
    int y = 0;
    for (int q = 0; q < len; q++) {
        y |= (((x >> q) & 1) << (len-q-1));
    }
    return y;
}

void FFT(vector<complex<ld>> &a) {
    int n = (int)a.size(), len = 1;
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
    int n = (int)a.size();
    FFT(a);
    reverse(a.begin()+1, a.end());
    for (complex<ld> &q : a) {
        q /= n;
    }
}

vector<complex<ld>> to_FFT_form(const vector<int> &a, int deg) {
    vector<complex<ld>> A;
    for (int q : a) {
        A.emplace_back(q);
    }
    while (A.size() < deg) {
        A.emplace_back(0);
    }
    return A;
}

vector<int> from_FFT_form(const vector<complex<ld>> &A) {
    vector<int> a;
    for (const complex<ld> &q : A) {
        a.emplace_back(roundl(q.real()));
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return a;
}

vector<int> mul(const vector<int> &a, const vector<int> &b) {
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
    return from_FFT_form(C);
}

vector<int> mul(const vector<int>& a, int x) {
    vector<int> ans = a;
    for (int& q : ans) {
        q *= x;
    }
    return ans;
}

vector<int> add(const vector<int>& a, const vector<int>& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<int> c(max(n, m));
    for (int q = 0; q < max(n, m); q++) {
        c[q] = (q < n ? a[q] : 0)+(q < m ? b[q] : 0);
    }
    return c;
}

vector<int> multiply(vector<int> a, vector<int> b, int parts = 1, int max_value = INF) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> first(parts), second(parts);
    for (int q1 = 0; q1 < parts; q1++) {
        for (int q = 0; q < n; q++) {
            first[q1].push_back(a[q] % max_value);
            a[q] /= max_value;
        }
        for (int q = 0; q < m; q++) {
            second[q1].push_back(b[q] % max_value);
            b[q] /= max_value;
        }
    }
    vector<int> degs = {1}, ans;
    for (int q = 1; q < 2*parts-1; q++) {
        degs.push_back(degs.back()*max_value);
    }
    for (int q = 0; q < parts; q++) {
        for (int q1 = 0; q1 < parts; q1++) {
            vector<int> now = mul(first[q], second[q1]);
            ans = add(ans, mul(now, degs[q+q1]));
        }
    }
    return ans;
}

vector<int> to_polynomial(const string &n) {
    vector<int> a;
    for (char q : n) {
        a.push_back(q-'0');
    }
    reverse(a.begin(), a.end());
    return a;
}

string to_number(const vector<int> &a) {
    string n;
    int x = 0;
    for (int q = 0; q < a.size() || x > 0; q++) {
        x += (q < a.size() ? a[q] : 0);
        n += '0'+x % 10;
        x /= 10;
    }
    reverse(n.begin(), n.end());
    return n;
}

