#include <bits/stdc++.h>
using ll = long long;
using namespace std;
array<ll, 3> exgcd(ll a, ll b) {
    if(b == 0) {
        return {a, 1, 0};
    }
    auto [gd, x, y] = exgcd(b, a % b);
    return {gd, y, x - a / b * y};
}
array<ll,2> spxy(ll x0,ll y0,ll c,ll gd){
    return {x0 * c / gd,y0 * c / gd};
}
// ax + by = c;
// x = tx + (b / d) * n;
// y = ty - (a / d) * n;
ll EXCRT(vector<pair<ll, ll>> &v) {
    ll M = v[0].first, ans = v[0].second;
    for(int i = 1; i < v.size(); ++i) {
        auto [m, r] = v[i];
        auto [gd, x, y] = exgcd(M, m);
        ll dx = ((ans - r) % m + m) % m;
        if(dx % gd != 0) return -1;
        ll k = m / gd;
        x = __int128(dx / gd) % k * x % k;
        ans -= x * M;
        M *= k;
        ans = (ans % M + M) % M;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<ll, ll>> v(n);
    for(auto &[m, r] : v) {
        cin >> m >> r;
    }
    cout << EXCRT(v) << '\n';
    return 0;
}