#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0) 
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
void solve(){
    //前置模板
    int n,m;
    cin >> n >> m;
    int len = sqrt(n);
    int cnum = (n - 1) / len + 1;
    vector<int>a(n + 1),pos(n + 1),bl(cnum + 1),br(cnum + 1);
    for(int i = 1;i <= n;++i){
        cin >> a[i];
        pos[i] = (i - 1) / len + 1;
    }
    for(int i = 1;i <= cnum;++i){
        bl[i] = len * (i - 1) + 1;
        br[i] = min(i * len,n);
    }
}
signed main() {
    IOS;
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}