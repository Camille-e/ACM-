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
    //check满足条件时说明这个区间可能有答案
    template<class F>
    int findFirst(int x, int y, F check) {
        Info pre{};
        return findFirst(1, 1, n, x, y, pre, check);
    }
    template<class F>
    int findFirst(int id, int l, int r, int x, int y, Info &pre, F &check) {
        if (r < x || l > y) return -1;
        if (x <= l && r <= y) {
            Info cur = pre + info[id];
            if (!check(cur)) {
                pre = cur;
                return -1;
            }
            if (l == r) return l;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        int res = -1;
        if (x <= mid) res = findFirst(ls, l, mid, x, y, pre, check);
        if (res == -1 && y > mid) res = findFirst(rs, mid + 1, r, x, y, pre, check);
        return res;
    }
    template<class F>
    int findLast(int x, int y, F check) {
        Info suf{};
        return findLast(1, 1, n, x, y, suf, check);
    }
    template<class F>
    int findLast(int id, int l, int r, int x, int y, Info &suf, F &check) {
        if (r < x || l > y) return -1;
        if (x <= l && r <= y) {
            Info cur = info[id] + suf;
            if (!check(cur)) {
                suf = cur;
                return -1;
            }
            if (l == r) return l;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        int res = -1;
        if (y > mid) res = findLast(rs, mid + 1, r, x, y, suf, check);
        if (res == -1 && x <= mid) res = findLast(ls, l, mid, x, y, suf, check);
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
    int dis(int x, int y) {
        return deep[x] + deep[y] - 2 * deep[queryLCA(x, y)];
    }
    //线段树二分找第一个满足条件的id
    int queryid(int u,int v,int j){
        auto check = [&](Info &x){
            return !(x.sum >> j & 1);
        };
        vector<pair<int,int>> L,R;
        while(top[u] != top[v]){
            if(deep[top[u]] >= deep[top[v]]){
                L.push_back({dfn[top[u]],dfn[u]});
                u=fa[top[u]];
            }else{
                R.push_back({dfn[top[v]],dfn[v]});
                v=fa[top[v]];
            }
        }
        if(deep[u]>=deep[v]){
            L.push_back({dfn[v],dfn[u]});
        }else{
            R.push_back({dfn[u],dfn[v]});
        }
        for(auto [l,r]:L){
            int id=tree.findLast(l,r,check);
            if(id!=-1)return seg[id];
        }
        reverse(R.begin(),R.end());
        for(auto [l,r]:R){
            int id = tree.findFirst(l,r,check);
            if(id != -1)return seg[id];
        }
        return -1;
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