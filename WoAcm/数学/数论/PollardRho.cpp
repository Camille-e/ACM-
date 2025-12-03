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

//Miller_rabin判断质数
bool Miller(ll n) {
    if(n <= 1 || n % 2 == 0) return (n == 2);
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

//Pollard_rho找因子
ll Pollard_rho(ll n) {
    assert(n >= 2);
    if(n == 4) return 2;
    static mt19937_64 rnd  (chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int64_t> rangeRand(1, n - 1);
    ll c = rangeRand(rnd);
    auto f = [&](ll x) {
        return ((__int128)x * x + c) % n;
    };
    ll x = f(0), y = f(x);
    while(x != y) {
        ll gd = gcd(abs(x - y), n);
        if(gd != 1) return gd;
        x = f(x), y = f(f(y));
    }
    return n;
}

void solve() {
    ll x;
    cin >> x;
    ll res = 0;
    auto max_factor = [&](auto self, ll x) ->void {
        if(x <= res || x < 2) return;
        if(Miller(x)) {
            //x是其中一个因子
            res = max(res, x);
            return;
        }
        ll p = x;
        while(p == x) {
            p = Pollard_rho(x);
        }
        while(x % p == 0) {
            x /= p;
        }
        self(self, x), self(self, p);
    };
    max_factor(max_factor, x);
    if(res == x) {
        cout << "Prime\n";
    } else {
        cout << res << '\n';
    }
}

//Pollard_rho快速求大数因子
//https://www.luogu.com.cn/problem/P4718
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