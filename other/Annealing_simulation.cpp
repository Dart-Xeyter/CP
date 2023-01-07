mt19937 randint(179);

int change(int ind, vector<int> &a) {
    int x = a[ind], cost = 0;
    //code
    return cost;
}

const int MN = (1LL << 20);

bool P(int x, int y, long double t) {
    long double is = exp((y-x)/t);
    return randint() % MN < is*MN;
}

vector<int> annealing(int n) {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    long double t = 1000, gamma = 0.999;
    //vector<long double> temperature = {t};
    int cost = 0;
    while (t > 0.001 && !a.empty()) {
        /*if (temperature.back()/t > 2) {
            temperature.push_back(t);
            cout << t << endl;
        }*/
        int ind = randint() % a.size();
        int will_cost = change(ind, a);
        if (will_cost >= cost || P(cost, will_cost, t)) {
            change(ind, a);
            cost = will_cost;
        }
        t *= gamma;
    }
    return a;
}
