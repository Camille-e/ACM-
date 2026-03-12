#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
// https://www.luogu.com.cn/problem/P2495
const int mod = 1e9 + 7;
const int maxn = 2e5 + 2;
struct HLD{
    HLD(const int & n) : n(n), g(n + 1) {
        deep = fa = sz = son = top = dfn = seg = vector<int>(n + 1);
        e = vector<ll>(n + 1);
    }
    int n;
    vector<int> deep, fa, sz, son, top, dfn, seg;
    vector<ll> e;
    vector<vector<pair<int,int>>> g;
    int cntd = 0;
    void addedge(const int & x, const int & y,const int & w){
        g[x].push_back({y,w});
        g[y].push_back({x,w});
    }
    void build(int root = 1){
        dfs(root, 0);
        dfs1(root, root);
    }
    void dfs(int i, int f){
        deep[i] = deep[f] + 1;
        fa[i] = f;
        sz[i] = 1;
        for(const auto & [to,w] : g[i]){
            if(to == f) continue;
            e[to] = e[i] + w;
            dfs(to, i);
            sz[i] += sz[to];
            if(sz[to] > sz[son[i]]) son[i] = to;
        }
    }
    void dfs1(int i, int t){
        top[i] = t;
        dfn[i] = ++cntd;
        seg[cntd] = i;
        if(!son[i]) return;
        dfs1(son[i], t);
        for(const auto & [to,w] : g[i]){
            if(to != fa[i] && to != son[i]){
                dfs1(to, to);
            }
        }
    }
    int queryLCA(int u, int v){
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        return deep[u] < deep[v] ? u : v;
    }
    int dis(int x, int y) {
        return deep[x] + deep[y] - 2 * deep[queryLCA(x, y)];
    }
    ll edis(int x,int y){
        return e[x] + e[y] - 2 * e[queryLCA(x,y)];
    }
    bool isAncestor(int u, int v){
        return dfn[u] <= dfn[v] && dfn[v] <= dfn[u] + sz[u] - 1;
    }
    // tree: 虚树无向图，新编号 1..m
    // imp : imp[i] = 1 表示 i 是重要点
    // rid : rid[i] = 原树点编号
    tuple<vector<vector<int>>, vector<int>, vector<int>>
    buildVirtualTree(vector<int> key){
        if(key.empty()) return {{}, {}, {}};
        sort(key.begin(), key.end(), [&](int a, int b){
            return dfn[a] < dfn[b];
        });
        key.erase(unique(key.begin(), key.end()), key.end());
        vector<int> nodes = key;
        int m = (int)key.size();
        for(int i = 1; i < m; ++i){
            nodes.push_back(queryLCA(key[i - 1], key[i]));
        }
        sort(nodes.begin(), nodes.end(), [&](int a, int b){
            return dfn[a] < dfn[b];
        });
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        int tot = (int)nodes.size();
        vector<int> rid(tot + 1), imp(tot + 1, 0);
        for(int i = 0; i < tot; ++i){
            rid[i + 1] = nodes[i];
        }
        for(int i = 0, j = 0; i < tot && j < m; ++i){
            if(nodes[i] == key[j]){
                imp[i + 1] = 1;
                ++j;
            }
        }
        vector<vector<int>> tree(tot + 1);
        vector<int> st;
        st.reserve(tot);
        st.push_back(1); // 存新编号，不存原点
        for(int i = 2; i <= tot; ++i){
            int u = rid[i];
            while(!st.empty() && !isAncestor(rid[st.back()], u)){
                st.pop_back();
            }
            int p = st.back();
            tree[p].push_back(i);
            tree[i].push_back(p);
            st.push_back(i);
        }
        return {tree, imp, rid};
    }
};
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
auto rnd = [](ll l, ll r) { return (l <= r ? uniform_int_distribution<ll>(l, r)(rng) : 0); };
void solve(){
    int n;cin >> n;
    HLD tree(n);
    map<pair<int,int>,int>hash;
    for(int i = 1;i < n;++i){
        int u,v,w;cin >> u >> v >> w;
        tree.addedge(u,v,w);
        hash[{min(u,v),max(u,v)}] = w;
    }
    tree.build();
    int p = __lg(n + 1);
    auto &deep = tree.deep;
    auto &g = tree.g;
    vector<vector<ll>>stmi(n + 1,vector<ll>(p + 2,1e18)),st(n + 1,vector<ll>(p + 2));
    auto dfs = [&](auto &&dfs,int i,int fa)->void
    {
        if(hash.count({min(i,fa),max(i,fa)}))
        stmi[i][0] = hash[{min(i,fa),max(i,fa)}];
        st[i][0] = fa;
        for(int j = 1;(1 << j) <= deep[i];++j){
            stmi[i][j] = min(stmi[i][j - 1],stmi[st[i][j - 1]][j - 1]);
            st[i][j] = st[st[i][j - 1]][j - 1];
        }
        for(int j = 0;j < tree.g[i].size();++j){
            if(g[i][j].first != fa){
                dfs(dfs,g[i][j].first,i);
            }
        }
    };
    dfs(dfs,1,0);
    // for(int i = 1;i <= n;++i){
    //     for(int j = 0;j <= p;++j){
    //         cout << stmi[i][j] << " \n"[j == p];
    //     }
    // }
    auto qiumi = [&](int u,int v){
        if(u == v)return 0ll;
        auto lca = tree.queryLCA(u,v);
        int k = 32 - __builtin_clz(deep[u]);
        ll mi1 = 1e18,mi2 = 1e18;
        for(int j = k - 1;j >= 0;--j){
            if(deep[st[u][j]] >= deep[lca]){
                mi1 = min(mi1,stmi[u][j]);
                u = st[u][j];
            }
        }
        k = 32 - __builtin_clz(deep[v]);
        for(int j = k - 1;j >= 0;--j){
            if(deep[st[v][j]] >= deep[lca]){
                mi2 = min(mi2,stmi[v][j]);
                v = st[v][j];
            }
        }
        return min(mi1,mi2);
    };
    // for(int i = 1;i <= n;++i){
    //     for(int j = 1;j <= n;++j){
    //         cout << qiumi(i,j) << " \n"[j == n];
    //     }
    // }
    int q;cin >> q;
    for(int i = 1;i <= q;++i){
        int len;cin >> len;
        vector<int>tmp(len);
        for(int j = 1;j <= len;++j){
            cin >> tmp[j - 1];
        }
        tmp.push_back(1);
        auto [g,ok,rid] = tree.buildVirtualTree(tmp);
        ok[1] = 0;
        int kn = g.size() - 1;
        vector<ll>dp(kn + 1);
        auto dfs = [&](auto && dfs,int i,int fa)->void
        {
            if(ok[i])dp[i] = 1e18;
            for(auto to : g[i]){
                if(to == fa)continue;
                dfs(dfs,to,i);
                auto id1 = rid[i],id2 = rid[to];
                if(ok[i] == 0)
                dp[i] = min(dp[to],qiumi(id1,id2)) + dp[i];

            }
        };
        dfs(dfs,1,0);
        cout << dp[1] << '\n';
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