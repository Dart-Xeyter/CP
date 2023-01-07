unsigned seed = chrono::steady_clock::now().time_since_epoch().count();





mt19937 randint(179);
shuffle(perm.begin(), perm.end(), randint);





#include<bits/extc++.h>
#define int long long
#define p pair<int, int>
#define endl '\n'
const int INF = 1000000001;

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;





#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")





#include<bits/stdc++.h>
#define int long long
#define p pair<int, int>
#define endl '\n'
const int INF = 1000000001;

using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}





set(CMAKE_CXX_FLAGS -Wl,--stack=2000000179)
