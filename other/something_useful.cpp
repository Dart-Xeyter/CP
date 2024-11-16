unsigned seed = chrono::steady_clock::now().time_since_epoch().count();





#include <bits/stdc++.h>
#define int long long
#define ld long double
#define p pair<int, int>
#define endl '\n'
const int INF = (int)1e9+1;

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;





#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")
// avx2 -> avx/sse/sse2/sse3/sse4
// popcnt -> lzcnt/bmi/bmi2/...





set(CMAKE_CXX_FLAGS -Wl,--stack=2000000179)
set(CMAKE_CXX_FLAGS -fsplit-stack)
set(CMAKE_CXX_FLAGS -fsanitize=address,undefined)
add_compile_options(-D LOCAL)

