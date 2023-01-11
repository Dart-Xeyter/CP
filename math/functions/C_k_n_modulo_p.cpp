int pow1(int x, int y, int C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % C, y/2, C);
    }
    return pow1(x, y-1, C)*x % C;
}

vector<int> fact, rev_fact;

void make_fact(int C) {
    fact = {1};
    for (int q = 1; q < C; q++) {
        fact.push_back(fact.back()*q % C);
    }
    rev_fact = {pow1(fact.back(), C-2, C)};
    for (int q = C-1; q > 0; q--) {
        rev_fact.push_back(rev_fact.back()*q % C);
    }
    reverse(rev_fact.begin(), rev_fact.end());
}

int get_fact(int n, int C) {
    if (n < C) {
        return fact[n];
    }
    int ans = fact[n % C]*pow1(fact.back(), n/C, C) % C;
    return ans*get_fact(n/C, C) % C;
}

int get_rev_fact(int n, int C) {
    if (n < C) {
        return rev_fact[n];
    }
    int ans = rev_fact[n % C]*pow1(rev_fact.back(), n/C, C) % C;
    return ans*get_rev_fact(n/C, C) % C;
}

int p_degree(int n, int C) {
    int ans = 0, deg = C;
    while (deg <= n) {
        ans += n/deg, deg *= C;
    }
    return ans;
}

int C_k_n(int k, int n, int C) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (p_degree(n, C) > p_degree(k, C)+p_degree(n-k, C)) {
        return 0;
    }
    return get_fact(n, C)*get_rev_fact(k, C) % C*get_rev_fact(n-k, C) % C;
}

