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
