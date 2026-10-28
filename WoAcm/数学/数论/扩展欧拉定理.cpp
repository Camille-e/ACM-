#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
const int N = 1e8 + 1;
int Phi(int n){
    int res = n;
    for(int i = 2;i * i <= n;++i){
        if(n % i == 0){
            res = res / i * (i - 1);
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1)res = res / n * (n - 1);
    return res;
}
ll ksm(ll a,ll b,ll mod){
    ll res = 1;
    a %= mod;
    while(b){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}
void solve(){
    ll a,m;cin >> a >> m;
    string b;cin >> b;
    ll mo = 0;
    ll phi = Phi(m);
    vector<int>k(b.size());
    k[0] = 1;
    for(int i = 1;i < b.size();++i){
        k[i] = k[i - 1] * 10 % phi;
    }
    for(int i = 0;i < b.size();++i){
        mo += (b[i] - '0') * k[b.size() - 1 - i] % phi;
        mo %= phi;
    }
    if(b.size() > 10){
        cout << ksm(a,mo + phi,m) << '\n';
    }else{
        ll num = stoll(b);
        if(num >= phi){
            cout << ksm(a,mo + phi,m) << '\n';
        }else{
            cout << ksm(a,mo,m) << '\n';
        }
    }
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