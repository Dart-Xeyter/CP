vector<vector<int>> d;
vector<int> pa, pb;
vector<bool> was_a, was_b;

bool find_chain(int vertex) {
    was_a[vertex] = true;
    for (int q : d[vertex]) {
        if (pb[q] == -1 || !was_a[pb[q]] && find_chain(pb[q])) {
            pa[vertex] = q, pb[q] = vertex;
            return true;
        }
    }
    return false;
}

void Kun(int n, int m) {
    pa.assign(n, -1), pb.assign(m, -1), was_a.assign(n, false);
    for (int q = 0; q < n; q++) {
        if (find_chain(q)) {
            was_a.assign(n, false);
        }
    }
}

int max_matching(int n, int m) {
    Kun(n, m);
    return n-count(pa.begin(), pa.end(), -1);
}

void DFS_L_minus(int vertex) {
    was_a[vertex] = true;
    for (int q : d[vertex]) {
        if (q == pa[vertex] || was_b[q]) {
            continue;
        }
        was_b[q] = true;
        if (pb[q] != -1 && !was_a[pb[q]]) {
            DFS_L_minus(pb[q]);
        }
    }
}

int independent_set(int n, int m) {
    Kun(n, m);
    was_a.assign(n, false), was_b.assign(m, false);
    for (int q = 0; q < n; q++) {
        if (pa[q] == -1) {
            DFS_L_minus(q);
        }
    }
    return count(was_a.begin(), was_a.end(), true)+count(was_b.begin(), was_b.end(), false);
}

int paths_splitting(int n) {
    return n-max_matching(n, n);
}

void DFS_reachable(int vertex) {
    was_a[vertex] = true;
    for (int q : d[vertex]) {
        if (!was_a[q]) {
            DFS_reachable(q);
        }
    }
}

void make_transitive_closure(int n) {
    for (int q = 0; q < n; q++) {
        was_a.assign(n, false);
        DFS_reachable(q);
        d[q] = {};
        for (int q1 = 0; q1 < n; q1++) {
            if (q != q1 && was_a[q1]) {
                d[q].push_back(q1);
            }
        }
    }
}

int max_antichain(int n) {
    make_transitive_closure(n);
    return independent_set(n, n)-n; // was_a && !was_b
}

