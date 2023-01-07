struct Mo {
    vector<int> num, light, vertex;
    vector<bool> wow;
    int C, sqrt1;

    Mo(int C_, int sqrt1_) {
        C = C_, sqrt1 = sqrt1_;
        num.assign(C, 0);
        wow.assign(C, false);
        light.assign(sqrt1, 0);
    }

    void add(int x) {
        if (num[x] < sqrt1) {
            light[num[x]]--;
        }
        num[x]++;
        if (num[x] < sqrt1) {
            light[num[x]]++;
        } else if (!wow[x]) {
            wow[x] = true;
            vertex.push_back(x);
        }
    }

    void del(int x) {
        if (num[x] < sqrt1) {
            light[num[x]]--;
        }
        num[x]--;
        if (num[x] < sqrt1) {
            light[num[x]]++;
        } else if (!wow[x]) {
            wow[x] = true;
            vertex.push_back(x);
        }
    }

    int ans(int k) {
        vector<int> heavy, vertex1;
        for (int q : vertex) {
            if (num[q] < sqrt1) {
                wow[q] = false;
            } else {
                vertex1.push_back(q);
                heavy.push_back(num[q]);
            }
        }
        vertex = vertex1;
        sort(heavy.begin(), heavy.end());
        int answer = INF;
        for (int q = (int)heavy.size()-1; q >= k-1; q--) {
            answer = min(answer, heavy[q]-heavy[q-k+1]);
        }
        int x = sqrt1-1, sum1 = min((int)heavy.size(), k-1);
        for (int q = sum1-1; q > -1; q--) {
            while (x > 0 && sum1+light[x] < k) {
                sum1 += light[x];
                x--;
            }
            if (x != 0) {
                answer = min(answer, heavy[q]-x);
            }
            sum1--;
        }
        x = 1, sum1 = 0;
        for (int q = 1; q < sqrt1; q++) {
            while (x < sqrt1 && sum1+light[x] < k) {
                sum1 += light[x];
                x++;
            }
            if (x < sqrt1) {
                answer = min(answer, x-q);
                sum1 -= light[q];
            }
        }
        return answer;
    }
};

