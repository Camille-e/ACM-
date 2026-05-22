#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e7 + 2;
// https://www.luogu.com.cn/problem/P3455
vector<int>pri;
bitset<maxn>vis;
vector<int>mu(maxn,0);
vector<int>premu(maxn,0);
void mobius(){
    mu[1] = 1;
    for(int i = 2;i <= maxn;++i){
        if(!vis[i]){pri.push_back(i);mu[i] = -1;}
        for(int j = 0;i * pri[j] <= maxn;++j){
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0)
            {
                mu[i * pri[j]] = 0;
                break;
            }else{
                mu[i * pri[j]] = - mu[i];
            }
        }
    }
    for(int i = 1;i <= maxn;i++){
        premu[i] = premu[i - 1] + mu[i];
    }
}//莫比乌斯函数筛法
void solve(){
    ll a,b,d;
    cin >> a >> b >> d;
    ll ans = 0;
    a /= d;
    b /= d;
    for(ll l = 1,r;l <= min(a,b);l = r + 1){
        r = min(a / (a / l),b / (b / l));
        // ans += mu[i] *(a/i) * (b/i);
        ans += (premu[r] - premu[l - 1]) * (a / l) * (b / l);           
    }//整除分块
    cout << ans <<"\n";
}
signed main() {
    IOS;
    mobius();
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
