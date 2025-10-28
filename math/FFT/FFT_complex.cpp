const ld PI = numbers::pi_v<ld>;
using Complex = complex<ld>;

int reverse_bits(int x, int log1) {
    int y = 0;
    for (int q = 0; q < log1; q++) {
        y |= (((x >> q) & 1) << (log1-q-1));
    }
    return y;
}

vector<int> rev_bits;

void build_rev_bits(int log1) {
    int n = (1 << log1);
    rev_bits.assign(n, -1);
    for (int q = 0; q < n; q++) {
        int q1 = reverse_bits(q, log1);
        rev_bits[q] = min(q, q1);
    }
}

void FFT(vector<Complex>& a, int log1) {
    int n = (1 << log1);
    for (int q = 0; q < n; q++) {
        swap(a[q], a[rev_bits[q]]);
    }
    for (int q = 1; q < n; q <<= 1) {
        Complex root(cosl(PI/q), sinl(PI/q));
        for (int q1 = 0; q1 < n; q1 += (q << 1)) {
            Complex now = 1;
            for (int q2 = q1; q2 < q1+q; q2++) {
                Complex x = a[q2], y = a[q2+q]*now;
                a[q2] = x+y, a[q2+q] = x-y;
                now *= root;
            }
        }
    }
}

void IFFT(vector<Complex>& a, int log1) {
    int n = (1 << log1);
    FFT(a, log1);
    reverse(a.begin()+1, a.end());
    for (Complex& q : a) {
        q /= n;
    }
}

int get_degree(int n) {
    int log1 = 0;
    while ((1 << log1) < n) {
        log1++;
    }
    return log1;
}

vector<Complex> multiply(vector<Complex> a, vector<Complex> b) {
    int len = (int)a.size()+(int)b.size()-1;
    int log1 = get_degree(len), n = (1 << log1);
    build_rev_bits(log1);
    a.resize(n, 0), b.resize(n, 0);
    FFT(a, log1), FFT(b, log1);
    for (int q = 0; q < n; q++) {
        a[q] = a[q]*b[q];
    }
    IFFT(a, log1);
    return {a.begin(), a.begin()+len};
}

