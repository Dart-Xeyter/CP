struct DO {
    vector<int> do_arr, mins;
    vector<bool> degs;
    int len;
 
    DO(vector<int> a) {
        len = 1;
        while (len < a.size()) {
            len <<= 1;
        }
        do_arr.assign(len << 1, 0), mins.assign(len << 1, INF);
        degs.assign(len << 1, false), degs[len] = true;
        for (int q = len; q < a.size()+len; q++) {
            do_arr[q] = mins[q] = a[q-len];
        }
        for (int q = len-1; q > 0; q--) {
            do_arr[q] = do_arr[q << 1]+do_arr[(q << 1)+1];
            mins[q] = min(mins[q << 1], mins[(q << 1)+1]);
            degs[q] = degs[q << 1];
        }
    }
 
    void change(int q, int x) {
        do_arr[q+len] = x, mins[q+len] = x;
        q = ((q+len) >> 1);
        while (q > 0) {
            do_arr[q] = do_arr[q << 1]+do_arr[(q << 1)+1];
            mins[q] = min(mins[q << 1], mins[(q << 1)+1]);
            q >>= 1;
        }
    }
 
    int ans(int l, int r) {
        if (l >= r) {
            return 0;
        }
        l += len, r += len-1;
        int sum1 = 0;
        while (l < r) {
            sum1 += (l & 1)*do_arr[l];
            l = ((l+1) >> 1);
            sum1 += ((r & 1) ^ 1)*do_arr[r];
            r = ((r-1) >> 1);
        }
        return sum1+(l == r)*do_arr[l];
    }
 
    int left_less(int q, int x) {
        q += len;
        while (!degs[q] && mins[q] >= x) {
            q = ((q-1) >> 1);
        }
        if (mins[q] >= x) {
            return -1;
        }
        while (q < len) {
            q = (q << 1)+(mins[(q << 1)+1] < x);
        }
        return q-len;
    }
};

