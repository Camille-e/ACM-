#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 998244353;
const int maxn = 2e5 + 2;
//https://atcoder.jp/contests/arc136/tasks/arc136_d
int pw[] = {1,10,100,1000,10000,100000};
void solve(){
    int n;cin >> n;
    vector<int>dp(1e6);
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> a[i];
        dp[a[i]]++;
    }
    for(int i = 0;i < 6;++i){
        for(int j = 0;j < 1e6;++j){
            if(j / pw[i] % 10 != 0){
                dp[j] += dp[j - pw[i]];
            }
        }
    }
    ll ans = 0;
    for(int i = 1;i <= n;++i){
        ans += dp[999999 - a[i]];
        int ok = 1;
        for(int j = 0;j < 6;++j){
            if(a[i] / pw[j] % 10 >= 5){
                ok = 0;
                break;
            }
        }
        ans -= ok;
    }
    cout << ans / 2 << '\n';
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