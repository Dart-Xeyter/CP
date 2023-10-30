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

struct Pt_frac {
    int x_num, x_den;
    int y_num, y_den;
    
    Pt_frac(): x_num(0), x_den(1), y_num(0), y_den(1) {}
    Pt_frac(p x, p y): x_num(x.first), x_den(x.second), y_num(y.first), y_den(y.second) {}
};

struct Line {
    int a, b, c;

    Line(Pt x, Pt y): a(x.y-y.y), b(y.x-x.x), c(cross(x, y)) {}

    Pt dir() const {
        return {-b, a};
    }

    Pt norm() const {
        return {a, b};
    }
};

bool on_line(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x) == 0;
}

bool is_parallel(Line a, Line b) {
    return cross(a.dir(), b.dir()) == 0;
}

vector<Pt_frac> inter(Line a, Line b) {
    if (is_parallel(a, b)) {
        return {};
    }
    int det = cross(a.norm(), b.norm());
    int det_x = cross(Pt(-a.c, a.b), Pt(-b.c, b.b));
    int det_y = cross(Pt(a.a, -a.c), Pt(b.a, -b.c));
    return {Pt_frac({det_x, det}, {det_y, det})};
}

struct Seg {
    Pt x, y;

    Seg() = default;
    Seg(Pt x, Pt y): x(x), y(y) {}
    
    Line line() const {
        return {x, y};
    }
};

bool on_seg(Seg q, Pt point) {
    return on_line(q.x, q.y, point) && dot(point-q.x, q.y-q.x) >= 0 && dot(point-q.y, q.x-q.y) >= 0;
}

