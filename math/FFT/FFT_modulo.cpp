const int g = 31;
vector<int> rev_bits;

int reverse_bits(int x, int log1) {
    int y = 0;
    for (int q = 0; q < log1; q++) {
        y |= (((x >> q) & 1) << (log1-q-1));
    }
    return y;
}

void build_rev_bits(int log1) {
    int n = (1 << log1);
    rev_bits.assign(n, -1);
    for (int q = 0; q < n; q++) {
        int q1 = reverse_bits(q, log1);
        rev_bits[q] = min(q, q1);
    }
}

void FFT(int* a, int log1) {
    int n = (1 << log1);
    for (int q = 0; q < n; q++) {
        swap(a[q], a[rev_bits[q]]);
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

void IFFT(int* a, int log1) {
    int n = (1 << log1);
    FFT(a, log1);
    reverse(a+1, a+n);
    int rev_n = pow1(n, C-2);
    for (int q = 0; q < n; q++) {
        a[q] *= rev_n, a[q] %= C;
    }
}

int get_degree(int n) {
    int log1 = 0;
    while ((1 << log1) < n) {
        log1++;
    }
    return log1;
}

vector<int> multiply(vector<int>& aa, vector<int>& bb) {
    int len = (int)aa.size()+(int)bb.size()-1;
    int log1 = get_degree(len), n = (1 << log1);
    build_rev_bits(log1);
    int a[n], b[n];
    fill(a, a+n, 0), fill(b, b+n, 0);
    copy(aa.begin(), aa.end(), a);
    copy(bb.begin(), bb.end(), b);
    FFT(a, log1), FFT(b, log1);
    for (int q = 0; q < n; q++) {
        a[q] = a[q]*b[q] % C;
    }
    IFFT(a, log1);
    vector<int> ans(a, a+len);
    return ans;
}

