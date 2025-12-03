#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//O(1.5 * n * sqrt(m))
//一般块长设置为ceil(n / sqrt(m)),过不了设置为(n / sqrt(2 * m))
struct HLD {
    HLD(const int &_n) : n(_n), g(_n + 1) {
        fa = dep = son = sz = top = dfn = out = seg = vector<int>(_n + 1);
        st = ed = b = vector<int>(2 * _n + 2);
    }

    void addEdge(const int &x, const int &y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    int num = 0;
    void dfs1(int i,int f){
        dep[i] = dep[f] + 1;
        sz[i] = 1;
        fa[i] = f;
        st[i] = ++num;
        b[num] = i;
        for(const int & to : g[i]){
            if(to != f){
                dfs1(to,i);
                sz[i] += sz[to];
                if(sz[to] > sz[son[i]]){
                    son[i] = to;
                }
            }
        }
        ed[i] = ++num;
        b[num] = i;
    };
    int cntd = 0;
    void dfs2(int i,int t){
        top[i] = t;
        dfn[i] = ++cntd;
        seg[cntd] = i;
        if(son[i] == 0)return;
        dfs2(son[i],t);
        for(const int & to : g[i]){
            if(to != son[i] && to != fa[i]){
                dfs2(to,to);
            }
        }
    };
    void build(int root = 1) {
        int dfsn = 1;
        dfs1(root, dfsn);
        dfs2(root, root);
    }

    bool isAncestor(int x, int y) {
        return dfn[x] <= dfn[y] && out[x] >= out[y];
    }

    int lca(int x, int y) {
        while(top[x] != top[y]) { 
            if(dep[top[x]] < dep[top[y]]) {
                swap(x, y);
            }
            x = fa[top[x]];
        }
        return (dep[x] < dep[y] ? x : y);
    }

    int dis(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }

    int kth(int id, int k) {
        if(k > dep[id]) return 0;
        while(dep[id] - dep[top[id]] + 1 <= k) {
            k -= (dep[id] - dep[top[id]] + 1);
            id = fa[top[id]];
        }
        return seg[dfn[id] - k];
    }

    vector<vector<int>> g;
    vector<int> fa, dep, son, sz, top, dfn, out, seg, st, ed, b;
    int n;
};
void solve(){
    int n, m, k;
    cin >> n >> k >> m;
    vector<ll>v(k + 1),w(n + 1);
    for(int i = 1;i <= k;++i)cin >> v[i];
    for(int i = 1;i <= n;++i)cin >> w[i];
    HLD tree(n);
    for(int i = 1;i < n;++i){
        int u,v;cin >> u >> v;
        tree.addEdge(u,v);
    }
    tree.build();
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> a[i];
    }
    ll kind = 0;
    //看情况改数据范围;
    vector<int>cntnode(n + 1),cnt(k + 1);
    //l,r,添加lca结点(0为不添加),id
    int unit = ceil(n / sqrt(m));
    vector<array<int,5>>q(m + 1);
    vector<array<int,2>>chan(m + 1);
    int cntq = 0,cntchan = 0;
    for(int i = 0;i < m;++i){
        int op,u,v;
        cin >> op >> u >> v;
        if(op == 1){
            int id = ++cntq;
            int ok = 0;
            if(tree.st[u] > tree.st[v]){
                swap(u,v);
            }
            int lca = tree.lca(u,v);
            if(u == lca){
                u = tree.st[u];
                v = tree.st[v];
                ok = 0;
            }else{
                u = tree.ed[u];
                v = tree.st[v];
                ok = lca;
            }
            q[cntq] = {u,v,cntchan,ok,id};
        }else{
            ++cntchan;
            chan[cntchan] = {u,v};
        }
    }
    sort(q.begin() + 1,q.begin() + 1 + cntq,[&](array<int,5>&a,array<int,5>&b){
        if(a[0] / unit != b[0] / unit){
            return a[0] < b[0];
        }else if(a[1] / unit != b[1] / unit){
            return a[1] < b[1];
        }
        return a[2] < b[2];
    });

    //看情况改这个
    auto update = [&](int node,int num){
        if(num == -1){
            if(cntnode[node]-- == 2){
                cnt[a[node]]++;
                kind += v[a[node]] * w[cnt[a[node]]];
            }else{
                kind -= v[a[node]] * w[cnt[a[node]]];
                cnt[a[node]]--;
            }
        }else{
            if(cntnode[node]++ == 0){
                cnt[a[node]]++;
                kind += v[a[node]] * w[cnt[a[node]]];
            }else{
                kind -= v[a[node]] * w[cnt[a[node]]];
                cnt[a[node]]--;
            }
        }
    };
    //修改时
    auto updateval = [&](int val,int num){
        if(num == 1){
            cnt[val]++;
            kind += v[val] * w[cnt[val]];
        }else{
            kind -= v[val] * w[cnt[val]];
            cnt[val]--;
        }
    };
    int winl = 1,winr = 0,curt = 0;
    vector<ll>ans(cntq + 1);
    for(int i = 1;i <= cntq;++i){
        auto [l,r,time,lca,id] = q[i];
        while(winl > l)update(tree.b[--winl],1);
        while(winr < r)update(tree.b[++winr],1);
        while(winl < l)update(tree.b[winl++],-1);
        while(winr > r)update(tree.b[winr--],-1);
        if(lca > 0)update(lca,1);
        while(curt < time){
            curt++;
            //注意这里传引用,不要随意修改update的传参
            auto &[pos,val] = chan[curt];
            if(cntnode[pos] == 1){
                updateval(val,1);
                updateval(a[pos],- 1);
            }
            swap(val,a[pos]);
        }
        while(curt > time){
            //注意这里传引用,不要随意修改update的传参
            auto &[pos,val] = chan[curt];
            if(cntnode[pos] == 1){
                updateval(val,1);
                updateval(a[pos],-1);
            }
            curt--;
            swap(val,a[pos]);
        }
        ans[id] = kind;
        if(lca > 0)update(lca,-1);
    }
    for(int i = 1;i <= cntq;++i){
        cout << ans[i] << '\n';
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