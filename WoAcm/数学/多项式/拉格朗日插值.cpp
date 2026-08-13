#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
constexpr ll mod = 998244353;
ll ksm(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % mod;
        }
        b >>= 1;
        a = a * a % mod;
    }
    return res;
}
ll inv(ll a) {
    return ksm(a, mod - 2);
}
ll Lagrange(const vector<pair<ll, ll>> &points, ll k) {
    ll ans = 0;
    for (int i = 0; i < points.size(); i++) {
        auto [x, y] = points[i];
        ll sum = 1;
        for (int j = 0; j < points.size(); j++) {
            if (i == j) {
                continue;
            }
            auto [nx, _] = points[j];
            y = y * (k - nx + mod) % mod;
            sum = sum * (x - nx + mod) % mod;
        }
        ans = (ans + y * inv(sum)) % mod;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;ll k;
    cin >> n >> k;
    vector<pair<ll, ll>> v(n);
    for (auto &[x, y] : v) {
        cin >> x >> y;
    }
    cout << Lagrange(v, k) << '\n';
    return 0;
}