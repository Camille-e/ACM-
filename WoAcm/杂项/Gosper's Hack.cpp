#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
ll ksm(ll a,ll b){
    ll res = 1;
    a %= mod;
    while(b){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
};
ll inv(ll a){
    return ksm(a,mod - 2);
}
void enumerate_combinations(int n, int k) {
    assert(n >= 0 && n <= 64);
    assert(k >= 0 && k <= n);
    if (k == 0) {
        cout << 0 << '\n';
        return;
    }
    if (k == n) {
        cout << (1ULL << n) - 1 << '\n';
        return;
    }
    unsigned long long x = (1ULL << k) - 1;
    unsigned long long limit = (1ULL << n);
    while (x < limit) {
        // std::bitset<64> bs(x);
        // std::string binary = bs.to_string().substr(64 - n);
        cout << x << '\n';
        unsigned long long u = x & -x;
        unsigned long long v = x + u;
        x = v + ((v ^ x) / u >> 2);
    }
}
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
auto rnd = [](ll l, ll r) { return (l <= r ? uniform_int_distribution<ll>(l, r)(rng) : 0); };
void solve(){
    enumerate_combinations(4,2);
}
signed main() {
    IOS;
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}