#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//O(1.5 * n * sqrt(m))
//一般块长设置为ceil(n / sqrt(m)),过不了设置为(n / sqrt(2 * m))
void solve(){
    int n, m;
    cin >> n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i)cin >> a[i];
    int kind = 0;
    //看情况改数据范围;
    vector<int>cnt(1e6 + 1);
    cin >> m;
    //l,r,id
    int unit = ceil(n / sqrt(m));
    vector<array<int,3>>q(m);
    for(int i = 0;i < m;++i){
        cin >> q[i][0] >> q[i][1];
        q[i][2] = i;
    }
    sort(q.begin(),q.end(),[&](array<int,3>&a,array<int,3>&b){
        if(a[0] / unit != b[0] / unit){
            return a[0] < b[0];
        }
        if((a[0] / unit) & 1)return a[1] > b[1];
        return a[1] < b[1];
    });
    //看情况改这个
    auto update = [&](int x,int num){
        if(num == -1){
            if(--cnt[x] == 0){
                kind--;
            }
        }else{
            if(++cnt[x] == 1){
                kind++;
            }
        }
    };
    int winl = 1,winr = 0;
    vector<int>ans(m);
    for(int i = 0;i < m;++i){
        auto [l,r,id] = q[i];
        while(winl > l)update(a[--winl],1);
        while(winr < r)update(a[++winr],1);
        while(winl < l)update(a[winl++],-1);
        while(winr > r)update(a[winr--],-1);
        ans[id] = kind;
    }
    for(int i = 0;i < m;++i){
        cout << ans[i] << '\n';
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