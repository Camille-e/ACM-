#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://www.luogu.com.cn/problem/P8671
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
void solve(){
    int n,k;
    cin >> n >> k;
    int ans = 1;
    for(int i = 2;i <= n;++i){
        ans = (ans + k - 1) % i + 1;
    }
    cout << ans << '\n';
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