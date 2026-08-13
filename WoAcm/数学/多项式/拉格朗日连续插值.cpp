#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
constexpr ll mod = 998244353;
ll qpow(ll a, ll b) {
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
    return qpow(a, mod - 2);
}
struct Lagrange {
    int n;
    vector<ll> y, fac, invfac;
    Lagrange() = default;
    Lagrange(const vector<ll> &_y) : n(_y.size() - 1), y(_y), fac(n + 1, 1), invfac(n + 1) {
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        invfac[n] = inv(fac[n]);
        for (int i = n; i >= 1; i--) {
            invfac[i - 1] = invfac[i] * i % mod;
        }
    }
// 1 - n
    ll solve(ll k) {
        if (k <= n) {
            return y[k];
        }
        vector<ll> pre(n + 1, 1), suf(n + 2, 1);
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] * (k - i) % mod;
        }
        for (int i = n; i >= 0; i--) {
            suf[i] = suf[i + 1] * (k - i) % mod;
        }
        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + y[i] * pre[i - 1] % mod * suf[i + 1] % mod * invfac[i - 1] % mod * invfac[n - i] % mod * (n - i & 1 ? mod - 1 : 1)) % mod;
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;ll k;
    cin >> n >> k;
    vector<ll> y(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> y[i];
    }
    Lagrange la(y);
    cout << la.solve(k) << '\n';
    return 0;
}