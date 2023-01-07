vector<p> factor(int n) {
    vector<p> fact;
    int sqrt1 = sqrt(n);
    for (int q = 2; q <= sqrt1; q++) {
        if (n % q == 0) {
            fact.push_back({q, 0});
        }
        while (n % q == 0) {
            n /= q, fact.back().second++;
        }
    }
    if (n != 1) {
        fact.push_back({n, 1});
    }
    return fact;
}

vector<int> gen_dividers(vector<p> &factor) {
    vector<int> dividers = {1};
    for (p q : factor) {
        int m = dividers.size(), x = 1;
        for (int q1 = 1; q1 <= q.second; q1++) {
            x *= q.first;
            for (int q2 = 0; q2 < m; q2++) {
                dividers.push_back(dividers[q2]*x);
            }
        }
    }
    return dividers;
}
