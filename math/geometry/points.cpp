struct Pt;
long double abs(Pt x);

struct Pt {
    int x, y;

    Pt(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}

    Pt operator+() {
        return Pt(x, y);
    }

    Pt operator+(Pt point) {
        return Pt(x+point.x, y+point.y);
    }

    Pt operator-() {
        return Pt(-x, -y);
    }

    Pt operator-(Pt point) {
        return Pt(x-point.x, y-point.y);
    }

    Pt operator*(int k) {
        return Pt(x*k, y*k);
    }

    Pt operator/(int k) {
        return Pt(x/k, y/k);
    }

    bool operator==(Pt point) {
        return x-point.x == 0 && y-point.y == 0;
    }

    bool operator!=(Pt point) {
        return !(*this == point);
    }

    bool operator<(Pt point) {
        return x < point.x || (x == point.x && y < point.y);
    }

    long double angle() {
        return atan2(y, x);
    }
};

istream& operator>>(istream& cin1, Pt &x) {
    cin1 >> x.x >> x.y;
    return cin1;
}

ostream& operator<<(ostream& cout1, Pt x) {
    cout1 << x.x << ' ' << x.y;
    return cout1;
}

int dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

int cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

long double abs(Pt x) {
    return hypot(x.x, x.y);
}

long double dist(Pt x, Pt y) {
    return abs(Pt(x-y));
}

long double angle(Pt x, Pt y) {
    return atan2(cross(x, y), dot(x, y));
}

bool in_tr(Pt x, Pt y, Pt z, Pt point) {
    bool flag = true;
    if (cross(y-x, z-y) > 0) {
        flag &= (cross(point-x, y-x) >= 0 && cross(point-y, z-y) >= 0 && cross(point-z, x-z) >= 0);
    } else {
        flag &= (cross(point-x, y-x) <= 0 && cross(point-y, z-y) <= 0 && cross(point-z, x-z) <= 0);
    }
    return flag;
}

int S2_tr(Pt x, Pt y, Pt z) {
    return cross(z-x, y-x);
}

bool ray_seg(Pt a, Pt b, Pt x, Pt y) {
    if (a == x || a == y || b == x || b == y) {
        return true;
    }
    if (a == b && x == y) {
        return false;
    }
    if (a == b) {
        return cross(x-y, x-a) == 0 && dot(y-x, a-x) > 0 && dot(x-y, a-y) > 0;
    }
    if (x == y) {
        return cross(a-b, a-x) == 0 && dot(b-a, x-a) > 0 && dot(a-b, x-b) > 0;
    }
    int w = cross(x-a, b-a), w1 = cross(b-a, y-a), w2 = cross(x-a, y-a);
    if (w == 0 && w1 == 0) {
        return dot(b-a, x-a) > 0 || dot(b-a, y-a) > 0;
    }
    if (w == 0) {
        return dot(b-a, x-a) > 0;
    }
    if (w1 == 0) {
        return dot(b-a, y-a) > 0;
    }
    if (w2 == 0) {
        return dot(y-x, a-x) > 0 && dot(x-y, a-y) > 0;
    }
    return w*w1 > 0 && w*w2 > 0;
}

bool seg_seg(Pt a, Pt b, Pt x, Pt y) {
    return ray_seg(a, b, x, y) && ray_seg(b, a, x, y);
}

