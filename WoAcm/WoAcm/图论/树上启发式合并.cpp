#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://www.luogu.com.cn/problem/U41492
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
    int n;cin >> n;
    vector<int>ans(n + 1);
    HLD tree(n);
    for(int i = 1;i < n;++i){
        int u,v;cin >> u >> v;
        tree.addedge(u,v);
    }
    tree.build();
    vector<int>a(n + 1);
    vector<int>color(n + 1);
    for(int i = 1;i <= n;++i)cin >> a[i];
    auto &g = tree.g;
    auto &son = tree.son;
    int cnt = 0;
    auto dfsf = [&](auto && dfsf,int i,int fa,int val)->void
    {
        if(val == -1){
            if(--color[a[i]] == 0)cnt--;
        }else{
            if(++color[a[i]] == 1)cnt++;
        }
        for(int to : g[i]){
            if(to != fa){
                dfsf(dfsf,to,i,val);
            }
        }
    };
    auto dfs = [&](auto && dfs,int i,int fa,int st)->void
    {
        for(int to : g[i]){
            if(to != fa && to != son[i]){
                dfs(dfs,to,i,0);
            }
        }
        if(son[i])
        dfs(dfs,son[i],i,1);
        for(int to : g[i]){
            if(to != fa && to != son[i]){
                dfsf(dfsf,to,i,1);
            }
        }
        if(++color[a[i]] == 1){
            cnt++;
        }
        ans[i] = cnt;
        if(st == 0){
            dfsf(dfsf,i,fa,-1);
        }
    };
    dfs(dfs,1,0,0);
    int q;cin >> q;
    for(int i = 1;i <= q;++i){
        int x;cin >> x;
        cout << ans[x] << "\n";
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