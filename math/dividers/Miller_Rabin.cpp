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

bool Miller_Rabin_test(int n) {
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
        if (!Miller_Rabin_test(n)) {
            return false;
        }
    }
    return true;
}

