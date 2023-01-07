int phi(int n) {
    int sqrt1 = sqrt(n), ans = 1;
    for (int q = 2; q <= sqrt1; q++) {
        if (n % q == 0) {
            ans *= q-1, n /= q;
        }
        while (n % q == 0) {
            ans *= q, n /= q;
        }
    }
    if (n != 1) {
        ans *= n-1;
    }
    return ans;
}

