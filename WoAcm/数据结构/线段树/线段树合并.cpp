#include <bits/stdc++.h>
using ll = long long;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://www.luogu.com.cn/problem/P3605
template<typename Info, typename Tag>
struct SegmentTree {
    struct Node {
        int ls = 0, rs = 0;
        Info info = Info();
    };
    SegmentTree() = default;
    SegmentTree(int n,int m) : n(n) {
        tr.reserve(n * m);
        tr.push_back(Node());
    }
    int newNode() {
        tr.push_back(Node());
        return (int)tr.size() - 1;
    }
    void pushup(int id) {
        tr[id].info = tr[tr[id].ls].info + tr[tr[id].rs].info;
    }
    void update(int &id, int pos, const Tag &v) {
        update(id, 1, n, pos, v);
    }
    void update(int &id, int l, int r, int pos, const Tag &v) {
        if (!id) id = newNode();
        if (l == r) {
            tr[id].info.apply(v, l);
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) {
            update(tr[id].ls, l, mid, pos, v);
        } else {
            update(tr[id].rs, mid + 1, r, pos, v);
        }
        pushup(id);
    }
    Info rangeQuery(int id, int l, int r) {
        return rangeQuery(id, 1, n, l, r);
    }
    Info query(int id, int pos) {
        return rangeQuery(id, pos, pos);
    }
    Info rangeQuery(int id, int l, int r, int x, int y) {
        if (!id) return Info();
        if (x <= l && r <= y) {
            return tr[id].info;
        }
        int mid = (l + r) >> 1;
        Info res;
        if (x <= mid) {
            res = res + rangeQuery(tr[id].ls, l, mid, x, y);
        }
        if (y > mid) {
            res = res + rangeQuery(tr[id].rs, mid + 1, r, x, y);
        }
        return res;
    }
    int merge(int x, int y) {
        return merge(x, y, 1, n);
    }
    int merge(int x, int y, int l, int r) {
        if (!x || !y) return x | y;
        if (l == r) {
            tr[x].info.merge(tr[y].info,l);
            return x;
        }
        int mid = (l + r) >> 1;
        tr[x].ls = merge(tr[x].ls, tr[y].ls, l, mid);
        tr[x].rs = merge(tr[x].rs, tr[y].rs, mid + 1, r);
        pushup(x);
        return x;
    }
    int kth(int id, ll k) {
        if (!id || k <= 0 || tr[id].info.sum < k) return -1;
        return kth(id, 1, n, k);
    }
    int kth(int id, int l, int r, ll k) {
        if (!id || k <= 0 || tr[id].info.sum < k) return -1;
        if (l == r) return l;
        int mid = (l + r) >> 1;
        ll left = tr[tr[id].ls].info.sum;
        if (k <= left) return kth(tr[id].ls, l, mid, k);
        return kth(tr[id].rs, mid + 1, r, k - left);
    }
    int n;
    vector<Node> tr;
};
struct Tag {
    ll add = 0;
};
struct Info {
    ll mx = 0;
    int id = 0;
    void apply(const Tag &t, int pos) {
        mx += t.add;
        id = (mx > 0 ? pos : 0);
    }
    void merge(const Info &s,int pos){
        mx = mx + s.mx;
        if(mx > 0)id = pos;
    }
};
Info operator+(const Info &x, const Info &y) {
    Info s;
    if (x.mx > y.mx) {
        s.mx = x.mx;
        s.id = x.id;
    } else if (x.mx < y.mx) {
        s.mx = y.mx;
        s.id = y.id;
    } else {
        s.mx = x.mx;
        if (!x.id) s.id = y.id;
        else if (!y.id) s.id = x.id;
        else s.id = min(x.id, y.id);
    }
    return s;
}
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
    int n,m;cin >> n >> m;
    HLD tree(n);
    for(int i = 1;i <= n - 1;++i){
        int u,v;cin >> u >> v;
        tree.addedge(u,v);
    }
    tree.build(1);
    vector<int>ans(n + 1);
    vector<int>root(n + 1);
    SegmentTree<Info,Tag>tr(1e5,80);
    for(int i = 1;i <= m;++i){
        int u,v,w;cin >> u >> v >> w;
        tr.update(root[u],w,{1});
        tr.update(root[v],w,{1});
        int lca = tree.queryLCA(u,v);
        tr.update(root[lca],w,{-1});
        if(tree.fa[lca]){
            tr.update(root[tree.fa[lca]],w,{-1});
        }
    }
    auto &g = tree.g;
    auto dfs = [&](auto && dfs,int i,int fa)->void
    {
        for(auto to : g[i]){
            if(to == fa)continue;
            dfs(dfs,to,i);
            root[i] = tr.merge(root[i],root[to]);
        }
        auto [mx,id] = tr.rangeQuery(root[i],1,1e5);
        ans[i] = id;
    };
    dfs(dfs,1,0);
    for(int i = 1;i <= n;++i){
        cout << ans[i] << '\n';
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
