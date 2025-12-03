#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
struct Tarjan{
    int n;
    vector<vector<int>>ecc;
    vector<vector<pair<int,int>>>g;
    vector<int>dfn, low, stk, bel;
    Tarjan (const int & _n) : n(_n){
        ecc = vector<vector<int>>(n + 1);
        g = vector<vector<pair<int,int>>>(n + 1);
        dfn = low = stk = bel = vector<int>(n + 1);
    };
    //添加编号防止重边
    void addedge(int u,int v,int i){
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }
    int cnt = 0, tot = 0, top = 0;
    void dfs(int id, int lid){
        dfn[id] = low[id] = ++cnt;
        stk[++top] = id;
        for(auto [nxt, eid] : g[id]) {
            if(!dfn[nxt]) {
                dfs(nxt, eid);
                low[id] = min(low[id], low[nxt]);
            } else if(lid != eid) {
                low[id] = min(low[id], dfn[nxt]);
            }
        }
        if(dfn[id] == low[id]) {
            ++tot;
            while(true) {
                int num = stk[top];
                ecc[tot].push_back(num);
                bel[num] = tot;
                top--;
                if(id == num) break;
            }
        }
    };
    void build(){
        for(int i = 1; i <= n; ++i) {
            if(!dfn[i]) {
                dfs(i, 0);
            }
        }
    }
};
// //缩点 && 去重边
// int pren = n;
// //这是缩点后树上点的个数
// n = tar.tot;
// vector<vector<int>>g(n + 1);
// vector<int>vis(n + 1);
// for(int i = 1;i <= n;++i){
//     for(auto x : tar.ecc[i]){
//         for(auto [k,id] : tar.g[x]){
//             if(tar.bel[k] != i && !vis[tar.bel[k]]){
//                 g[i].push_back(tar.bel[k]);
//                 vis[tar.bel[k]] = 1;
//             }
//         }
//     }
//     for(auto to : g[i])vis[to] = 0;
// }
void solve(){
    int n,m;
    cin >> n >> m;
    Tarjan tar(n);
    for(int i = 1;i <= m;++i){
        int u,v;cin >> u >> v;
        tar.addedge(u,v,i);
    }
    tar.build();
    cout << tar.tot << '\n';
    for(int i = 1;i <= n;++i){
        if(tar.ecc[i].size()){
            cout << tar.ecc[i].size() << ' ';
            for(auto x : tar.ecc[i]){
                cout << x << ' ';
            }
            cout << '\n';
        }
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