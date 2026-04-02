#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
struct Triple {
    int a, b, c;
};
//O(nlogn)生成c <= lim
vector<Triple> primitive_pythagorean(int lim) {
    vector<Triple> res;
    for (int m = 2; 1LL * m * m + 1 <= lim; ++m) {
        for (int n = 1; n < m; ++n) {
            if (((m - n) & 1) == 0) continue;
            if (gcd(m, n) != 1) continue;
            int a = m * m - n * n;
            int b = 2 * m * n;
            int c = m * m + n * n;
            if (c > lim) break;
            if (a > b) swap(a, b);
            res.push_back({a, b, c});
        }
    }
    return res;
}
vector<Triple> all_pythagorean(int lim) {
    vector<Triple> res;
    for (int m = 2; 1LL * m * m + 1 <= lim; ++m) {
        for (int n = 1; n < m; ++n) {
            if (((m - n) & 1) == 0) continue;
            if (gcd(m, n) != 1) continue;
            int a = m * m - n * n;
            int b = 2 * m * n;
            int c = m * m + n * n;
            if (c > lim) break;
            if (a > b) swap(a, b);
            for (int k = 1; 1LL * k * c <= lim; ++k) {
                res.push_back({k * a, k * b, k * c});
            }
        }
    }
    return res;
}
int main() {
    int lim = 100;
    auto prim = primitive_pythagorean(lim);

    for (auto &t : prim) {
        cout << t.a << ' ' << t.b << ' ' << t.c << '\n';
    }
    return 0;
}
