__int128 pow2(__int128 x, __int128 y, __int128 C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow2(x*x % C, y/2, C);
    }
    return pow2(x, y-1, C)*x % C;
}

bool Miller_Rabin_test(int a, int n) {
    int d = n-1;
    while ((d & 1) ^ 1) {
        d >>= 1;
    }
    __int128 now = pow2(a, d, n);
    if (now == 1) {
        return true;
    }
    while (d < n-1) {
        if (now == n-1) {
            return true;
        }
        now = now*now % n, d <<= 1;
    }
    return false;
}

mt19937 randint(17957179);

bool Miller_Rabin(int n, int k = 20) {
    if (n == 1) {
        return false;
    }
    for (int q = 0; q < k; q++) {
        if (!Miller_Rabin_test(randint() % (n-1)+1, n)) {
            return false;
        }
    }
    return true;
}

int f_Pollard(__int128 x, int n) {
    return (x*x+1) % n;
}

vector<int> make_Pollard(int n) {
    if (Miller_Rabin(n)) {
        return {n};
    }
    int x = randint() % (n-1)+1;
    int y = f_Pollard(x, n);
    while (__gcd(n, abs(y-x)) == 1) {
        x = f_Pollard(x, n);
        y = f_Pollard(f_Pollard(y, n), n);
    }
    if (x == y) {
        return make_Pollard(n);
    }
    int d = __gcd(n, abs(y-x));
    vector<int> ans = make_Pollard(d);
    for (int q : make_Pollard(n/d)) {
        ans.push_back(q);
    }
    return ans;
}

vector<int> Pollard(int n) {
    vector<int> primes, small = {2, 3, 5, 7};
    for (int q : small) {
        while (n % q == 0) {
            primes.push_back(q);
            n /= q;
        }
    }
    if (n == 1) {
        return primes;
    }
    multiset<int> all;
    for (int q : make_Pollard(n)) {
        all.insert(q);
    }
    for (int q : all) {
        primes.push_back(q);
    }
    return primes;
}

