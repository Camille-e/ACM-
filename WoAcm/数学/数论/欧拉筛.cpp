#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e8 + 2;
//https://www.luogu.com.cn/problem/P3383
vector<int>pri;
bitset<maxn>vis;
void eular(){
    for(int i = 2;i <= maxn;++i){
        if(!vis[i])pri.push_back(i);
        for(int j = 0;i * pri[j] <= maxn;++j){
            vis[i * pri[j]] = 1;
            if(i % pri[j] == 0)break;
        }
    }
}
void solve(){
    int n,q;cin >> n >> q;
    eular();
    for(int i = 1;i <= q;++i){
        int k;cin >> k;
        cout << pri[k - 1] << '\n';
    }
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