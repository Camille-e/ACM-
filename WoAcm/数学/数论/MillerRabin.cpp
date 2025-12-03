#include <bits/stdc++.h>
using ll = long long;
using namespace std;
ll qpow(ll a, ll b, ll p) {
    ll res = 1;
    while(b) {
        if(b & 1) {
            res = (__int128)res * a % p;
        }
        a = (__int128)a * a % p;
        b >>= 1; 
    }
    return res;
}

bool Minller(ll n) {
    if(n == 2) return true;
    if(n <= 1 || n % 2 == 0) return false;
    ll u = n - 1, k = 0;
    while(u % 2 == 0) u /= 2, ++k;
    static vector<ll> base = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for(auto x : base) {
        ll res = qpow(x, u, n);
        if(res == 0 || res == 1 || res == n - 1) continue;
        for(int i = 1; i <= k; ++i) {
            res = (__int128)res * res % n;
            if(res == n - 1) break;
            if(i == k) return false;
        }
    }
    return true;
}

void solve() {
    ll x;
    cin >> x;
    cout << (Minller(x) ? "YES" : "NO") << '\n';
}

//Miller_rabin素数测验
//https://www.luogu.com.cn/problem/SP288
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}