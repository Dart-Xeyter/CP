#define ld double
#define Complex complex<ld>

const ld PI = acosl(-1);
vector<vector<int>> reversed;
vector<vector<Complex>> roots;

int reverse_bits(int x, int len) {
    int y = 0;
    for (int q = 0; q < len; q++) {
        y |= (((x >> q) & 1) << (len-q-1));
    }
    return y;
}

void FFT(vector<Complex> &a) {
    int n = a.size(), len = 0;
    while ((1 << len) < n) {
        len++;
    }
    for (int q = 0; q < n; q++) {
        if (q < reversed[len][q]) {
            swap(a[q], a[reversed[len][q]]);
        }
    }
    len = 0;
    for (int q = 1; q < n; q <<= 1, len++) {
        for (int q1 = 0; q1 < n; q1 += (q << 1)) {
            for (int q2 = q1; q2 < q1+q; q2++) {
                Complex y = a[q2+q]*roots[len][q2-q1];
                a[q2+q] = a[q2]-y, a[q2] += y;
            }
        }
    }
}

void IFFT(vector<Complex> &a) {
    int n = a.size();
    FFT(a);
    reverse(a.begin()+1, a.end());
    for (Complex &q : a) {
        q /= n;
    }
}

vector<Complex> to_FFT_form(const vector<int> &a, int deg) {
    vector<Complex> A;
    for (int q : a) {
        A.push_back(Complex{(ld)q, 0});
    }
    while (A.size() < deg) {
        A.push_back(Complex{0, 0});
    }
    return A;
}

vector<int> from_FFT_form(const vector<Complex> &A) {
    vector<int> a;
    for (const Complex &q : A) {
        a.push_back(round(q.real()));
    }
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
    return a;
}

int get_degree(int n) {
    int deg = 1;
    while (deg < n) {
        deg <<= 1;
    }
    return deg;
}

void FFT_preculc(int n) {
    reversed = {}, roots = {};
    int deg = get_degree(n);
    for (int q = 0; (1 << q) <= deg; q++) {
        reversed.emplace_back();
        for (int q1 = 0; q1 < (1 << q); q1++) {
            reversed.back().push_back(reverse_bits(q1, q));
        }
    }
    for (int q = 1; q < deg; q <<= 1) {
        roots.emplace_back();
        Complex root{cos(PI/q), sin(PI/q)};
        Complex now{1, 0};
        for (int q1 = 0; q1 < q; q1++) {
            roots.back().push_back(now);
            now = now*root;
        }
        roots.back().push_back(now);
    }
}

vector<int> mul(const vector<int> &a, const vector<int> &b) {
    int deg = get_degree(a.size()+b.size());
    FFT_preculc(deg);
    vector<Complex> A = to_FFT_form(a, deg);
    vector<Complex> B = to_FFT_form(b, deg);
    FFT(A), FFT(B);
    vector<Complex> C(deg);
    for (int q = 0; q < deg; q++) {
        C[q] = A[q]*B[q];
    }
    IFFT(C);
    return from_FFT_form(C);
}

vector<int> to_polynomial(const string &n, int digit = 2) {
    int len = n.size();
    vector<int> a;
    for (int q = 0; q < len; q++) {
        if (q == 0 || q % digit == len % digit) {
            a.push_back(0);
        }
        a.back() *= 10, a.back() += n[q]-'0';
    }
    reverse(a.begin(), a.end());
    return a;
}

string to_number(const vector<int> &a, int digit = 2) {
    string n;
    int x = 0;
    for (int q = 0; q < a.size() || x > 0; q++) {
        x += (q < a.size() ? a[q] : 0);
        for (int q1 = 0; q1 < digit; q1++) {
            n += '0'+x % 10;
            x /= 10;
        }
    }
    while (n.size() > 1 && n.back() == '0') {
        n.pop_back();
    }
    reverse(n.begin(), n.end());
    return n;
}

