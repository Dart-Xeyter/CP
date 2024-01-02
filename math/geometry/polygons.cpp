#define ld long double

struct Pt {
    int x, y;

    Pt(): x(0), y(0) {}
    Pt(int x, int y): x(x), y(y) {}

    auto operator<=>(const Pt& other) const = default;

    Pt operator+(const Pt& point) const {
        return {x+point.x, y+point.y};
    }

    Pt operator-(const Pt& point) const {
        return {x-point.x, y-point.y};
    }
};

istream& operator>>(istream& in, Pt& point) {
    in >> point.x >> point.y;
    return in;
}

ostream& operator<<(ostream& out, const Pt& point) {
    out << point.x << ' ' << point.y;
    return out;
}

int dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

int cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

ld abs(Pt x) {
    return hypot(x.x, x.y);
}

int abs_2(Pt x) {
    return x.x*x.x+x.y*x.y;
}

ld dist(Pt x, Pt y) {
    return abs(x-y);
}

int dist_2(Pt x, Pt y) {
    return abs_2(x-y);
}

ld angle(Pt x, Pt y) {
    // angle between (1, 0) и (sin, cos)
    return atan2(cross(x, y), dot(x, y));
}

bool on_line(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x) == 0;
}

struct Seg {
    Pt x, y;

    Seg(Pt x, Pt y): x(x), y(y) {}

    auto operator<=>(const Seg& other) const = default;

    explicit operator bool() const {
        return x != y;
    }
};

bool on_seg(Seg q, Pt point) {
    return on_line(q.x, q.y, point) && dot(point-q.x, point-q.y) <= 0;
}

int S_tr_2(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x);
}

struct Polygon {
    vector<Pt> a;

    explicit Polygon(vector<Pt> a_ = {}): a(std::move(a_)) {
        if (a.empty()) {
            return;
        }
        normalize();
        if (a.size() > 1) {
            a.push_back(a[0]);
        }
    }

    void counterclockwise() {
        if (S_2() < 0) {
            reverse(a.begin(), a.end());
        }
    }

    void normalize() {
        int n = (int)a.size();
        int ind = 1;
        while (ind < n-1 && on_line(a[0], a[ind], a[ind+1])) {
            ind++;
        }
        if (ind >= n-1) {
            Pt min1 = *min_element(a.begin(), a.end());
            Pt max1 = *max_element(a.begin(), a.end());
            a = (min1 == max1 ? vector{min1} : vector{min1, max1});
            return;
        }
        rotate(a.begin(), a.begin()+ind, a.end());
        a.push_back(a[0]);
        vector<Pt> will_a = {a[0]};
        for (int q = 1; q < n; q++) {
            if (!on_line(will_a.back(), a[q], a[q+1])) {
                will_a.push_back(a[q]);
            }
        }
        a = will_a;
    }

    vector<Seg> get_edges() const {
        int n = (int)a.size();
        vector<Seg> edges;
        for (int q = 1; q < n; q++) {
            edges.emplace_back(a[q-1], a[q]);
        }
        return edges;
    }

    bool on_border(Pt point) const {
        return ranges::any_of(get_edges(), [point](Seg q) {return on_seg(q, point);});
    }

    int belonging(Pt point) const { // 0 -> out, 1 -> in, 2 -> border
        if (on_border(point)) {
            return 2;
        }
        ld ang = 0;
        for (Seg q : get_edges()) {
            ang += angle(q.x-point, q.y-point);
        }
        // will be 0 or 2*pi
        return abs(ang) > numbers::pi_v<ld>;
    }

    int S_2() const {
        int ans = 0;
        for (Seg q : get_edges()) {
            ans += S_tr_2(a[0], q.x, q.y);
        }
        return ans;
    }
};

bool need_pop_back(Pt x, vector<Pt>& ans, bool up) {
    int m = (int)ans.size(), sign = 2*up-1;
    return m >= 2 && cross(ans[m-1]-ans[m-2], x-ans[m-2])*sign >= 0;
}

void make_envelope(vector<Pt>& a, bool up) {
    int n = (int)a.size();
    vector<Pt> ans = {a[0]};
    for (int q = 1; q < n; q++) {
        while (need_pop_back(a[q], ans, up)) {
            ans.pop_back();
        }
        ans.push_back(a[q]);
    }
    a = ans;
}

Polygon convex_hull(vector<Pt> a) {
    int n = (int)a.size();
    sort(a.begin(), a.end());
    if (n == 0 || a[0] == a.back()) {
        return Polygon(n == 0 ? vector<Pt>{} : vector{a[0]});
    }
    vector<Pt> up = {a[0]}, down = {a[0]};
    for (int q = 1; q < n-1; q++) {
        int value = cross(a.back()-a[0], a[q]-a[0]);
        if (value > 0) {
            up.push_back(a[q]);
        } else if (value < 0) {
            down.push_back(a[q]);
        }
    }
    up.push_back(a.back());
    down.push_back(a.back());
    make_envelope(up, true);
    make_envelope(down, false);
    up.insert(up.end(), down.rbegin()+1, down.rend()-1);
    return Polygon(up);
}

