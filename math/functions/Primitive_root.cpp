int pow1(int x, int y, int C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2, C);
    }
    return pow1(x, y-1, C)*x % C;
}

vector<int> factor(int n) {
    vector<int> primes;
    int sqrt1 = sqrt(n);
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

int phi(int n) {
    vector<int> fact = factor(n);
    int ans = n;
    for (int q : fact) {
        ans -= ans/q;
    }
    return ans;
}

int find_g(int C) {
    int phi_C = phi(C);
    vector<int> primes = factor(phi_C);
    for (int q = 1;; q++) {
        bool flag = true;
        for (int q1 : primes) {
            if (pow1(q, phi_C/q1, C) == 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return q;
        }
    }
}

int g_degree(int x, int g, int C) {
    int sqrt1 = sqrt(C);
    unordered_map<int, int> a;
    a.reserve(sqrt1);
    int now = 1;
    for (int q = 0; q < sqrt1; q++) {
        a[now] = q;
        now = now*g % C;
    }
    int rev_sqrt = pow1(now, C-2, C);
    for (int q = 0; q <= C/sqrt1; q++) {
        if (a.find(x) != a.end()) {
            return q*sqrt1+a[x];
        }
        x = x*rev_sqrt % C;
    }
    return -1;
}

