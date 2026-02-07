#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://atcoder.jp/contests/abc302/tasks/abc302_h
struct DSU {
    vector<int> siz,edges;
    vector<int> f;
    vector<array<int, 2>> his;
    
    DSU(int n) : siz(n + 1, 1), edges(n + 1), f(n + 1) {
        iota(f.begin(), f.end(), 0);
    }
    
    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        his.push_back({x, y});
        siz[x] += siz[y];
        edges[x] += edges[y] + 1;
        f[y] = x;
        return true;
    }
    
    bool same(int a,int b){
        return find(a) == find(b);
    }

    int time() {
        return his.size();
    }
    
    void revert(int tm) {
        while (his.size() > tm) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
            edges[x] -= edges[y] + 1;
        }
    }
};
void solve(){
    int n;cin >> n;
    vector<pair<int,int>>vc(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> vc[i].first >> vc[i].second;
    }
    DSU dsu(n + 1);
    vector<vector<int>>g(n + 1);
    for(int i = 1;i < n;++i){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>ans(n + 1);
    int cnt = 0;
    auto dfs = [&](auto && dfs,int i,int fa)->void
    {
        auto [a,b] = vc[i];
        int t = dsu.his.size();
        int s = 0,add = 0;
        int f1 = dsu.find(a);
        int f2 = dsu.find(b);
        if(f1 == f2){
            s = 1;
            if(dsu.edges[f1] < dsu.siz[f1]){
                cnt++;
                add = 1;
            }
            dsu.edges[f1]++;
        }else{
            if(dsu.edges[f1] < dsu.siz[f1] || dsu.edges[f2] < dsu.siz[f2]){
                cnt++;
                add = 1;
            }
            dsu.merge(f1,f2);
        }
        ans[i] = cnt;
        for(auto to : g[i]){
            if(to != fa){
                dfs(dfs,to,i);
            }
        }
        dsu.edges[f1] -= s;
        cnt -= add;
        dsu.revert(t);
    };
    dfs(dfs,1,0);
    for(int i = 2;i <= n;++i){
        cout << ans[i] << " \n"[i == n];
    }
}
signed main() {
    IOS;
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}