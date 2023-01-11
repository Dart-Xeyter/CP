#include <bits/stdc++.h>
#define int long long
#define p pair<int, int>
#define endl '\n'
const int INF = 1e9+1;

using namespace std;

template <typename T>
struct Heap {
    vector<pair<int, T>> a = {{-INF, {}}};

    void sieve_up(int q) {
        while (a[q].first < a[q/2].first) {
            swap(a[q], a[q/2]);
            q /= 2;
        }
    }

    void sieve_down(int q) {
        while (true) {
            int left = (2*q < a.size() ? a[2*q].first : INF);
            int right = (2*q+1 < a.size() ? a[2*q+1].first : INF);
            if (a[q].first <= min(left, right)) {
                break;
            }
            int ind = (left < right ? 2*q : 2*q+1);
            swap(a[q], a[ind]);
            q = ind;
        }
    }

    void add(pair<int, T> x) {
        a.push_back(x);
        sieve_up((int)a.size()-1);
    }

    pair<int, T> get_min() {
        return a[1];
    }

    void del_min() {
        swap(a[1], a.back());
        a.pop_back();
        sieve_down(1);
    }

    bool empty() {
        return a.size() == 1;
    }
};

vector<int> order(vector<pair<p, int>> &a, int x) {
    Heap<p> s;
    for (pair<p, int> q : a) {
        s.add({q.first.first, {q.first.second-q.first.first, q.second}});
    }
    vector<int> ans;
    while (!s.empty() && s.get_min().first < x) {
        x += s.get_min().second.first;
        ans.push_back(s.get_min().second.second);
        s.del_min();
    }
    return {s.empty() ? ans : vector<int>()};
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, start;
    cin >> n >> start;
    vector<p> a(n);
    for (int q = 0; q < n; q++) {
        cin >> a[q].first >> a[q].second;
    }
    vector<pair<p, int>> first, second;
    int end = start;
    for (int q = 0; q < n; q++) {
        if (a[q].first <= a[q].second) {
            first.push_back({a[q], q});
        } else {
            second.push_back({{a[q].second, a[q].first}, q});
        }
        end += a[q].second-a[q].first;
    }
    vector<int> ans_first = order(first, start), ans_second = order(second, end);
    reverse(ans_second.begin(), ans_second.end());
    if (ans_first.size()+ans_second.size() < n) {
        cout << "NIE" << endl;
        return 0;
    }
    cout << "TAK" << endl;
    for (int q : ans_first) {
        cout << q+1 << ' ';
    }
    for (int q : ans_second) {
        cout << q+1 << ' ';
    }
    cout << endl;
    return 0;
}
