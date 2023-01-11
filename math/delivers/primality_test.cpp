bool is_prime(int n) {
    if (n == 1) {
        return false;
    }
    int sqrt1 = sqrt(n);
    for (int q = 2; q <= sqrt1; q++) {
        if (n % q == 0) {
            return false;
        }
    }
    return true;
}

