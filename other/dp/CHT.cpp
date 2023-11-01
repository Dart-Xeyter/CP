#define ld long double
const ld E = 1e-8;

struct Line {
    int k, b;

    int value(int x) const {
        return k*x+b;
    }

    ld value(ld x) const {
        return k*x+b;
    }
};

ld inter(Line a, Line b) {
    return (ld)(b.b-a.b)/(a.k-b.k);
}

struct CHT { // max, different angles
    deque<pair<Line, ld>> a;

    void add_increasing(Line line) {
        while (a.size() > 1 && a.back().first.value(a.back().second)-E < line.value(a.back().second)) {
            a.pop_back();
        }
        if (a.empty()) {
            a.emplace_back(line, -INF);
        } else {
            a.emplace_back(line, inter(a.back().first, line));
        }
    }

    void add_decreasing(Line line) {
        while (a.size() > 1 && a[1].first.value(a[1].second)-E < line.value(a[1].second)) {
            a.pop_front();
        }
        if (!a.empty()) {
            a[0].second = inter(a[0].first, line);
        }
        a.emplace_front(line, -INF);
    }

    int ans(int x) const {
        auto w = --lower_bound(a.begin(), a.end(), x, [](pair<Line, ld> x, ld y) {return x.second < y;});
        return w->first.value(x);
    }
};

