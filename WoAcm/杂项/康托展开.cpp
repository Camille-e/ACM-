#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
//https://www.luogu.com.cn/problem/P5367
using namespace std;
const int mod = 998244353;
const int maxn = 1e5 + 2;
void solve(){
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;++i)cin >> a[i];
    vector<int>tree(n + 1);
    auto add = [&](int x,int val){
        while(x <= n){
            tree[x] += val;
            x += (x & -x);
        }
    };
    auto query = [&](int x){
        int res = 0;
        while(x){
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    };
    vector<ll>fac(n + 1,1);
    for(int i = 1;i <= n;++i){
        fac[i] = fac[i - 1] * i % mod;
    }
    for(int i = 1;i <= n;++i){
        add(i,1);
    }
    ll res = 0;
    for(int i = 0;i < n;++i){
        int k = query(a[i] - 1);
        //cout << k << '\n';
        add(a[i],-1);
        res += k * fac[n - i - 1] % mod;
        res %= mod;
    }
    cout << (res + 1) % mod << '\n';
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