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
    vector<vector<int>>g;
    vector<std::vector<int>> vcc;
    vector<int> dfn, low, stk, bel;
    Tarjan (const int & _n) : n(_n){
        g = vcc = vector<vector<int>>(n + 1);
        dfn = low = stk = bel = vector<int>(n + 1);
    };
    int cnt = 0, tot = 0, top = 0;
    void dfs(int id, int lst){
        dfn[id] = low[id] = ++cnt;
        stk[++top] = id;
        int num = 0;
        for(auto nxt : g[id]) {
            if(!dfn[nxt]) {
                num++;
                dfs(nxt, id);
                low[id] = min(low[id], low[nxt]);
                if(low[nxt] >= dfn[id]) {
                    ++tot;
                    while(true) {
                        int num = stk[top];
                        --top;
                        vcc[tot].push_back(num);
                        bel[num] = tot;
                        if(num == nxt) break;
                    }
                    vcc[tot].push_back(id);
                }
            } else if(nxt != lst) {
                low[id] = min(low[id], dfn[nxt]);
            }
        }
        if(lst == 0 && num == 0) {
            ++tot;
            vcc[tot].push_back(id);
        }
    };
    void addedge(int u,int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
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
//     for(auto x : tar.vcc[i]){
//         for(auto k : tar.g[x]){
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
        tar.addedge(u,v);
    }
    tar.build();
    for(int i = 1;i <= n;++i){
        cout << tar.vcc[i].size() << ' ';
        for(auto to : tar.vcc[i]){
            cout << to << ' ';
        }
        cout << '\n';
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