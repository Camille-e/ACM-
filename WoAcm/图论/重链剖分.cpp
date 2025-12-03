#include<bits/stdc++.h>
using ll = long long;
#define ull unsigned long long
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int maxn = 1e5 + 2;

template<typename Info, typename Tag>

struct SegmentTree {
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree() = default;
    SegmentTree(int n) : n(n), info(n << 2) , tag(n << 2){}
    constexpr void operator=(const SegmentTree<Info, Tag> &t) {
        n = t.n;
        info = t.info;
        tag = t.tag;
    }
    SegmentTree(const std::vector<Info> &init) : SegmentTree((int)init.size() - 1) {
        auto build = [&](auto self, int id, int l, int r) ->void {
            if(l == r) {
                info[id] = init[l];
                return;
            }
            int mid = (l + r) / 2;
            self(self, ls, l, mid);
            self(self, rs, mid + 1, r);
            pushup(id);
        };
        build(build, 1, 1, n);
    }
    void apply(int id, const Tag &dx) {
        info[id].apply(dx);
        tag[id].apply(dx);
    }
    void pushup(int id) {
        info[id] = info[ls] + info[rs];
    }
    void pushdown(int id) {
        apply(ls, tag[id]);
        apply(rs, tag[id]);
        tag[id] = Tag();
    }
    void rangeUpdate(int l, int r, const Tag &dx) {
        rangeUpdate(1, 1, n, l, r, dx);
    }
    void update(int t, const Tag &dx) {
        rangeUpdate(t, t, dx);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 1, n, l, r);
    }
    Info query(int t) {
        return rangeQuery(t, t);
    }
    void rangeUpdate(int id, int l, int r, int x, int y, const Tag &dx) {
        if(x <= l && r <= y) {
            apply(id, dx);
            return;
        }
        int mid = (l + r) / 2;
        pushdown(id);
        if(x <= mid) {
            rangeUpdate(ls, l, mid, x, y, dx);
        }
        if(y > mid) {
            rangeUpdate(rs, mid + 1, r, x, y, dx);
        }
        pushup(id);
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if(x <= l && r <= y) {
            return info[id];
        }
        int mid = (l + r) / 2;
        pushdown(id);
        Info res;
        if(x <= mid) {
            res = res + rangeQuery(ls, l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs, mid + 1, r, x, y);
        }
        return res;
    }
#undef ls
#undef rs
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
};

struct Tag {
    ll addtag = 0;
    void apply(const Tag &dx) {
        addtag += dx.addtag;
    }
};

struct Info {
    ll sum = 0;
    ll len = 0;
    void apply(const Tag &dx) {
        sum += dx.addtag * len;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}

struct HLD{
    HLD(const int & n,vector<Info> & a) : n(n), g(n + 1) {
        deep = fa = sz = son = top = dfn = seg = vector<int>(n + 1);
        b = a;
    }

    void build(int root = 1){
        dfs(root,0);
        dfs1(root,root);
        vector<Info>c(b.size());
        for(int i = 1;i <= n;++i){
            c[dfn[i]] = b[i];
        }
        tree = SegmentTree<Info, Tag>(c);
    }
    int n;
    vector<int>deep,fa,sz,son,top,dfn,seg;
    vector<vector<int>>g;
    SegmentTree<Info,Tag>tree;
    vector<Info>b;
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
    void add(int u,int v,ll val){
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            tree.rangeUpdate(dfn[top[u]],dfn[u],{val});
            u = fa[top[u]];
        }
        if(deep[u] < deep[v]){
            swap(u,v);
        }
        //边权转化为点权
        // if(u != v){
        //     tree.rangeUpdate(dfn[v] + 1,dfn[u],{val});
        // }
        tree.rangeUpdate(dfn[v],dfn[u],{val});
    }
    ll querySum(int u,int v){
        ll sum = 0;
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            sum = sum + tree.rangeQuery(dfn[top[u]],dfn[u]).sum;
            u = fa[top[u]];
        }
        if(deep[u] < deep[v]){
            swap(u,v);
        }
        sum = sum + tree.rangeQuery(dfn[v],dfn[u]).sum;
        return sum;
    }
    void addzitree(int u,ll val){
        tree.rangeUpdate(dfn[u],dfn[u] + sz[u] - 1,{val});
    }
    Info queryzitree(int u){
        return tree.rangeQuery(dfn[u],dfn[u] + sz[u] - 1);
    }
    ll queryLCA(int u,int v){
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            u = fa[top[u]];
        }
        return dfn[u] < dfn[v] ? u : v;
    }
    // ll querymx(int u,int v){
    //     ll res = -1e11;
    //     while(top[u] != top[v]){
    //         if(deep[top[u]] < deep[top[v]]){
    //             swap(u,v);
    //         }
    //         res = max(res,tree.rangeQuery(dfn[top[u]],dfn[u]).mx);
    //         u = fa[top[u]];
    //     }
    //     if(deep[u] < deep[v]){
    //         swap(u,v);
    //     }
    //     res = max(res,tree.rangeQuery(dfn[v],dfn[u]).mx);
    //     return res;
    // }
    // void chan(int u,int val){
    //     tree.update(dfn[u],{val,1});
    // }
};

void solve(){
    int n,m,r,p;
    cin >> n >> m >> r >> p;
    vector<Info>a(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> a[i].sum;
        a[i].len = 1;
    }
    HLD tree(n,a);
    for(int i = 1;i < n;++i){
        int u,v;
        cin >> u >> v;
        tree.addedge(u,v);
    }
    tree.build(r);
    for(int i = 0;i < m;++i){
        int op,u,v,w;
        cin >> op;
        if(op == 1){
            cin >> u >> v >> w;
            tree.add(u,v,w);
        }else if(op == 2){
            cin >> u >> v;
            cout << tree.querySum(u,v) << '\n';
        }else if(op == 3){
            cin >> u >> w;
            tree.addzitree(u,w);
        }else{
            cin >> u;
            cout << tree.queryzitree(u).sum << '\n';
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
}