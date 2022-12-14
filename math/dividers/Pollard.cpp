mt19937 randint(179);

__int128 pow1(__int128 x, __int128 y, __int128 z) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % z, y/2, z);
    }
    return pow1(x, y-1, z)*x % z;
}

bool Milner_Rabin_test(int n) {
    __int128 a = randint() % (n-1)+1;
    int u = 0, now = n-1;
    while (now % 2 == 0) {
        now /= 2, u++;
    }
    a = pow1(a, now, n);
    if (a == 1) {
        return true;
    }
    for (int q = 0; q < u; q++) {
        if (a == n-1) {
            return true;
        }
        a = a*a % n;
    }
    return false;
}

bool is_prime(int n, int C = 30) {
    if (n == 2 || n == 3 || n == 5 || n == 7) {
        return true;
    }
    if (n == 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) {
        return false;
    }
    for (int q = 0; q < C; q++) {
        if (!Milner_Rabin_test(n)) {
            return false;
        }
    }
    return true;
}

int func(__int128 x, int n) {
    return (x*x+1) % n;
}

vector<int> Pollard(int n) {
    vector<int> primes = {2, 3, 5, 7}, for_fact, ans;
    for (int q1 : primes) {
        while (n % q1 == 0) {
            ans.push_back(q1);
            n /= q1;
        }
    }
    if (n == 1) {
        return ans;
    }
    for_fact.push_back(n);
    while (!for_fact.empty()) {
        n = for_fact.back();
        for_fact.pop_back();
        if (is_prime(n)) {
            ans.push_back(n);
            continue;
        }
        while (true) {
            int x = randint() % n, y = x, t = 1;
            while (t == 1) {
                x = func(x, n), y = func(func(y, n), n);
                t = __gcd((x >= y ? x-y : y-x), n);
            }
            if (t != n) {
                for_fact.push_back(t);
                for_fact.push_back(n/t);
                break;
            }
        }
    }
    return ans;
}

