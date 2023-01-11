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

int reverse_bits(int x, int len) {
    int y = 0;
    for (int q = 0; q < len; q++) {
        y |= (((x >> q) & 1) << (len-q-1));
    }
    return y;
}

void FFT(vector<int> &a, int C) {
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
    int g = find_g(C);
    for (int q = 1; q < n; q <<= 1) {
        int root = pow1(g, (C-1)/(q << 1), C);
        for (int q1 = 0; q1 < n; q1 += (q << 1)) {
            int now = 1;
            for (int q2 = q1; q2 < q1+q; q2++) {
                int x = a[q2], y = a[q2+q]*now % C;
                a[q2] = (x+y) % C, a[q2+q] = (x-y+C) % C;
                now = now*root % C;
            }
        }
    }
}

void IFFT(vector<int> &a, int C) {
    int n = a.size();
    FFT(a, C);
    reverse(a.begin()+1, a.end());
    for (int &q : a) {
        q = q*pow1(n, C-2, C) % C;
    }
}

void fix_polynomial(vector<int> &a, int n, int C) {
    while (a.size() < n) {
        a.push_back(0);
    }
    while (a.size() > n && a.back() == 0) {
        a.pop_back();
    }
    for (int &q : a) {
        q = (q % C+C) % C;
    }
}

int get_degree(int n) {
    int deg = 1;
    while (deg < n) {
        deg <<= 1;
    }
    return deg;
}

vector<int> multiply(vector<int> a, vector<int> b, int C) {
    int deg = get_degree(a.size()+b.size());
    fix_polynomial(a, deg, C), fix_polynomial(b, deg, C);
    FFT(a, C), FFT(b, C);
    for (int q = 0; q < deg; q++) {
        a[q] = a[q]*b[q] % C;
    }
    IFFT(a, C);
    fix_polynomial(a, 1, C);
    return a;
}

