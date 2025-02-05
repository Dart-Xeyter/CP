__builtin_ffsll(x); // index of the last 1 (0 if x == 0)
__builtin_clzll(x); // number of leading zeros (x != 0)
__builtin_popcountll(x); // number of 1

bitset<17> b;
b._Find_first(); // index of first 1 in bitset
b._Find_next(3); // index of the next 1 in bitset





#pragma GCC optimize("O3,unroll-loops") // removes short cycles and repeats code of them instead
// [for (int q = 0; q < 3; q++) {ans += q;}] converts to [ans += 1, ans += 2, ans += 3]
#pragma GCC target("avx2,popcnt,lzcnt")
// avx2/avx/sse/sse2/sse3/sse4 -> do multiple operations in parallel in cycles
// popcnt/lzcnt/abm/bmi/bmi2 -> do some bitwise operations in 1 processor action





set(CMAKE_CXX_FLAGS -fsplit-stack) // lets you create very huge arrays and vectors
set(CMAKE_CXX_FLAGS -fsanitize=address,undefined) // helps to find RE and UB
add_compile_definitions(-D_GLIBCXX_DEBUG -DLOCAL)

