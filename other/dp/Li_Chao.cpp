struct Line {
    int k, b;

    Line(): k(0), b(INF) {}
    Line(int k, int b): k(k), b(b) {}

    int value(int x) const {
        return k*x+b;
    }
};

struct Node {
    Line line;
    Node *l, *r;

    explicit Node(Line line): line(line), l(nullptr), r(nullptr) {}

    void make_sons() {
        if (l == nullptr) {
            l = new Node(Line());
        }
        if (r == nullptr) {
            r = new Node(Line());
        }
    }
};

struct Li_Chao { // min
    Node* root;
    int MIN, MAX;

    Li_Chao(int MIN, int MAX): MIN(MIN), MAX(MAX), root(new Node(Line())) {}

    static void add(int l, int r, Node* tree, Line line) {
        int m = (l+r)/2;
        if (line.value(m) < tree->line.value(m)) {
            swap(line, tree->line);
        }
        if (r-l == 1) {
            return;
        }
        tree->make_sons();
        if (line.k < tree->line.k) {
            add(m, r, tree->r, line);
        } else {
            add(l, m, tree->l, line);
        }
    }

    void add(Line line) const {
        add(MIN, MAX, root, line);
    }

    static int ans(int l, int r, Node* tree, int x) {
        int answer = tree->line.value(x);
        if (r-l == 1) {
            return answer;
        }
        tree->make_sons();
        int m = (l+r)/2;
        if (x < m) {
            answer = min(answer, ans(l, m, tree->l, x));
        } else {
            answer = min(answer, ans(m, r, tree->r, x));
        }
        return answer;
    }

    int ans(int x) const {
        return ans(MIN, MAX, root, x);
    }
};

