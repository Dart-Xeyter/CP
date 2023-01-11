int pow1(int x, int y, int C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2, C);
    }
    return pow1(x, y-1, C)*x % C;
}

int phi(int n, const vector<int> primes) {
    int ans = n;
    for (int q : primes) {
        ans -= ans/q;
    }
    return ans;
}

vector<int> fact, rev_fact;

void make_fact(int n, int C, vector<int> primes) {
    fact = {1};
    vector<int> numbers = {0};
    for (int q = 1; q <= n; q++) {
        int now = q;
        for (int q1 : primes) {
            while (now % q1 == 0) {
                now /= q1;
            }
        }
        fact.push_back(fact.back()*now % C);
        numbers.push_back(now);
    }
    rev_fact = {pow1(fact.back(), phi(C, primes)-1, C)};
    for (int q = min(n, C-1); q > 0; q--) {
        rev_fact.push_back(rev_fact.back()*numbers[q] % C);
    }
    reverse(rev_fact.begin(), rev_fact.end());
}

int p_degree(int n, int C) {
    int ans = 0, deg = C;
    while (deg <= n) {
        ans += n/deg, deg *= C;
    }
    return ans;
}

int C_k_n(int k, int n, int C, vector<int> primes) {
    int ans = fact[n]*rev_fact[k] % C*rev_fact[n-k] % C;
    for (int q : primes) {
        int deg = p_degree(n, q)-p_degree(k, q)-p_degree(n-k, q);
        ans = ans*pow1(q, deg, C) % C;
    }
    return ans;
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

