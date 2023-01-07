struct Ln {
    int k, b;

    Ln(int k1, int b1) : k(k1), b(b1) {}
};

int value(Ln line, int x) {
    return line.k*x+line.b;
}

int inter(Ln line, Ln line1) {
    if (line.k == line1.k) {
        exit(179);
    }
    return (line1.b-line.b)/(line.k-line1.k)-(line1.b < line.b && (line1.b-line.b) % (line.k-line1.k) != 0);
}

struct CHT{
    vector<pair<Ln, int>> a;

    void add(Ln line) {
        while (!a.empty() && a.back().first.k == line.k && a.back().first.b >= line.b) {
            a.pop_back();
        }
        if (a.empty()) {
            a.push_back({line, -INF});
            return;
        }
        if (a.back().first.k == line.k) {
            return;
        }
        while (value(a.back().first, a.back().second) > value(line, a.back().second)) {
            a.pop_back();
        }
        while (!a.empty() && inter(a.back().first, line) <= -INF) {
            a.pop_back();
        }
        int x = inter(a.back().first, line);
        if (x < INF) {
            a.push_back({line, x});
        }
    }

    int ans(int x) {
        auto w = --lower_bound(a.begin(), a.end(), x, [](pair<Ln, int> x, int y){return x.second < y;});
        return value(w->first, x);
    }
};

