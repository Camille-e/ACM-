#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 998244353;
using Poly = vector<ll>;
ll ksm(ll a, ll b = mod - 2) {
    ll res = 1;
    for (; b; b >>= 1, a = a * a % mod) {
        if (b & 1) res = res * a % mod;
    }
    return res;
}
void norm(Poly &a) {
    while (a.size() > 1 && a.back() == 0) {
        a.pop_back();
    }
}
// 返回 {商, 余数}
// 系数按低次到高次存储
pair<Poly, Poly> divi(Poly a, Poly b) {
    norm(a);
    norm(b);
    // assert(!(b.size() == 1 && b[0] == 0));
    if (a.size() < b.size()) {
        return {Poly{0}, a};
    }
    Poly q(a.size() - b.size() + 1, 0);
    ll inv = ksm(b.back());
    while (a.size() >= b.size() && !(a.size() == 1 && a[0] == 0)) {
        int d = a.size() - b.size();
        ll k = a.back() * inv % mod;
        q[d] = k;
        for (int i = 0; i < b.size(); i++) {
            a[i + d] = (a[i + d] - k * b[i] % mod + mod) % mod;
        }
        norm(a);
    }
    norm(q);
    norm(a);
    return {q, a};
}