#define ld long double
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

