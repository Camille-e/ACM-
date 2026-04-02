#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
struct CUTAD{
    int n;
    vector<vector<pair<int,int>>>g;
    vector<int> dfn, low;
    vector<pair<int,int>>bridge;
    CUTAD (const int & _n) : n(_n){
        g = vector<vector<pair<int,int>>>(n + 1);
        dfn = low = vector<int>(n + 1);
    };
    //加id防止重边
    void addedge(int u,int v,int id){
        g[u].push_back({v,id});
        g[v].push_back({u,id});
    };
    int cnt = 0;
    void dfs(int id, int lid){
        dfn[id] = low[id] = ++cnt;
        for(auto [to, eid] : g[id]) {
            if(eid == lid)continue;
            if(!dfn[to]){
                dfs(to, eid);
                low[id] = min(low[id], low[to]);
                if(low[to] > dfn[id]) { //是割边
                    bridge.push_back({id, to});
                }
            }else{
                low[id] = min(low[id], dfn[to]);
            }
        }
    };
    void build(){
        for(int i = 1;i <= n;++i){
            if(!dfn[i]){
                dfs(i,0);
            }
        }
    }
};
void solve(){
    int n,m;
    cin >> n >> m;
    CUTAD tar(n);
    for(int i = 1;i <= m;++i){
        int u,v;cin >> u >> v;
        tar.addedge(u,v,i);
    }
    tar.build();
    for(auto [a,b] : tar.bridge){
        cout << a << ' ' << b << '\n';
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