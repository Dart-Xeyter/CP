vector<int> left_migration_less(vector<int> &a) {
    int n = a.size();
    vector<int> left(n, -1);
    vector<p> stack;
    for (int q = n-1; q > -1; q--) {
        while (!stack.empty() && stack.back().first > a[q]) {
            left[stack.back().second] = q;
            stack.pop_back();
        }
        stack.push_back({a[q], q});
    }
    return left;
}

vector<int> right_migration_less(vector<int> &a) {
    int n = a.size();
    vector<int> right(n, n);
    vector<p> stack;
    for (int q = 0; q < n; q++) {
        while (!stack.empty() && stack.back().first > a[q]) {
            right[stack.back().second] = q;
            stack.pop_back();
        }
        stack.push_back({a[q], q});
    }
    return right;
}

