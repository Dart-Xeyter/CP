vector<vector<p>> d;

vector<int> Dijkstra(int vertex) {
    int n = d.size();
    vector<int> dist(n, INF);
    vector<bool> was(n, false);
    priority_queue<p> a;
    a.push({0, vertex});
    dist[vertex] = 0;
    while (!a.empty()) {
        p q = a.top();
        a.pop();
        int x = q.second;
        if (!was[x]) {
            was[x] = true;
            for (p q1 : d[x]) {
                if (dist[q1.first] > dist[x]+q1.second) {
                    dist[q1.first] = dist[x]+q1.second;
                    a.push({-dist[q1.first], q1.first});
                }
            }
        }
    }
    return dist;
}

