mt19937 randint(179);
const int MN = (1LL << 20);

bool P(int x, int y, ld t) {
    ld is = exp((y-x)/t);
    return randint() % MN < is*MN;
}

int get_score(int x, vector<int>& a) {
    int ans = 0;
    for (int q : a) {
        ans += min(3LL, num_bits[q ^ x]);
    }
    return ans;
}

int delta_score(int ind, int x, vector<int> &a) {
    int score = 0, w = a[ind];
    a[ind] = x;
    score += get_score(a[ind], a);
    a[ind] = w;
    score -= get_score(a[ind], a);
    return score*2;
}

auto annealing(int n) {
    vector<int> a(1 << k);
    iota(a.begin(), a.end(), 0);
    shuffle(a.begin(), a.end(), randint);
    a.resize(n);
    int score = 0;
    for (int q : a) {
        score += get_score(q, a);
    }
    ld t = 1000, gamma = 0.999;
    ld prev_t = t;
    while (t > 0.001) {
        if (prev_t > 1.1*t) {
            cerr << t << endl;
            prev_t = t;
        }
        int ind = randint() % a.size();
        int x = randint() % (1 << k);
        int delta = delta_score(ind, x, a);
        if (delta >= 0 || P(score, score+delta, t)) {
            a[ind] = x, score += delta;
        }
        t *= gamma;
    }
    return pair{score, a};
}

