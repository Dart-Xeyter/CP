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

ostream& operator<<(ostream& out, const Pt& point) {
    out << point.x << ' ' << point.y;
    return out;
}

int dot(Pt x, Pt y) {
    return x.x*y.x+x.y*y.y;
}

int cross(Pt x, Pt y) {
    return x.x*y.y-x.y*y.x;
}

bool on_line(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x) == 0;
}

struct Seg {
    Pt x, y;

    Seg(Pt x, Pt y): x(x), y(y) {}

    auto operator<=>(const Seg& other) const = default;

    explicit operator bool() const {
        return x != y;
    }
};

bool on_seg(Seg q, Pt point) {
    return on_line(q.x, q.y, point) && dot(point-q.x, point-q.y) <= 0;
}

int S_tr_2(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x);
}

struct Polygon {
    vector<Pt> a;

    explicit Polygon(vector<Pt> a_ = {}): a(std::move(a_)) {
        if (a.empty()) {
            return;
        }
        normalize();
        if (a.size() > 1) {
            a.push_back(a[0]);
        }
    }

    void counterclockwise() {
        if (S_2() < 0) {
            reverse(a.begin(), a.end());
        }
    }

    void normalize() {
        int n = (int)a.size();
        int ind = 1;
        while (ind < n-1 && on_line(a[0], a[ind], a[ind+1])) {
            ind++;
        }
        if (ind >= n-1) {
            Pt min1 = *min_element(a.begin(), a.end());
            Pt max1 = *max_element(a.begin(), a.end());
            a = (min1 == max1 ? vector{min1} : vector{min1, max1});
            return;
        }
        rotate(a.begin(), a.begin()+ind, a.end());
        a.push_back(a[0]);
        vector<Pt> will_a = {a[0]};
        for (int q = 1; q < n; q++) {
            if (!on_line(will_a.back(), a[q], a[q+1])) {
                will_a.push_back(a[q]);
            }
        }
        a = will_a;
    }

    vector<Seg> get_edges() const {
        int n = (int)a.size();
        vector<Seg> edges;
        for (int q = 1; q < n; q++) {
            edges.emplace_back(a[q-1], a[q]);
        }
        return edges;
    }

    int S_2() const {
        int ans = 0;
        for (Seg q : get_edges()) {
            ans += S_tr_2(a[0], q.x, q.y);
        }
        return ans;
    }
};

static int insert_type = 0;
static bool start_at_the_far_side;

struct cmp_bybass {
    bool operator()(const Seg& x, const Seg& y) const {
        if (insert_type == 0) {
            return cmp_add(x, y);
        }
        if (insert_type <= 2) {
            return cmp_tangent(x, y);
        }
        return cmp_belonging(x, y);
    }

    bool cmp_add(const Seg& x, const Seg& y) const {
        return cross(x.y-x.x, y.y-y.x) > 0;
    }

    bool cmp_tangent(const Seg& x, const Seg& y) const {
        Pt he = x.y-x.x, me = x.y-y.x, first = y.y-y.x;
        int me_he = cross(me, he);
        if (me_he <= 0) {
            return insert_type == 2 && (me_he < 0 || dot(me, he) < 0);
        }
        return start_at_the_far_side && cross(first, me) > 0;
    }

    bool cmp_belonging(const Seg& x, const Seg& y) const {
        return x.y != y.y && cross(x.y-y.y, y.x-y.y) >= 0;
    }
};

struct Bypass {
    set<Seg, cmp_bybass> left, right;

    explicit Bypass(Polygon pol) {
        assert(pol.a.size() > 1);
        pol.counterclockwise();
        for (Seg& q : pol.get_edges()) {
            add_seg(q);
        }
    }

    static int type_of_seg(Seg seg) {
        int c = cross(Pt(1, 0), seg.y-seg.x);
        int d = dot(Pt(1, 0), seg.y-seg.x);
        assert(c != 0 || d != 0);
        return c > 0 || c == 0 && d > 0;
    }

    void add_seg(Seg seg) {
        if (type_of_seg(seg) == 0) {
            left.insert(seg);
        } else {
            right.insert(seg);
        }
    }

    Seg next_seg(Seg seg) {
        int type = type_of_seg(seg);
        auto& my = (type == 0 ? left : right);
        auto& other = (type == 0 ? right : left);
        auto w = my.upper_bound(seg);
        return w == my.end() ? *other.begin() : *w;
    }

    static bool check_tangent(Pt q, Seg x, Seg y, int type) {
        int sign1 = cross(x.y-q, x.y-x.x);
        int sign2 = cross(y.x-q, y.y-y.x);
        if (type == 0) {
            return sign1 > 0 && sign2 <= 0;
        }
        return sign1 < 0 && sign2 >= 0;
    }

    vector<Seg> find_tangent(Pt q, const set<Seg, cmp_bybass>& a, Seg prev, int type) const {
        Seg beg = *a.begin();
        start_at_the_far_side = (cross(beg.x-q, beg.y-beg.x) >= 0);
        insert_type = type+1;
        auto w = a.lower_bound(Seg(q, beg.x));
        insert_type = 0;
        if (check_tangent(q, prev, beg, type)) {
            return {beg};
        }
        if (w == a.begin()) {
            return {};
        }
        prev = *((--w)++);
        if (w == a.end() || !check_tangent(q, prev, *w, type)) {
            return {};
        }
        return {*w};
    }

    Seg get_tangent(Pt q, int type) const {  // seg if on the line else after
        assert(left.size()+right.size() > 2);
        auto lefts = find_tangent(q, left, *right.rbegin(), type);
        auto rights = find_tangent(q, right, *left.rbegin(), type);
        assert(lefts.size()+rights.size() == 1);
        Seg ans = (lefts.empty() ? rights[0] : lefts[0]);
        return ans;
    }

    Seg left_tangent(Pt q) const {
        return get_tangent(q, 0);
    }

    Seg right_tangent(Pt q) const {
        return get_tangent(q, 1);
    }

    int check_belonging(Pt q, const set<Seg, cmp_bybass>& a, Pt start) const {
        insert_type = 3;
        auto w = a.lower_bound(Seg(q, start));
        insert_type = 0;
        if (w->y == start) {
            return 2*on_seg(*w, q);
        }
        int far_side = cross(w->y-w->x, q-w->x);
        return (far_side >= 0)+(far_side == 0);
    }

    int belonging(Pt q) const { // 0 -> out, 1 -> in, 2 -> border
        Pt start = right.begin()->x;
        int first_side = cross(right.begin()->y-start, q-start);
        if (first_side <= 0) {
            return 2*on_seg(*right.begin(), q);
        }
        if (cross(left.begin()->x-start, q-start) >= 0) {
            return check_belonging(q, left, start);
        }
        return check_belonging(q, right, start);
    }

    pair<Seg, Seg> delete_between_tangents(Pt q) {
        Seg tan_left = left_tangent(q);
        Seg tan_right = right_tangent(q);
        if (on_line(tan_right.x, tan_right.y, q)) {
            tan_right = next_seg(tan_right);
        }
        pair<Seg, Seg> tangents = {tan_left, tan_right};
        while (tan_left != tan_right) {
            auto& now = (type_of_seg(tan_left) == 0 ? left : right);
            now.erase(tan_left);
            tan_left = next_seg(tan_left);
        }
        return tangents;
    }

    void add_point(Pt q) {
        if (belonging(q)) {
            return;
        }
        if (left.size()+right.size() == 2) {
            *this = Bypass(Polygon({q, left.begin()->x, right.begin()->x}));
            return;
        }
        auto [tan_left, tan_right] = delete_between_tangents(q);
        add_seg(Seg(tan_left.x, q));
        add_seg(Seg(q, tan_right.x));
    }
};

Polygon get_Polygon(const Bypass& bypass) {
    vector<Pt> pol;
    for (Seg q : bypass.left) {
        pol.push_back(q.x);
    }
    for (Seg q : bypass.right) {
        pol.push_back(q.x);
    }
    return Polygon(pol);
}

