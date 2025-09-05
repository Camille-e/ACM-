#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
struct Inv_fac{
    int n;
    vector<ll>facinv,inv,fac;
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
    }
    Inv_fac(const int & _n) : n(_n){
        facinv = inv = fac = vector<ll>(n + 1);
        auto build = [&](){
            fac[0] = fac[1] = 1;
            inv[1] = 1;
            for(int i = 2;i <= n;++i){
                fac[i] = fac[i - 1] * i % mod;
                inv[i] = mod - inv[mod % i] * (mod / i) % mod;
            }
            facinv[n] = ksm(fac[n],mod - 2);
            for(int i = n - 1;i >= 0;--i){
                facinv[i] = (i + 1) * facinv[i + 1] % mod;
            }
        };
        build();
    }
};
void solve(){
    
}
signed main() {
    IOS;
    int _ = 1;
    //cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}