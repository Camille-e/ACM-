#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
void solve() {
    int n, u, v;
    cin >> n;
    vector<vector<int>>g(n + 1);
    for(int i = 1;i < n;++i){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>ans(n + 1);
    auto dfs = [&](auto && dfs,int i,int fa)->int
    {
        int maxv = 0;
        for(auto to : g[i]){
            if(to != fa){
                int cur = dfs(dfs,to,i);
                ans[i] = max(ans[i],maxv + cur);
                maxv = max(cur,maxv);
            }
        }
        return  maxv + 1;
    };
    dfs(dfs,1,0);
    cout << *max_element(ans.begin(),ans.end()) << '\n';
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