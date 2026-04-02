#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0) 
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 3e4 + 2;
//https://www.luogu.com.cn/problem/P3603
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
void solve(){
    //前置模板
    int n,m,f;
    cin >> n >> m >> f;
    vector<int>v(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> v[i];
    }
    HLD tree(n);
    for(int i = 1;i < n;++i){
        int u,v;cin >> u >> v;
        tree.addedge(u,v);
    }
    tree.build();
    int len = sqrt(n * 20);
    int cnum = (n - 1) / len + 1;
    vector<int>a(n + 1),pos(n + 1),bl(cnum + 1),br(cnum + 1);
    vector<bitset<maxn>>bit(cnum + 1);
    for(int i = 1;i <= n;++i){
        a[tree.dfn[i]] = v[i];
    }
    for(int i = 1;i <= n;++i){
        pos[i] = (i - 1) / len + 1;
    }
    for(int i = 1;i <= cnum;++i){
        bl[i] = len * (i - 1) + 1;
        br[i] = min(i * len,n);
        for(int j = bl[i];j <= br[i];++j){
            bit[i][a[j]] = 1;
        }
    }
    bitset<maxn>ans;
    auto calc = [&](int x,int y){
        int l = pos[x],r = pos[y];
        if(l == r){
            for(int k = x;k <= y;++k){
                ans[a[k]] = 1;
            }
        }else{
            for(int k = x;k <= br[l];++k){
                ans[a[k]] = 1;
            }
            for(int k = bl[r];k <= y;++k){
                ans[a[k]] = 1;
            }
            for(int k = l + 1;k <= r - 1;++k){
                ans |= bit[k];
            }
        }
    };
    ll lastans = 0;
    for(int i = 1;i <= m;++i){
        int len;cin >> len;
        ll kind = 0,mex = 0;
        ans.reset();
        for(int j = 1;j <= len;++j){
            int u,v;
            cin >> u >> v;
            if(f == 1){
                u ^= lastans;
                v ^= lastans;
            }
            while(tree.top[u] != tree.top[v]) { 
                if(tree.deep[tree.top[u]] < tree.deep[tree.top[v]]) {
                    swap(u, v);
                }
                calc(tree.dfn[tree.top[u]],tree.dfn[u]);
                u = tree.fa[tree.top[u]];
            }
            int x = tree.dfn[u],y = tree.dfn[v];
            if(x > y)swap(x,y);
            calc(x,y);
        }
        kind = ans.count();
        for(int k = 0;k < maxn;++k){
            if(ans[k] == 0){
                mex = k;
                break;
            }
        }
        lastans = kind + mex;
        cout << kind << ' ' << mex << '\n';
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