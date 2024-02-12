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

ld abs_2(Pt x) {
    return x.x*x.x+x.y*x.y;
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
    Pt x, dir;
    ld ang;
    static constexpr ld pi = numbers::pi_v<ld>;

    Line(Pt x, Pt y): a(x.y-y.y), b(y.x-x.x), c(cross(x, y)),
            x(x), dir(y-x), ang(angle(Pt(0, -1), dir)) {
        ang += (ang < -E)*2*pi;
    }

    Pt norm() const {
        return {a, b};
    }

    Line per(Pt point) const {
        return {point, point+norm()};
    }
};

vector<Pt> inter(const Line& a, const Line& b) {
    ld det = cross(a.norm(), b.norm());
    if (abs(det) < E) {
        return {};
    }
    ld det_x = cross(Pt(-a.c, a.b), Pt(-b.c, b.b));
    ld det_y = cross(Pt(a.a, -a.c), Pt(b.a, -b.c));
    return {Pt(det_x/det, det_y/det)};
}

struct Polygon {
    vector<Pt> a;

    Polygon(vector<Pt> a_ = {}): a(std::move(a_)) {
        if (a.size() <= 1) {
            return;
        }
        a.push_back(a[0]);
    }
};

void err() {
    throw 0;
}

int type_of_seg(Pt x, Pt y) {
    if (x == Pt() || y == Pt()) {
        err();
    }
    ld crs = cross(x, y), dt = dot(x, y);
    return 1-(crs > E || abs(crs) < E && dt > E);
}

bool less_parallel(const Line& x, const Line& y) {
    ld crs = cross(x.dir, y.x-x.x);
    return crs > 0;
}

bool cmp_lines(const Line& x, const Line& y) {
    return x.ang < y.ang;
}

bool add_line_CHT(const Line& q, vector<Line>& stack, vector<Pt>& points) {
    while (!stack.empty()) {
        vector<Pt> inters = inter(stack.back(), q);
        if (inters.empty() && less_parallel(q, stack.back())) {
            return false;
        }
        if (inters.empty() || !points.empty() &&
                              dot(inters[0]-points.back(), stack.back().dir) < E) {
            stack.pop_back();
            if (!points.empty()) {
                points.pop_back();
            }
        } else {
            points.push_back(inters[0]);
            break;
        }
    }
    return true;
}

vector<Pt> make_CHT(vector<Line>& a, bool up) {
    sort(a.begin(), a.end(), cmp_lines);
    if (!up) {
        a.emplace_back(Pt(INF+1, -INF), Pt(INF+1, INF));
    } else {
        a.emplace_back(Pt(-INF-1, INF), Pt(-INF-1, -INF));
    }
    vector<Line> stack;
    vector<Pt> points;
    for (auto& q : a) {
        if (add_line_CHT(q, stack, points)) {
            stack.push_back(q);
        }
    }
    return points;
}

vector<Pt> expand_CHT(vector<Pt>& cht, vector<ld>& xs) {
    int n = (int)cht.size(), m = (int)xs.size();
    vector<Pt> a = {cht[0]};
    int ind = 0;
    for (int q = 1; q < n; q++) {
        while (ind < m && xs[ind] < cht[q-1].x+E) {
            ind++;
        }
        Line seg(cht[q-1], cht[q]);
        while (ind < m && xs[ind] < cht[q].x-E) {
            a.emplace_back(xs[ind], (-seg.c-seg.a*xs[ind])/seg.b);
            ind++;
        }
        a.push_back(cht[q]);
    }
    return a;
}

void fix_CHT(vector<Pt>& cht1, vector<Pt>& cht2) {
    vector<ld> xs, xs1, xs2;
    for (Pt q : cht1) {
        xs1.push_back(q.x);
    }
    for (Pt q : cht2) {
        xs2.push_back(q.x);
    }
    merge(xs1.begin(), xs1.end(), xs2.begin(), xs2.end(), back_inserter(xs));
    cht1 = expand_CHT(cht1, xs);
    cht2 = expand_CHT(cht2, xs);
    cht1.insert(cht1.begin(), Pt(cht1[0].x, max((ld)INF, cht1[0].y)+1));
    cht2.push_back(Pt(cht2.back().x, min((ld)-INF, cht2.back().y)-1));
}

bool cmp_points(Pt x, Pt y) {
    return x.x < y.x-E || abs(x.x-y.x) < E && x.y > y.y+E;
}

void build_merge_up_down(vector<Pt>& cht1, vector<Pt>& cht2, vector<Pt>& up,
                   vector<Pt>& down, vector<int>& up_ind, vector<int>& down_ind) {
    int n1 = (int)cht1.size(), n2 = (int)cht2.size();
    int ind1 = 1, ind2 = 1;
    while (ind1 < n1 && ind2 < n2) {
        if (cmp_points(cht1[ind1], cht2[ind2])) {
            if (cross(cht2[ind2]-cht2[ind2-1], cht1[ind1]-cht2[ind2-1]) < E) {
                down.push_back(cht1[ind1]);
                down_ind.push_back(ind1);
            }
            ind1++;
        } else {
            if (cross(cht1[ind1]-cht1[ind1-1], cht2[ind2]-cht1[ind1-1]) > -E) {
                up.push_back(cht2[ind2]);
                up_ind.push_back(ind2);
            }
            ind2++;
        }
    }
}

Polygon merge_CHT(vector<Pt>& cht1, vector<Pt>& cht2) {
    vector<Pt> up, down;
    vector<int> up_ind, down_ind;
    build_merge_up_down(cht1, cht2, up, down, up_ind, down_ind);
    if (up.empty() || down.empty()) {
        return {};
    }
    vector<Pt> inter_left = inter(Line(cht1[down_ind[0]-1], cht1[down_ind[0]]),
                                  Line(cht2[up_ind[0]-1], cht2[up_ind[0]]));
    vector<Pt> inter_right = inter(Line(cht1[down_ind.back()], cht1[down_ind.back()+1]),
                                   Line(cht2[up_ind.back()], cht2[up_ind.back()+1]));
    if (inter_left.empty() || inter_right.empty()) {
        err();
    }
    vector<Pt> ans = {inter_left[0]};
    ans.insert(ans.end(), down.begin(), down.end());
    ans.push_back(inter_right[0]);
    ans.insert(ans.end(), up.rbegin(), up.rend());
    return Polygon(ans);
}

Polygon half_plane_inter(vector<Line> a) {
    a.emplace_back(Pt(-INF, -INF), Pt(INF, -INF));
    a.emplace_back(Pt(INF, -INF), Pt(INF, INF));
    a.emplace_back(Pt(INF, INF), Pt(-INF, INF));
    a.emplace_back(Pt(-INF, INF), Pt(-INF, -INF));
    vector<Line> up, down;
    for (auto& q : a) {
        if (type_of_seg(Pt(0, -1), q.dir) == 0) {
            down.push_back(q);
        } else {
            up.push_back(q);
        }
    }
    vector<Pt> cht1 = make_CHT(down, false), cht2 = make_CHT(up, true);
    reverse(cht2.begin(), cht2.end());
    fix_CHT(cht1, cht2);
    return merge_CHT(cht1, cht2);
}

