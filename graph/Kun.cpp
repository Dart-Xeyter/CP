vector<vector<int>> d;
vector<int> pa, pb;
vector<bool> was;

bool DFS_Kun(int vertex) {
    was[vertex] = true;
    for (int q : d[vertex]) {
        if (pb[q] == -1 || (!was[pb[q]] && DFS_Kun(pb[q]))) {
            pb[q] = vertex, pa[vertex] = q;
            return true;
        }
    }
    return false;
}

int Kun(int n, int m) {
    pa.assign(n, -1), pb.assign(m, -1);
    for (int q = 0; q < n; q++) {
        was.assign(n, false);
        DFS_Kun(q);
    }
    int ans = 0;
    for (int q : pa) {
        ans += (q != -1);
    }
    return ans;
}

