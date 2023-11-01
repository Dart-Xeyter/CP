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
    int n = (int)d.size();
    was.assign(n, false), topsort = {};
    top_sort(vertex);
    reverse(topsort.begin(), topsort.end());
    vector<int> dist(n, INF);
    dist[vertex] = 0;
    bool flag = true;
    for (int q2 = 0; q2 < n; q2++) {
        flag = false;
        for (int q : topsort) {
            for (p q1 : d[q]) {
                if (dist[q1.first] > dist[q]+q1.second) {
                    dist[q1.first] = dist[q]+q1.second;
                    flag = true;
                }
            }
        }
    }
    return flag ? vector<int>() : dist;
}

