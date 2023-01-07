#define ld long double
const ld E = 0.00000001;

struct Pt {
    ld x, y;

    Pt(ld x1 = 0, ld y1 = 0): x(x1), y(y1) {}

    bool operator==(Pt point) {
        return x == point.x && y == point.y;
    }

    bool operator!=(Pt point) {
        return x != point.x || y != point.y;
    }

    bool operator<(const Pt point) const {
        return x < point.x-E || (abs(x-point.x) < E && y < point.y-E);
    }

    bool operator>(Pt point) {
        return x > point.x+E || (abs(x-point.x) < E && y > point.y+E);
    }

    Pt operator+(Pt point) {
        return Pt(x+point.x, y+point.y);
    }

    Pt operator-(Pt point) {
        return Pt(x-point.x, y-point.y);
    }

    Pt operator*(ld t) {
        return Pt(x*t, y*t);
    }

    Pt operator/(ld t) {
        return Pt(x/t, y/t);
    }
};

istream& operator>>(istream &cin1, Pt &point) {
    int x, y;
    cin >> x >> y;
    point = Pt(x, y);
    return cin1;
}

ld abs_2(Pt x) {
    return x.x*x.x+x.y*x.y;
}

ld dist_2(Pt x, Pt y) {
    return abs_2(x-y);
}

ld dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

ld cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

struct Ln {
    ld a, b, c;

    Ln(ld a1 = 0, ld b1 = 0, ld c1 = 0): a(a1), b(b1), c(c1) {}
};

Ln make_line(Pt x, Pt y) {
    return Ln(x.y-y.y, y.x-x.x, x.x*y.y-x.y*y.x);
}

Ln perpendicular(Ln line, Pt x) {
    return Ln(-line.b, line.a, line.b*x.x-line.a*x.y);
}

Pt inter(Ln line1, Ln line2) {
    if (line1.a*line2.b == line2.a*line1.b) {
        return Pt(INF, INF);
    }
    long double x = (line2.b*line1.c-line1.b*line2.c)/(line2.a*line1.b-line1.a*line2.b);
    long double y = (line2.a*line1.c-line1.a*line2.c)/(line1.a*line2.b-line2.a*line1.b);
    return Pt(x, y);
}

struct Cr {
    ld x, y, r;
    Pt c;

    Cr(ld x1, ld y1, ld r1): x(x1), y(y1), r(r1), c(x, y) {}

    bool operator==(Cr cir) {
        return c == cir.c && abs(r-cir.r) < E;
    }

    bool operator!=(Cr cir) {
        return !(*this == cir);
    }
};

vector<Pt> inter(Cr cir, Ln line) {
    Ln per = perpendicular(line, cir.c);
    Pt inter1 = inter(line, per), dir = Pt(-line.b, line.a);
    ld d = dist_2(inter1, cir.c);
    if (d > cir.r*cir.r+E) {
        return {};
    }
    if (d > cir.r*cir.r-E) {
        return {inter1};
    }
    ld len = sqrt(cir.r*cir.r-d);
    Pt change = dir/sqrt(abs_2(dir))*len;
    return {inter1+change, inter1-change};
}

Ln rad_axis(Cr cir1, Cr cir2) {
    Ln line = Ln(2*(cir2.x-cir1.x), 2*(cir2.y-cir1.y), cir1.x*cir1.x-cir2.x*cir2.x+cir1.y*cir1.y-cir2.y*cir2.y+cir2.r*cir2.r-cir1.r*cir1.r);
    return line;
}

vector<Pt> inter(Cr cir1, Cr cir2) {
    return inter(cir1, rad_axis(cir1, cir2));
}

pair<bool, Pt> O_center(Pt x, Pt y, Pt z) {
    if (abs(cross(y-x, z-x)) < E) {
        return {false, Pt()};
    }
    return {true, inter(perpendicular(make_line(x, y), (x+y)/2), perpendicular(make_line(x, z), (x+z)/2))};
}
