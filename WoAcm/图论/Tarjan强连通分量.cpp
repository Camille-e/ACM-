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
    vector<vector<int>> scc;//可以不要
    vector<vector<int>>g;
    vector<int> dfn, low, ins, bel, stk;
    Tarjan (const int& n) : n(n){
        scc = g = vector<vector<int>>(n + 1);
        dfn = low = ins = bel = stk = vector<int>(n + 1);
    };
    //添加一条u -> v的边
    void addedge(int u,int v){
        g[u].push_back(v);
    };
    int cnt = 0, tot = 0, top = 0;
    void dfs (int id){
        dfn[id] = low[id] = ++cnt;
        stk[++top] = id;
        ins[id] = 1;
        for(auto nxt : g[id]) {
            if(!dfn[nxt]) {
                dfs(nxt);
                low[id] = min(low[id], low[nxt]);
            } else if(ins[nxt]) {
                low[id] = min(low[id], dfn[nxt]);
            }
        }
        if(dfn[id] == low[id]) {
            ++tot;
            while(true) {
                int num = stk[top--];
                ins[num] = 0;
                bel[num] = tot;
                scc[tot].push_back(num);//可以不要
                if(id == num) break;
            }
        }
    }
    void build(){
        for(int i = 1;i <= n;++i){
            if(!dfn[i]){
                dfs(i);
            }
        }
    }
};
// 缩点 && 去重边
// int pren = n;
// 记得此时的n是缩点之后的n
// 拓扑排序时可以直接利用tarjan逆拓扑的性质直接从后往前遍历
// n = tar.tot;
// vector<vector<int>>g(n + 1);vector<int>in(n + 1),out(n + 1),vis(n + 1);
// for(int i = 1;i <= n;++i){
//     for(auto cur : tar.scc[i]){
//         for(int to : tar.g[cur]){
//             if(tar.bel[to] != i){
//                 if(vis[tar.bel[to]] == 0){
//                     vis[tar.bel[to]] = 1;
//                     g[i].push_back(tar.bel[to]);
//                     in[tar.bel[to]]++;
//                     out[i]++;
//                 }
//             }
//         }
//     }
//     for(auto to : g[i])vis[to] = 0;
// }
void solve(){
    int n,m;
    cin >> n >> m;
    Tarjan tar(n);
    for(int i = 0;i < m;++i){
        int u,v;
        cin >> u >> v;
        tar.addedge(u,v);
    }
    tar.build();
    for(int i = 1;i <= tar.tot;++i){
        sort(tar.scc[i].begin(),tar.scc[i].end());
    }
    sort(tar.scc.begin() + 1, tar.scc.begin() + tar.tot + 1);
    cout << tar.tot << '\n';
    for(int i = 1; i <= tar.tot; ++i) {
        for(int j = 0; j < tar.scc[i].size(); ++j) {
            std::cout << tar.scc[i][j] << " \n"[j == tar.scc[i].size() - 1];
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