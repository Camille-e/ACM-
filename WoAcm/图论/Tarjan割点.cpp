#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
//tarjan求割点
//https://www.luogu.com.cn/problem/P3388
struct CUTP{
    int n;vector<vector<int>>g;
    vector<int>dfn,low,cut;
    CUTP (const int &_n) : n(_n){
        g = vector<vector<int>>(n + 1);
        dfn = low = cut = vector<int>(n + 1);
    }
    int cnt = 0, root = 0;
    void dfs(int id, int fa){
        dfn[id] = low[id] = ++cnt;
        int sz = 0; //儿子个数
        for(auto to : g[id]) {
            if(!dfn[to]) {
                sz++;
                dfs(to, id);
                low[id] = min(low[id], low[to]);
                if(low[to] >= dfn[id]) {
                    cut[id] = 1;
                }
            } else if(to != fa) {
                low[id] = min(low[id], dfn[to]);
            }
        }
        if(sz <= 1 && id == root) {
            cut[id] = 0;
        }
    };
    void addedge(int u,int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(){
        for(int i = 1;i <= n;++i){
            if(!dfn[i]){
                root = i;
                dfs(i,0);
            }
        }
    }
};
void solve(){
    
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