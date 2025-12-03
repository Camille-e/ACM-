#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
using ui = unsigned int;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
// https://www.luogu.com.cn/problem/P3379
void solve() {
    int n,m,s;
    cin >> n >> m >> s;
    vector<vector<int>>g(n + 1);
    int u,v;
    for(int i = 0;i < n - 1;++i){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int p = __lg(n + 1);
    vector<int>deep(n + 1);
    vector<vector<int>>st(n + 1,vector<int>(p + 2));
    auto dfs = [&](auto &&dfs,int i,int fa)->void
    {
        st[i][0] = fa;
        deep[i] = deep[fa] + 1;
        for(int j = 1;(1 << j) <= deep[i];++j){
            st[i][j] = st[st[i][j - 1]][j - 1];
        }
        for(int j = 0;j < g[i].size();++j){
            if(g[i][j] != fa){
                dfs(dfs,g[i][j],i);
            }
        }
    };
    dfs(dfs,s,0);
    auto lca = [&](int u,int v){
        int curu = u;
        int curv = v;
        if(deep[u] > deep[v]){
            int diff = deep[u] - deep[v];
            int k = 32 - __builtin_clz(diff);
            for(int j = 0;j < k;++j){
                if((diff >> j) & 1)
                curu = st[curu][j];
            }
        }
        if(deep[v] > deep[u]){
            int diff = deep[v] - deep[u];
            int k = 32 - __builtin_clz(diff);
            for(int j = 0;j < k;++j){
                if((diff >> j) & 1)
                curv = st[curv][j];
            }
        }
        if(curu == curv){
            return curu;
        }
        int k = 32 - __builtin_clz(deep[curv]);
        for(int j = k - 1;j >= 0;--j){
            if(st[curv][j] != st[curu][j]){
                curv = st[curv][j];
                curu = st[curu][j];
            }
        }
        return st[curv][0];
    };
    for(int i = 0;i < m;++i){
        cin >> u >> v;
        cout << lca(u,v) << '\n'; 
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