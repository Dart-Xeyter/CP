#define ld long double
const ld E = 1e-8;

struct Pt {
    ld x, y;

    Pt(): x(0), y(0) {}
    Pt(ld x, ld y): x(x), y(y) {}

    bool operator==(const Pt& point) const {
        return abs(x-point.x) < E && abs(y-point.y) < E;
    }

    bool operator<(const Pt& point) const {
        return x+E < point.x || abs(x-point.x) < E && y+E < point.y;
    }

    Pt operator+(const Pt& point) const {
        return {x+point.x, y+point.y};
    }

    Pt operator-(const Pt& point) const {
        return {x-point.x, y-point.y};
    }

    ld get_abs() const {
        return hypotl(x, y);
    }

    Pt norm(ld len) const {
        ld k = len/get_abs();
        return {x*k, y*k};
    }
};

istream& operator>>(istream& in, Pt& point) {
    in >> point.x >> point.y;
    return in;
}

ld dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

ld cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

ld abs(Pt x) {
    return x.get_abs();
}

ld abs_2(Pt x) {
    return x.x*x.x+x.y*x.y;
}

ld dist(Pt x, Pt y) {
    return abs(x-y);
}

ld dist_2(Pt x, Pt y) {
    return abs_2(x-y);
}

ld angle(Pt x, Pt y) {
    // angle between (1, 0) и (sin, cos)
    return atan2(cross(x, y), dot(x, y));
}

struct Line {
    ld a, b, c;

    Line(ld a, ld b, ld c): a(a), b(b), c(c) {}
    Line(Pt x, Pt y): a(x.y-y.y), b(y.x-x.x), c(cross(x, y)) {}

    Pt dir() const {
        return {b, -a};
    }

    Pt norm() const {
        return {a, b};
    }

    Line per(Pt x) const {
        return {x, x+norm()};
    }

    bool on(Pt x) const {
        return abs(a*x.x+b*x.y+c) < E;
    }
};

bool on_line(Pt x, Pt y, Pt z) {
    return abs(cross(y-x, z-x)) < E;
}

bool is_parallel(Line a, Line b) {
    return abs(cross(a.dir(), b.dir())) < E;
}

vector<Pt> inter(Line a, Line b) {
    if (is_parallel(a, b)) {
        return {};
    }
    ld det = cross(a.norm(), b.norm());
    ld det_x = cross(Pt(-a.c, a.b), Pt(-b.c, b.b));
    ld det_y = cross(Pt(a.a, -a.c), Pt(b.a, -b.c));
    return {Pt(det_x/det, det_y/det)};
}

Pt projection(Line line, Pt x) {
    return inter(line, line.per(x))[0];
}

struct Seg {
    Pt x, y;

    Seg() = default;
    Seg(Pt x, Pt y): x(x), y(y) {}

    explicit operator bool() const {
        return x != y;
    }

    Line line() const {
        return {x, y};
    }

    bool on(Pt point) const {
        return on_line(x, y, point) && dot(point-x, point-y) < E;
    }
};

vector<Pt> inter(Seg a, Seg b) {
    vector<Pt> inters;
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

struct Cir {
    Pt x;
    ld r = 0;

    Cir() = default;
    Cir(Pt x, ld r): x(x), r(r) {}

    bool on(Pt point) const {
        return abs(dist(point, x)-r) < E;
    }
};

vector<Pt> inter(Cir cir, Line line) {
    Pt proj = projection(line, cir.x);
    ld h = dist(proj, cir.x);
    if (h > cir.r-E) {
        return h > cir.r+E ? vector<Pt>() : vector{proj};
    }
    ld len = sqrtl(cir.r*cir.r-h*h);
    Pt dir = line.dir().norm(len);
    vector<Pt> ans = {proj-dir, proj+dir};
    sort(ans.begin(), ans.end());
    return ans;
}

vector<Pt> inter(Cir cir, Seg seg) {
    if (!seg) {
        return cir.on(seg.x) ? vector{seg.x} : vector<Pt>();
    }
    vector<Pt> ans, inters = inter(cir, seg.line());
    for (Pt q : inters) {
        if (seg.on(q)) {
            ans.push_back(q);
        }
    }
    return ans;
}

Line rad_axis(Cir cir1, Cir cir2) {
    ld a1 = cir1.x.x, b1 = cir1.x.y, r1 = cir1.r;
    ld a2 = cir2.x.x, b2 = cir2.x.y, r2 = cir2.r;
    return {2*(a2-a1), 2*(b2-b1), a1*a1-a2*a2+b1*b1-b2*b2+r2*r2-r1*r1};
}

vector<Pt> inter(Cir cir1, Cir cir2) {
    if (cir1.x == cir2.x) {
        return {};
    }
    return inter(cir1, rad_axis(cir1, cir2));
}

