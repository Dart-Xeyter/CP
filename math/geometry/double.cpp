#define ld long double
const ld E = 1e-8;

struct Pt_ld {
    ld x, y;

    Pt_ld(): x(0), y(0) {}
    Pt_ld(ld x, ld y): x(x), y(y) {}

    bool operator==(const Pt_ld& point) const {
        return abs(x-point.x) < E && abs(y-point.y) < E;
    }

    bool operator<(const Pt_ld& point) const {
        return x+E < point.x || abs(x-point.x) < E && y+E < point.y;
    }

    Pt_ld operator+(const Pt_ld& point) const {
        return {x+point.x, y+point.y};
    }

    Pt_ld operator-(const Pt_ld& point) const {
        return {x-point.x, y-point.y};
    }

    ld get_abs() const {
        return hypotl(x, y);
    }

    Pt_ld norm(ld len) const {
        ld k = len/get_abs();
        return {x*k, y*k};
    }
};

istream& operator>>(istream& in, Pt_ld& point) {
    in >> point.x >> point.y;
    return in;
}

ld dot(Pt_ld x, Pt_ld y) {
    return x.x*y.x+x.y*y.y;
}

ld cross(Pt_ld x, Pt_ld y) {
    return x.x*y.y-x.y*y.x;
}

ld abs(Pt_ld x) {
    return x.get_abs();
}

ld abs_2(Pt_ld x) {
    return x.x*x.x+x.y*x.y;
}

ld dist(Pt_ld x, Pt_ld y) {
    return abs(x-y);
}

ld dist_2(Pt_ld x, Pt_ld y) {
    return abs_2(x-y);
}

ld angle(Pt x, Pt y) {
    // angle between (1, 0) и (sin, cos)
    return atan2(cross(x, y), dot(x, y));
}

struct Line_ld {
    ld a, b, c;

    Line_ld(Pt_ld x, Pt_ld y): a(x.y-y.y), b(y.x-x.x), c(cross(x, y)) {}

    Pt_ld dir() const {
        return {-b, a};
    }

    Pt_ld norm() const {
        return {a, b};
    }

    Line_ld per(Pt_ld x) const {
        return {x, x+norm()};
    }

    bool on(Pt_ld x) const {
        return abs(a*x.x+b*x.y+c) < E;
    }
};

bool on_line(Pt_ld x, Pt_ld y, Pt_ld z) {
    return abs(cross(y-x, z-x)) < E;
}

bool is_parallel(Line_ld a, Line_ld b) {
    return abs(cross(a.dir(), b.dir())) < E;
}

vector<Pt_ld> inter(Line_ld a, Line_ld b) {
    if (is_parallel(a, b)) {
        return {};
    }
    ld det = cross(a.norm(), b.norm());
    ld det_x = cross(Pt_ld(-a.c, a.b), Pt_ld(-b.c, b.b));
    ld det_y = cross(Pt_ld(a.a, -a.c), Pt_ld(b.a, -b.c));
    return {Pt_ld(det_x/det, det_y/det)};
}

Pt_ld projection(Line_ld line, Pt_ld x) {
    return inter(line, line.per(x))[0];
}

struct Seg_ld {
    Pt_ld x, y;

    Seg_ld() = default;
    Seg_ld(Pt_ld x, Pt_ld y): x(x), y(y) {}

    explicit operator bool() const {
        return x != y;
    }

    Line_ld line() const {
        return {x, y};
    }

    bool on(Pt_ld point) const {
        return on_line(x, y, point) && dot(point-q.x, point-q.y) < E;
    }
};

vector<Pt_ld> inter(Seg_ld a, Seg_ld b) {
    vector<Pt_ld> inters;
    if (!a && b.on(a.x)) {
        inters.push_back(a.x);
    } else if (!b && a.on(b.x)) {
        inters.push_back(b.x);
    }
    if (!a || !b) {
        return inters;
    }
    inters = inter(a.line(), b.line());
    if (!inters.empty() && a.on(inters[0]) && b.on(inters[0])) {
        return inters;
    }
    return {};
}

struct Cir_ld {
    Pt_ld x;
    ld r = 0;

    Cir_ld() = default;
    Cir_ld(Pt_ld x, ld r): x(x), r(r) {}

    bool on(Pt_ld point) const {
        return abs(dist(point, x)-r) < E;
    }
};

vector<Pt_ld> inter(Cir_ld cir, Line_ld line) {
    Pt_ld proj = projection(line, cir.x);
    ld h = dist(proj, cir.x);
    if (h > cir.r-E) {
        return h > cir.r+E ? vector<Pt_ld>() : vector{proj};
    }
    ld len = sqrtl(cir.r*cir.r-h*h);
    Pt_ld dir = line.dir().norm(len);
    vector<Pt_ld> ans = {proj-dir, proj+dir};
    sort(ans.begin(), ans.end());
    return ans;
}

vector<Pt_ld> inter(Cir_ld cir, Seg_ld seg) {
    if (!seg) {
        return cir.on(seg.x) ? vector{seg.x} : vector<Pt_ld>();
    }
    vector<Pt_ld> ans, inters = inter(cir, seg.line());
    for (Pt_ld q : inters) {
        if (seg.on(q)) {
            ans.push_back(q);
        }
    }
    return ans;
}

