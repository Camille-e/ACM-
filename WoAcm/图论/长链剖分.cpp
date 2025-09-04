#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 998244353;
const int maxn = 1e5 + 2;
struct LLD{
    int n, m;
    vector<vector<int>>st, g, up, down;
    vector<int> dep, len, son, lg, top, dfn;
    LLD(const int &_n) : n(_n) {
        son = len = dep = top = dfn = vector<int>(n + 1);
        lg = vector<int>(n + 2);
        g = up = down = vector<vector<int>>(n + 1);
        m = bit_width(bit_ceil((unsigned)n));
        st = vector<vector<int>>(n + 1,vector<int>(m + 1));
        for(int i = 2; i <= n; ++i) {
            lg[i] = lg[i >> 1] + 1;
        }
    };
    void addEdge(const int &u, const int &v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void dfs1(int i, int fa) {
        st[i][0] = fa;
        dep[i] = dep[fa] + 1;
        len[i] = 1;
        for(int p = 1;p <= m;++p){
            st[i][p] = st[st[i][p - 1]][p - 1];
        }
        
        for(const auto &to : g[i]) {
            if(to == fa) continue;
            dfs1(to, i);
            if(len[to] + 1 > len[i]) {
                len[i] = len[to] + 1;
                son[i] = to;
            }
        }
    }
    int cnt = 0;
    void dfs2(int i, int t) {
        top[i] = t;
        dfn[i] = ++cnt;
        if(son[i] == 0) return;
        dfs2(son[i], t);
        for(const auto &to : g[i]) {
            if(to == st[i][0] || to == son[i]) continue;
            dfs2(to, to);
        }
    }
    void build(int root = 1) {
        dfs1(root, 0);
        dfs2(root, root);
        // 预处理每条长链头节点的向上/向下路径
        for(int i = 1; i <= n; ++i) {
            if(top[i] != i) continue;
            for(int j = 1, now = i; j <= len[i] && now; ++j, now = st[now][0]) {
                up[i].push_back(now);
            }
            for(int j = 1, now = i; j <= len[i] && now; ++j, now = son[now]) {
                down[i].push_back(now);
            }
        }
    }
    int lca(int u, int v) {
        while(top[u] != top[v]) { 
            if(dep[top[u]] < dep[top[v]]){
                swap(u,v);
            }
            u = st[top[u]][0];
        }
        return (dep[u] < dep[v] ? u : v);
    }
    int dis(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }
    int kth(int x,int k){
        if(k == 0)return x;
        int t = lg[k];
        k -= (1 << t);
        x = st[x][t];
        int p = top[x];
        if(dep[x] - dep[p] >= k) {
            x = down[p][(dep[x] - dep[p]) - k];
        } else {
            x = up[p][k - (dep[x] - dep[p])];
        }
        return x;
    }
};

void solve(){
    int n,q;
    cin >> n;
    LLD tree(n);
    int root = 1;
    for(int i = 1;i <= n;++i){
        int f;cin >> f;
        if(f == 0)
            root = i;
        else
            tree.addEdge(i,f);
    }
    tree.build(root);
    
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