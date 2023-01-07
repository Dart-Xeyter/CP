struct Pt {
    int x, y;

    Pt(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}

    Pt operator+(Pt point) {
        return Pt(x+point.x, y+point.y);
    }

    Pt operator-(Pt point) {
        return Pt(x-point.x, y-point.y);
    }
};

int dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

int cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

struct Ln {
    int a, b, c;

    Ln(Pt x = Pt(), Pt y = Pt()) {
        a = y.y-x.y, b = x.x-y.x;
        c = -a*x.x-b*x.y;
    }

    bool operator==(Ln x) {
        return a*x.b-b*x.a == 0 && a*x.c-c*x.a == 0;
    }

    bool operator!=(Ln x) {
        return !(*this == x);
    }

    Ln per(Pt x) {
        return Ln(x, x+Pt(a, b));
    }

    pair<Pt, Pt> points() {
        if (c != 0) {
            exit(179);
        }
        return {Pt(), Pt(-b, a)};
    }

    int value(Pt x) {
        return a*x.x+b*x.y+c;
    }
};

istream& operator>>(istream& cin1, Ln &line) {
    cin1 >> line.a >> line.b >> line.c;
    return cin1;
}

ostream& operator<<(ostream& cout1, Ln line) {
    cout1 << line.a << ' ' << line.b << ' ' << line.c;
    return cout1;
}

Ln build_line(int a, int b, int c) {
    Ln line = Ln(Pt(), Pt());
    line.a = a, line.b = b, line.c = c;
    return line;
}

bool on_ray(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x) == 0 && dot(y-x, z-x) >= 0;
}

bool on_seg(Pt x, Pt y, Pt z) {
    return on_ray(x, y, z) && on_ray(y, x, z);
}

