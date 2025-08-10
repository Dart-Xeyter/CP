struct Polygon {
    vector<Pt> a;
    int n;

    Polygon(const vector<Pt>& a_): a(a_) {
        auto w = std::unique(a.begin(), a.end());
        n = w-a.begin();
        if (n == 0) {
            return;
        }
        n -= (n > 1 && a[0] == a[n-1]);
        a.resize(n);
        a.push_back(a[0]);
    }
};

int belong_convex(Polygon& a, Pt x) {
    if (a.n <= 1) {
        return (a.n == 1 && a.a[0] == x)-1;
    }
    Pt pt = a.a[0];
    if (cross(a.a[1]-pt, x-pt) <= Num(0)) {
        return on_seg(a.a[0], a.a[1], x)-1;
    }
    if (cross(a.a[a.n-1]-pt, x-pt) >= Num(0)) {
        return on_seg(a.a[0], a.a[a.n-1], x)-1;
    }
    int l = 0, r = a.n;
    while (r-l > 1) {
        int m = (l+r)/2;
        if (cross(a.a[m]-pt, x-pt) > Num(0)) {
            l = m;
        } else {
            r = m;
        }
    }
    return make_line(a.a[l], a.a[r]).side(x);
}

Polygon convex_hull(vector<Pt>& A) {
    if (A.empty()) {
        return {{}};
    }
    Pt pt = ranges::min(A, {}, [](Pt x) {return pair{x.x.val, x.y.val};});
    auto aa = views::filter(A, [&pt](Pt x) {return x != pt;});
    vector<Pt> a(aa.begin(), aa.end());
    ranges::sort(a, [&pt](Pt x, Pt y) {
        Num cr = cross(x-pt, y-pt);
        return cr > Num(0) || cr == Num(0) && dot(pt-x, y-x) < Num(0);
    });
    vector<Pt> hull = {pt};
    for (Pt q : views::join(vector{a, {pt}})) {
        while (hull.size() > 1) {
            Pt prev = hull[(int)hull.size()-2];
            if (cross(hull.back()-prev, q-prev) > Num(0)) {
                break;
            }
            hull.pop_back();
        }
        hull.push_back(q);
    }
    if (hull.size() == 2 && !a.empty()) {
        return {{pt, a.back()}};
    }
    return {{hull.begin(), hull.end()-1}};
}

bool add_line(deque<Line>& hull, Line line) {
    int len = (int)hull.size();
    while (len > 1 && line.side(inter(hull[len-1], hull[len-2])) == -1) {
        hull.pop_back();
        len--;
    }
    while (len > 1 && line.side(inter(hull[0], hull[1])) == -1) {
        hull.pop_front();
        len--;
    }
    if (len > 0 && cross(line.dir, hull.back().dir) == Num(0)) {
        if (dot(line.dir, hull.back().dir) < Num(0)) {
            return false;
        }
        if (cross(hull.back().dir, line.a-hull.back().a) > Num(0)) {
            hull.pop_back();
        } else {
            return true;
        }
    }
    if (len == 1 && cross(hull[0].dir, line.dir) < Num(0)) {
        return false;
    }
    hull.push_back(line);
    return true;
}

vector<Line> inter_lines(vector<Line>& a) {
    deque<Line> hull;
    for (Line line : a) {
        if (!add_line(hull, line)) {
            return {};
        }
    }
    if (hull.empty() || !add_line(hull, hull[0])) {
        return {};
    }
    return {hull.begin(), hull.end()-1};
}

Polygon half_planes_inter(vector<Line> A) {
    A.emplace_back(Pt(-INF, -INF), Pt(1, 0));
    A.emplace_back(Pt(INF, -INF), Pt(0, 1));
    A.emplace_back(Pt(INF, INF), Pt(-1, 0));
    A.emplace_back(Pt(-INF, INF), Pt(0, -1));

    vector<pair<Line, ld>> aa;
    for (Line line : A) {
        aa.emplace_back(line, angle(line.dir));
    }
    ranges::sort(aa, {}, [](auto x) {return x.second;});
    vector<Line> a;
    for (auto q : aa) {
        a.push_back(q.first);
    }
    vector<Line> hull = inter_lines(a);

    int n = (int)hull.size();
    vector<Pt> ans;
    for (int q = 0; q < n; q++) {
        ans.push_back(inter(hull[q], hull[(q+1) % n]));
    }
    return {ans};
}

