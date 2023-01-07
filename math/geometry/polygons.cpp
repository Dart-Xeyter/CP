struct Pt {
    int x, y;

    Pt(int x1 = 0, int y1 = 0) : x(x1), y(y1) {}

    bool operator<(Pt point) {
        return x < point.x || (x == point.x && y < point.y);
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

vector<Pt> convex_hull(vector<Pt> a) {
    int n = a.size();
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
    int n = a.size();
    a.push_back(a.back());
    int ans = 0;
    for (int q = 1; q <= n; q++) {
        ans += S_tr_2(a[0], a[q-1], a[q]);
    }
    return ans;
}

