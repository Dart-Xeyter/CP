const ld E = 1e-8;

template <typename T>
struct NumT {
    T val;

    NumT(T val): val(val) {}

    operator T() {
        return val;
    }

    bool operator==(const NumT& other) const {
        return abs(val-other.val) < E;
    }
};

using Num = NumT<ld>;

auto operator<=>(const Num& x, const Num& y) {
    if (x == y) {
        return x.val <=> x.val;
    }
    return x.val <=> y.val;
}

istream& operator>>(istream& in, Num& x) {
    int val;
    cin >> val;
    x.val = val;
    return in;
}

int sign(Num x) {
    return (x > Num(0))-(x < Num(0));
}

struct Pt {
    Num x = 0, y = 0;

    bool operator==(const Pt& other) const {
        return x == other.x && y == other.y;
    }

    Pt operator+(Pt other) {
        return {x+other.x, y+other.y};
    }

    Pt operator-(Pt other) {
        return {x-other.x, y-other.y};
    }

    Pt operator*(Num t) {
        return {x*t, y*t};
    }
};

Num dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

Num cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

Num dist_2(Pt x, Pt y) {
    return dot(y-x, y-x);
}

ld angle(Pt x) {
    ld alpha = atan2l(x.y, x.x);
    ld pi = numbers::pi_v<ld>;
    return alpha+2*pi*(alpha < -E);
}

struct Line {
    Pt a, dir;

    int side(Pt x) {
        return sign(cross(dir, x-a));
    }

    Pt proj(Pt x) {
        ld t = dot(x-a, dir)/dot(dir, dir);
        return a+dir*t;
    }
};

Line make_line(Pt x, Pt y) {
//    ld t = 1/sqrtl(dist_2(x, y));
    int t = 1;
    return {x, (y-x)*t};
}

Pt inter(Line line1, Line line2) {
    Num det = cross(line1.dir, line2.dir);
    if (det == Num(0)) {
        return {NAN, NAN};
    }
    Pt r = line2.a-line1.a;
    Num det_x = cross(r, line2.dir);
    ld t = det_x/det;
    return line1.a+line1.dir*t;
}

bool on_seg(Pt a, Pt b, Pt x) {
    return cross(x-a, x-b) == Num(0) && dot(x-a, x-b) <= Num(0);
}

struct Cir {
    Pt c;
    Num r = 0;

    int in(Pt x) {
        return sign(r*r-dist_2(c, x));
    }
};

vector<Pt> inter(Cir cir, Line line) {
    Pt proj = line.proj(cir.c);
    Num d_2 = dist_2(proj, cir.c);
    Num r_2 = cir.r*cir.r;
    if (d_2 > r_2) {
        return {};
    }
    if (d_2 == r_2) {
        return {proj};
    }
    Pt dir = line.dir;
    ld t = sqrtl((r_2-d_2)/dot(dir, dir));
    return {proj-dir*t, proj+dir*t};
}

Line rad_axis(Cir cir1, Cir cir2) {
    Num d_2 = dist_2(cir1.c, cir2.c);
    Num r_2 = cir1.r*cir1.r-cir2.r*cir2.r;
    ld t = (d_2+r_2)/(2*d_2);
    Pt dir = cir2.c-cir1.c;
    return {cir1.c+dir*t, {-dir.y, dir.x}};
}

vector<Pt> inter(Cir cir1, Cir cir2) {
    if (cir1.c == cir2.c) {
        return {};
    }
    return inter(cir1, rad_axis(cir1, cir2));
}

vector<Pt> tangents(Cir cir, Pt x) {
    Num r_2 = dist_2(cir.c, x)-cir.r*cir.r;
    ld r = sqrtl(max<ld>(0, r_2));
    return inter({x, r}, cir);
}

