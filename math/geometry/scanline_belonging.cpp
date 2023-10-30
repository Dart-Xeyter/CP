#include <bits/extc++.h>
#define int long long
#define ld long double
#define p pair<int, int>
#define endl '\n'
const int INF = (int)1e9+1;

using namespace __gnu_pbds;
using namespace std;

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

bool on_line(Pt x, Pt y, Pt z) {
    return cross(y-x, z-x) == 0;
}

int X;

struct Seg {
    Pt x, y;
    int num;

    Seg(Pt x, Pt y, int num = -1): x(x), y(y), num(num) {}

    strong_ordering operator<=>(Seg other) const {
        p Y1 = get_Y(), Y2 = other.get_Y();
        __int128 dif = (__int128)Y1.first*Y2.second-(__int128)Y2.first*Y1.second;
        if (dif != 0) {
            return dif <=> 0;
        }
        set<Pt> all = {x, y, other.x, other.y};
        if (all.size() == 4) {
            return strong_ordering::equivalent;
        }
        if (x == other.y || y == other.x) {
            return strong_ordering::less;
        }
        if (y == other.y) {
            swap(other.x, other.y);
        }
        return cross(other.y-other.x, y-x) <=> 0;
    }

    p get_Y() const {
        return x.x == y.x ? p{x.y, 1} : p{(y.y-x.y)*(X-x.x)+x.y*(y.x-x.x), y.x-x.x};
    }
};

struct Polygon {
    vector<Pt> a;

    explicit Polygon(vector<Pt> a): a(std::move(a)) {
        normalize();
    }

    void normalize() {
        int ind = 1;
        while (on_line(a[0], a[ind], a[ind+1])) {
            ind++;
        }
        rotate(a.begin(), a.begin()+ind, a.end());
        a.push_back(a[0]);
        vector<Pt> will_a = {a[0]};
        for (int q = 1; q < (int)a.size()-1; q++) {
            if (!on_line(will_a.back(), a[q], a[q+1])) {
                will_a.push_back(a[q]);
            }
        }
        a = will_a;
    }

    vector<Seg> get_edges() const {
        vector<Pt> a1 = a;
        a1.push_back(a[0]);
        vector<Seg> edges;
        for (int q = 1; q < a1.size(); q++) {
            edges.emplace_back(a1[q-1], a1[q]);
        }
        return edges;
    }
};

struct Event {
    Seg seg;
    int type;
    bool quest;

    Event(Seg seg, int type, bool quest): seg(seg), type(type), quest(quest) {}

    auto operator<=>(Event other) const {
        Event me = *this;
        if (me.type == 1) {
            swap(me.seg.x, me.seg.y);
        }
        if (other.type == 1) {
            swap(other.seg.x, other.seg.y);
        }
        return pair{me.seg.x, p(me.seg.num, me.type)} <=> pair{other.seg.x, p(other.seg.num, other.type)};
    }
};

void vertices_and_vertical(Polygon& pol, vector<Pt>& a, vector<int>& ans) {
    vector<pair<Pt, int>> a1;
    for (int q = 0; q < a.size(); q++) {
        a1.emplace_back(a[q], q);
    }
    sort(a1.begin(), a1.end());
    vector<Seg> edges = pol.get_edges();
    for (Pt q : pol.a) {
        edges.emplace_back(q, q);
    }
    for (Seg q : edges) {
        if (q.x.x != q.y.x) {
            continue;
        }
        if (q.x > q.y) {
            swap(q.x, q.y);
        }
        auto w = lower_bound(a1.begin(), a1.end(), pair{q.x, -1LL});
        while (w != a1.end() && w->first <= q.y) {
            ans[(w++)->second] = 2;
        }
    }
}

typedef tree<Seg, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

void general_case(vector<Event>& events, vector<int>& ans) {
    ordered_set s;
    for (Event& q : events) {
        X = (q.type == 0 ? q.seg.x.x : q.seg.y.x);
        if (q.type == 0) {
            s.insert(q.seg);
            continue;
        }
        int k = (int)s.order_of_key(q.seg);
        auto w = s.find_by_order(k);
        k = (q.seg.num == -1 || w->num == (q.seg.num ^ 1) ? k : (int)s.size());
        if (q.quest) {
            ans[q.seg.num >> 1] = (k == s.size() ? 2 : (k & 1));
        }
        if (k != s.size()) {
            s.erase(s.find_by_order(k));
        }
    }
}

vector<int> check_belonging(Polygon pol, vector<Pt>& a) {
    vector<int> ans(a.size(), -1);
    vertices_and_vertical(pol, a, ans);
    vector<Event> events;
    for (Seg q : pol.get_edges()) {
        if (q.x.x == q.y.x) {
            continue;
        }
        if (q.x > q.y) {
            swap(q.x, q.y);
        }
        events.emplace_back(q, 0, false);
        events.emplace_back(q, 1, false);
    }
    for (int q = 0; q < a.size(); q++) {
        if (ans[q] != -1) {
            continue;
        }
        events.emplace_back(Seg(a[q], a[q], 2*q), 0, true);
        events.emplace_back(Seg(a[q], a[q], 2*q+1), 1, true);
    }
    sort(events.begin(), events.end());
    general_case(events, ans);
    return ans;
}

