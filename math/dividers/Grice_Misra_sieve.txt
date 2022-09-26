vector<int> Grice_Misra_sieve(int n) {
    vector<int> primes, lcp(n+1, 0);
    for (int q = 2; q <= n; q++) {
        if (lcp[q] == 0) {
            lcp[q] = q;
            primes.push_back(q);
        }
        for (int q1 = 0; q1 < primes.size() && primes[q1] <= lcp[q] && q*primes[q1] <= n; q1++) {
            lcp[q*primes[q1]] = primes[q1];
        }
    }
    return lcp;
}
