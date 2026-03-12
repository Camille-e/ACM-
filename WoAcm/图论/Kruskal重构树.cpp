#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://www.luogu.com.cn/problem/P2245
struct DSU{
    DSU(int n) : fa(n + 1),sz(n + 1,1){
        iota(fa.begin(),fa.end(),0);
    }
    vector<int>fa,sz;
    int find(int x){
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool same(int u,int v){
        return find(u) == find(v);
    }
    //代表节点当父亲要传到第一个
    int merge(int f,int z){
        f = find(f),z = find(z);
        sz[f] += sz[z];
        fa[z] = f;
        return f;
    }
    int size(int x){
        return sz[find(x)];
    }
};
struct HLD{
    HLD(const int & n) : n(n), g(n + 1) {
        deep = fa = sz = son = top = dfn = seg = vector<int>(n + 1);
    }
    void build(int root = 1){
        dfs(root,0);
        dfs1(root,root);
    }
    int n;
    vector<int>deep,fa,sz,son,top,dfn,seg;
    vector<vector<int>>g;
    void addedge(const int & x ,const int & y){
        g[x].push_back(y);
        g[y].push_back(x);
    }
    void dfs(int i,int f){
        deep[i] = deep[f] + 1;
        sz[i] = 1;
        fa[i] = f;
        for(const int & to : g[i]){
            if(to != f){
                dfs(to,i);
                sz[i] += sz[to];
                if(sz[to] > sz[son[i]]){
                    son[i] = to;
                }
            }
        }
    };
    int cntd = 0;
    void dfs1(int i,int t){
        top[i] = t;
        dfn[i] = ++cntd;
        seg[cntd] = i;
        if(son[i] == 0)return;
        dfs1(son[i],t);
        for(const int & to : g[i]){
            if(to != son[i] && to != fa[i]){
                dfs1(to,to);
            }
        }
    };
    int queryLCA(int u,int v){
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            u = fa[top[u]];
        }
        return dfn[u] < dfn[v] ? u : v;
    }
    int kth(int id, int k) {
        if(k > deep[id]) return 0;
        while(deep[id] - deep[top[id]] + 1 <= k) {
            k -= (deep[id] - deep[top[id]] + 1);
            id = fa[top[id]];
        }
        return seg[dfn[id] - k];
    }
};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
auto rnd = [](ll l, ll r) { return (l <= r ? uniform_int_distribution<ll>(l, r)(rng) : 0); };
void solve(){
    int n,m;cin >> n >> m;
    vector<vector<int>>g(n + 1);
    vector<array<int,3>>edges(m + 1);
    for(int i = 1;i <= m;++i){
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
    }
    sort(edges.begin() + 1,edges.end());
    DSU dsu(n * 2 + 1);
    HLD tree(2 * n);
    int cnt = n;
    vector<int>val(2 * n + 1);
    for(int i = 1;i <= m;++i){
        auto [w,u,v] = edges[i];
        if(!dsu.same(u,v)){
            int f1 = dsu.find(u),f2 = dsu.find(v);
            ++cnt;
            tree.addedge(f1,cnt);
            tree.addedge(f2,cnt);
            //代表节点当父亲要传到第一个
            dsu.merge(cnt,f1);
            dsu.merge(cnt,f2);
            val[cnt] = w;
        }
    }
    for(int i = cnt;i >= 1;--i){
        if(tree.deep[i] == 0)tree.build(i);
    }
    int q;cin >> q;
    for(int i = 1;i <= q;++i){
        int u,v;cin >> u >> v;
        if(!dsu.same(u,v)){
            cout << "impossible\n";
        }else{
            cout << val[tree.queryLCA(u,v)] << '\n';
        }
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