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

