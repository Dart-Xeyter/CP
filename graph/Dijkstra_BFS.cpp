vector<vector<int>> d;

vector<int> BFS(int vertex) {
    int n = d.size();
    vector<int> dist(n, INF);
    queue<int> a;
    a.push(vertex);
    dist[vertex] = 0;
    while (!a.empty()) {
        int x = a.front();
        a.pop();
        for (int q : d[x]) {
            if (dist[q] > dist[x]+1) {
                dist[q] = dist[x]+1;
                a.push(q);
            }
        }
    }
    return dist;
}

vector<vector<p>> d;

vector<int> Dijkstra(int vertex) {
    int n = d.size();
    vector<int> dist(n, INF);
    vector<bool> was(n, false);
    priority_queue<p> a;
    a.emplace(0, vertex);
    dist[vertex] = 0;
    while (!a.empty()) {
        auto [_, x] = a.top();
        a.pop();
        if (was[x]) {
            continue;
        }
        was[x] = true;
        for (auto [q1, c] : d[x]) {
            if (dist[q1] > dist[x]+c) {
                dist[q1] = dist[x]+c;
                a.emplace(-dist[q1], q1);
            }
        }
    }
    return dist;
}
