#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://www.luogu.com.cn/problem/P8435
struct Tarjan{
    int n,m;
    vector<vector<int>>g;
    vector<vector<int>> vcc;
    vector<int> dfn, low, stk;
    vector<pair<int,int>> estk;
    vector<vector<pair<int,int>>> vcc_edges;
    Tarjan (const int & _n,const int & _m) : n(_n), m(_m){
        g = vcc = vector<vector<int>>(n + 1);
        vcc_edges = vector<vector<pair<int,int>>>(n + 1);
        dfn = low = stk = vector<int>(n + 1);
        estk = vector<pair<int,int>>(m + 1);
    };
    int cnt = 0, tot = 0, top = 0, etop = 0;
    void dfs(int id, int lst){
        dfn[id] = low[id] = ++cnt;
        stk[++top] = id;
        int num = 0;
        for(auto nxt : g[id]) {
            if(!dfn[nxt]) {
                num++;
                estk[++etop] = {min(id,nxt),max(id,nxt)};
                dfs(nxt, id);
                low[id] = min(low[id], low[nxt]);
                if(low[nxt] >= dfn[id]) {
                    ++tot;
                    while(true) {
                        int num = stk[top--];
                        vcc[tot].push_back(num);
                        if(num == nxt) break;
                    }
                    while (true) {
                        auto e = estk[etop--];
                        vcc_edges[tot].push_back(e);
                        if (e == make_pair(min(id, nxt), max(id, nxt))) {
                            break;
                        }
                    }
                    vcc[tot].push_back(id);
                }
            } else if(nxt != lst && dfn[nxt] < dfn[id]) {
                estk[++etop] = {min(id, nxt), max(id, nxt)};
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
                top = 0;
                etop = 0;
            }
        }
    }
};
// int pren = n;
// //这是缩点后树上点的个数
// n = tar.tot;
void solve(){
    int n,m;
    cin >> n >> m;
    Tarjan tar(n,m);
    for(int i = 1;i <= m;++i){
        int u,v;cin >> u >> v;
        tar.addedge(u,v);
    }
    tar.build();
    cout << tar.tot << '\n';
    for(int i = 1;i <= tar.tot;++i){
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