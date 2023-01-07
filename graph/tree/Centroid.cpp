vector<vector<int>> d;
vector<int> height, sizes, f;
vector<bool> was_centroid;

void make_size(int vertex, int parent, int h) {
    sizes[vertex] = 1, height[vertex] = h;
    f.push_back(vertex);
    for (int q : d[vertex]) {
        if (!was_centroid[q] && q != parent) {
            make_size(q, vertex, h+1);
            sizes[vertex] += sizes[q];
        }
    }
}

int centroid(int vertex) {
    int parent = -1, all = sizes[vertex];
    bool flag = false;
    while (!flag) {
        flag = true;
        for (int q : d[vertex]) {
            if (!was_centroid[q] && q != parent && sizes[q]*2 > all) {
                parent = vertex, vertex = q, flag = false;
                break;
            }
        }
    }
    return vertex;
}

void centroid_decomposition(int vertex) {
    make_size(vertex, -1, 0);
    int k = centroid(vertex);
    f = {};
    make_size(k, -1, 0);
    was_centroid[k] = true;
    for (int q : d[k]) {
        if (!was_centroid[q]) {
            centroid_decomposition(q);
        }
    }
}

