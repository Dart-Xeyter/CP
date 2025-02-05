const int g = 31;

int reverse_bits(int x, int log1) {
    int y = 0;
    for (int q = 0; q < log1; q++) {
        y |= (((x >> q) & 1) << (log1-q-1));
    }
    return y;
}

void FFT(vector<int>& a, int log1) {
    int n = (1 << log1);
    for (int q = 0; q < n; q++) {
        int rev = reverse_bits(q, log1);
        swap(a[q], a[min(q, rev)]);
    }
    for (int q = 1; q < n; q <<= 1) {
        int root = pow1(g, (C-1)/(q << 1));
        for (int q1 = 0; q1 < n; q1 += (q << 1)) {
            int now = 1;
            for (int q2 = q1; q2 < q1+q; q2++) {
                int x = a[q2], y = a[q2+q]*now % C;
                a[q2] = x+y-(x+y >= C)*C;
                a[q2+q] = x-y+(x-y < 0)*C;
                now = now*root % C;
            }
        }
    }
}

void IFFT(vector<int>& a, int log1) {
    int n = (1 << log1);
    FFT(a, log1);
    reverse(a.begin()+1, a.end());
    int rev_n = pow1(n, C-2);
    for (int& q : a) {
        q *= rev_n, q %= C;
    }
}

int get_degree(int n) {
    int num_zeros = __builtin_clz(n-1);
    return 32-num_zeros;
}

vector<int> multiply(vector<int> a, vector<int> b) {
    int len = (int)a.size()+(int)b.size()-1;
    int log1 = get_degree(len), n = (1 << log1);
    a.resize(n, 0), b.resize(n, 0);
    FFT(a, log1), FFT(b, log1);
    for (int q = 0; q < n; q++) {
        a[q] *= b[q], a[q] %= C;
    }
    IFFT(a, log1), a.resize(len);
    return a;
}

void add_seg(vector<int>& a, vector<int>& b, vector<int>& c, int q, int len, int r) {
    vector<int> a1(a.begin()+q-len, a.begin()+q);
    vector<int> b1(b.begin(), b.begin()+min(r, 2*len));
    vector<int> c1 = multiply(a1, b1);
    for (int q1 = 0; q1 < min(r, len); q1++) {
        c[q+q1] += c1[q1+len-1];
    }
}

vector<int> online_FFT(vector<int>& b, int c0, int n) {
    vector<int> c(2*n+1, 0); // if a == c
    c[0] = c0;
    for (int q = 1; q <= n; q++) {
        int deg = __builtin_ctz(q), len = (1 << deg);
        add_seg(c, b, c, q, len, q);
        add_seg(b, c, c, q, len, q-len);
        int rev_q = pow1(q, C-2); // for Bell's numbers
        c[q] = c[q] % C*rev_q % C;
    }
    c.resize(n+1);
    return c;
}

