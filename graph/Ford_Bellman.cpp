vector<vector<p>> d;
vector<bool> was;
vector<int> topsort;

void top_sort(int vertex) {
    was[vertex] = true;
    for (p q : d[vertex]) {
        if (!was[q.first]) {
            top_sort(q.first);
        }
    }
    topsort.push_back(vertex);
}

vector<int> Ford_Bellman(int vertex) {
    int n = d.size();
    vector<int> dist(n, INF);
    dist[vertex] = 0;
    was.assign(n, false), topsort = {};
    top_sort(vertex);
    reverse(topsort.begin(), topsort.end());
    bool flag = true;
    int q2 = 0;
    while (flag && q2 < n) {
        flag = false, q2++;
        for (int q : topsort) {
            for (p q1 : d[q]) {
                if (dist[q1.first] > dist[q1.first]+q1.second) {
                    dist[q1.first] = dist[q1.first]+q1.second, flag = true;
                }
            }
        }
    }
    if (flag) {
        return {};
    }
    return dist;
}
