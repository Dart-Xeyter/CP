const int C = 1000000007;
vector<int> fact, rev_fact;

int pow1(int x, int y, int z = C) {
    if (y == 0) {
        return 1;
    }
    if (y % 2 == 0) {
        return pow1(x*x % z, y/2, z);
    }
    return pow1(x, y-1, z)*x % z;
}

void make_fact(int n) {
    fact = {1};
    for (int q = 1; q <= n; q++) {
        fact.push_back(fact.back()*q % C);
    }
    rev_fact = {pow1(fact.back(), C-2, C)};
    for (int q = n; q > 0; q--) {
        rev_fact.push_back(rev_fact.back()*q % C);
    }
    reverse(rev_fact.begin(), rev_fact.end());
}

int C_n_k(int k, int n) {
    if (k < 0 || k > n) {
        return 0;
    }
    return fact[n]*rev_fact[k] % C*rev_fact[n-k] % C;
}
