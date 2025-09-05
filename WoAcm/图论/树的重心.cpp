#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//http://bailian.openjudge.cn/practice/1655/
void solve() {
    int n, u, v, w;
    cin >> n;
    //带权树的重心
    vector<int> a(n + 1);
    for(int i = 1;i <= n;++i){
        //修改点的点权
        a[i] = 1;
    }
    int sum = accumulate(a.begin(),a.end(),0);
    //是否为树的重心
    vector<bool>ok(n + 1);
    vector<vector<int>>g(n + 1);
    for(int i = 1;i < n;++i){
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    auto dfs = [&](auto && dfs,int i,int fa)->int
    {
        int sz = a[i];
        bool flag = 1;
        for(int j = 0;j < g[i].size();++j){
            auto to = g[i][j];
            if(to != fa){
                int szt = dfs(dfs,to,i);
                if(szt > sum / 2)flag = 0;
                sz += szt;
            }
        }
        if(sum - sz > sum / 2)flag = 0;
        ok[i] = flag;
        return sz;
    };
    dfs(dfs,1,0);
    for(int i = 1;i <= n;++i){
        if(ok[i]){
            cout << i << ' ';
        }
    }
    cout << '\n';
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