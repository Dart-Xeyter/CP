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

ld abs_of_angle(Pt x, Pt y) {
    int num = abs_2(x)+abs_2(y)-dist_2(x, y);
    ld den = 2*abs(x)*abs(y);
    ld cos_angle = min((ld)1.0, max((ld)-1.0, num/den));
    return acosl(cos_angle);
}

ld angle(Pt x, Pt y) {
    ld abs_angle = abs_of_angle(x, y);
    return cross(x, y) >= 0 ? abs_angle : -abs_angle;
}

bool on_line(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x) == 0;
}

struct Seg {
    Pt x, y;

    Seg(Pt x, Pt y): x(x), y(y) {}
};

bool on_seg(Seg q, Pt point) {
    return on_line(q.x, q.y, point) && dot(point-q.x, q.y-q.x) >= 0 && dot(point-q.y, q.x-q.y) >= 0;
}

struct Polygon {
    vector<Pt> a;

    explicit Polygon(vector<Pt> a): a(std::move(a)) {
        normalize();
    }

    void normalize() {
        int ind = 1;
        while (on_line(a[0], a[ind], a[ind+1])) {
            ind++;
        }
        rotate(a.begin(), a.begin()+ind, a.end());
        a.push_back(a[0]);
        vector<Pt> will_a = {a[0]};
        for (int q = 1; q < (int)a.size()-1; q++) {
            if (!on_line(will_a.back(), a[q], a[q+1])) {
                will_a.push_back(a[q]);
            }
        }
        a = will_a;
    }

    vector<Seg> get_edges() const {
        vector<Pt> a1 = a;
        a1.push_back(a[0]);
        vector<Seg> edges;
        for (int q = 1; q < a1.size(); q++) {
            edges.emplace_back(a1[q-1], a1[q]);
        }
        return edges;
    }

    bool on_border(Pt point) const {
        return ranges::any_of(get_edges(), [point](Seg q) {return on_seg(q, point);});
    }

    int belonging(Pt point) const {
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
};

vector<Pt> convex_hull(vector<Pt> a) {
    int n = (int)a.size();
    if (n == 0) {
        return {};
    }
    sort(a.begin(), a.end());
    vector<Pt> up = {a[0]}, down = {a[0]};
    for (int q = 1; q < n; q++) {
        while (up.size() > 1 && cross(up.back()-up[(int)up.size()-2], a[q]-up[(int)up.size()-2]) > 0) {
            up.pop_back();
        }
        up.push_back(a[q]);
        while (down.size() > 1 && cross(down.back()-down[(int)down.size()-2], a[q]-down[(int)down.size()-2]) < 0) {
            down.pop_back();
        }
        down.push_back(a[q]);
    }
    reverse(down.begin(), down.end());
    up.pop_back(), down.pop_back();
    vector<Pt> hull;
    for (Pt q : up) {
        hull.push_back(q);
    }
    for (Pt q : down) {
        hull.push_back(q);
    }
    return hull;
}

int S_tr_2(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x);
}

int S_2(vector<Pt> a) {
    int n = (int)a.size();
    a.push_back(a.back());
    int ans = 0;
    for (int q = 1; q <= n; q++) {
        ans += S_tr_2(a[0], a[q-1], a[q]);
    }
    return ans;
}

