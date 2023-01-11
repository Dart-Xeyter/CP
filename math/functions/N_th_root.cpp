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

int find_g(int C) {
    vector<int> primes = factor(C-1);
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

int phi(int n) {
    vector<int> fact = factor(n);
    int ans = n;
    for (int q : fact) {
        ans -= ans/q;
    }
    return ans;
}

p ax_by_c(int a, int b, int c) {
    int t = __gcd(a, b);
    if (c % t != 0) {
        return {-1, -1};
    }
    a /= t, b /= t, c /= t;
    int x = (c*pow1(a, phi(b)-1, b) % b+b) % b;
    int y = (c-a*x)/b;
    return {x, y};
}

int sqrt_b(int a, int b, int C) {
    if (a == 0) {
        return 0;
    }
    int g = find_g(C);
    int deg_a = g_degree(a, g, C);
    int x = ax_by_c(b, C-1, deg_a).first;
    return (x == -1 ? -1 : pow1(g, x, C));
}

