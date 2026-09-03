#include<bits/stdc++.h>
using ll = long long;
using namespace std;
ll qpow(ll a, ll b, ll mod) {
    ll res = 1;
    while(b) {
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
ll primitive_root(ll P) {
    ll phi = P - 1;
    vector<ll> fac;
    ll x = phi;
    for(ll i = 2; i * i <= x; ++i) {
        if(x % i == 0) {
            fac.push_back(i);
            while(x % i == 0) {
                x /= i;
            }
        }
    }
    if(x > 1) fac.push_back(x);
    for(ll g = 2; ; ++g) {
        bool ok = true;
        for(ll p : fac) {
            if(qpow(g, phi / p, P) == 1) {
                ok = false;
                break;
            }
        }
        if(ok) return g;
    }
}