int pow1(int x, int y, int C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2, C);
    }
    return pow1(x, y-1, C)*x % C;
}

vector<int> get_primes(int n) {
    vector<int> primes;
    int sqrt1 = sqrtl(n);
    for (int q = 2; q <= sqrt1; q++) {
        if (n % q == 0) {
            primes.push_back(q);
        }
        while (n % q == 0) {
            n /= q;
        }
    }
    if (n > 1) {
        primes.push_back(n);
    }
    return primes;
}

int find_g(int C) {
    vector<int> primes = get_primes(C-1);
    for (int q = 1;; q++) {
        bool flag = true;
        for (int q1 : primes) {
            if (pow1(q, (C-1)/q1, C) == 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return q;
        }
    }
}

int reverse_bits(int x, int log1) {
    int y = 0;
    for (int q = 0; q < log1; q++) {
        y |= (((x >> q) & 1) << (log1-q-1));
    }
    return y;
}

void FFT(vector<int> &a, int C, int g, int log1) {
    int n = a.size();
    vector<bool> good(n, true);
    for (int q = 0; q < n; q++) {
        if (good[q]) {
            int q1 = reverse_bits(q, log1);
            swap(a[q], a[q1]);
            good[q1] = false;
        }
    }
    for (int q = 1; q < n; q <<= 1) {
        int root = pow1(g, (C-1)/(q << 1), C);
        for (int q1 = 0; q1 < n; q1 += (q << 1)) {
            int now = 1;
            for (int q2 = q1; q2 < q1+q; q2++) {
                int x = a[q2], y = a[q2+q]*now % C;
                a[q2] = x+y-(x+y >= C)*C, a[q2+q] = x-y+(x-y < 0)*C;
                now = now*root % C;
            }
        }
    }
}

void IFFT(vector<int> &a, int C, int g, int log1) {
    FFT(a, C, g, log1);
    reverse(a.begin()+1, a.end());
    int rev_n = pow1(a.size(), C-2, C);
    for (int &q : a) {
        q = q*rev_n % C;
    }
}

int get_degree(int n) {
    int log1 = 0;
    while ((1 << log1) < n) {
        log1++;
    }
    return log1;
}

vector<int> multiply(vector<int> a, vector<int> b, int C) {
    int log1 = get_degree(a.size()+b.size());
    int n = (1 << log1), g = find_g(C);
    a.resize(n, 0), b.resize(n, 0);
    FFT(a, C, g, log1), FFT(b, C, g, log1);
    for (int q = 0; q < n; q++) {
        a[q] = a[q]*b[q] % C;
    }
    IFFT(a, C, g, log1);
    auto w = find_if_not(a.rbegin(), a.rend(), [](int x) {return x == 0;});
    a.resize(max(1LL, (int)(a.rend()-w)));
    return a;
}

