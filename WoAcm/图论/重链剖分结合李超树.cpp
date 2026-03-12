#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using db = double;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
// https://www.luogu.com.cn/problem/P4069
using namespace std;
const int maxn = 50003;
const int mod = 1e9 + 1;
const db EPS = 1e-7;
const db INF = 1e9;
template<typename T>
struct line{
    T k,b;
};
template<class T, class S> bool equal(T x, S y) { //判断两个浮点数是否相等
    return -EPS < x - y && x - y < EPS;
}
vector<int>sg;
vector<ll>di;
//插入线段时要注意垂直的线段特判一下
template<typename T>
struct LiChao{
    #define ls q << 1
    #define rs q << 1 | 1
    int tot = 0,n = 0;
    vector<int>tag;
    vector<line<T>>fun;
    vector<T>val;
    LiChao(int _n) : n(_n){
        tag = vector<int>(_n << 2,0);
        val = vector<T>(_n << 2,123456789123456789);
        fun.push_back({0,123456789123456789});
        tot = 0;
    }
    //大于代表最大值
    inline bool check(int id1, int id2, int x){
        T y1 = Y(x, id1), y2 = Y(x, id2);
        if (!equal(y1, y2)) return y1 < y2;
        return id1 < id2;
    };
    inline bool check(T a,T b){
        return a < b;
    };
    //改
    inline T Y(T x,int id){
        return fun[id].k * di[sg[x]] + fun[id].b;
    }
    inline void insert_segment(int L,int R,T k,T b){
        fun.push_back({k,b});
        tot = fun.size() - 1;
        seg_update(1,1,n,L,R,tot);
    }
    //改
    inline void push_up(int q,int l,int r){
        T ans = min(Y(l,tag[q]),Y(r,tag[q]));
        if(l == r){
            val[q] = ans;
            return;
        }
        val[q] = min({ans,val[ls],val[rs]});
    }
    inline void seg_update(int q,int l,int r,int L,int R,int id){
        if(L <= l && r <= R){
            change(q,l,r,id);
            return;
        }
        int mid = (l + r) >> 1;
        if(L <= mid) seg_update(ls,l,mid,L,R,id);
        if(R > mid) seg_update(rs,mid + 1,r,L,R,id);
        push_up(q,l,r);
    }
    void change(int q, int l, int r, int id) {
        int m = (l + r) >> 1;
        int t = tag[q];
        if (check(id,t,m)) {
            swap(tag[q], id);
        }
        if (l == r) {
            val[q] = Y(l, tag[q]);
            return;
        }
        if (check(id,tag[q],l)) {
            change(ls, l, m, id);
        } else if (check(id,tag[q],r)) {
            change(rs, m + 1, r, id);
        }
        push_up(q,l,r);
    }
    inline pair<T,int> query(int q,int l,int r,int x){
        if(l == r) return {Y(l,tag[q]),tag[q]};
        int mid = (l + r) >> 1;
        T ans = Y(x,tag[q]);
        int id = tag[q];
        if(x <= mid) {
            auto [lans,lid] = query(ls,l,mid,x);
            if(check(lans,ans)){
                ans = lans;
                id = lid;
            }else if(equal(ans,lans)){
                id = min(id,lid);
            }
        }else{
            auto [rans,rid] = query(rs,mid + 1,r,x);
            if(check(rans,ans)){
                ans = rans;
                id = rid;
            }else if(equal(ans,rans)){
                id = min(id,rid);
            }
        }
        return {ans,id};
    }
    inline pair<T,int> query(int x){
        return query(1,1,n,x);
    }
    inline T Rangequery(int q,int l,int r,int L,int R){
        if(L <= l && r <= R) return val[q];
        int mid = (l + r) >> 1;
        T ans = 0;
        T a1 = Y(max(l,L),tag[q]);
        T a2 = Y(min(r,R),tag[q]);
        if(check(a1,a2)){
            ans = a1;
        }else{
            ans = a2;
        }
        if(L <= mid) {
            auto lans = Rangequery(ls,l,mid,L,R);
            if(check(lans,ans)){
                ans = lans;
            }
        }
        if(R > mid){
            auto rans = Rangequery(rs,mid + 1,r,L,R);
            if(check(rans,ans)){
                ans = rans;
            }
        }
        return ans;
    }
    inline T Rangequery(int L,int R){
        return Rangequery(1,1,n,L,R);
    }
};
map<pair<int,int>,int>mp;
template<typename T>
struct HLD{
    HLD(const int & n,LiChao<T> &_tree) : n(n), g(n + 1),tree(_tree) {
        deep = fa = sz = son = top = dfn = seg = vector<int>(n + 1);
        dis = vector<ll>(n + 1);
    }
    void build(int root = 1){
        dfs(root,0);
        dfs1(root,root);
    }
    int n;
    vector<int>deep,fa,sz,son,top,dfn,seg;
    vector<vector<int>>g;
    vector<ll>dis;
    LiChao<T> &tree;
    void addedge(const int & x ,const int & y){
        g[x].push_back(y);
        g[y].push_back(x);
    }
    void dfs(int i,int f){
        deep[i] = deep[f] + 1;
        dis[i] = dis[f] + mp[{min(i,f),max(i,f)}];
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
    void add(int u,int v,T k,T b){
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            tree.insert_segment(dfn[top[u]],dfn[u],k,b);
            u = fa[top[u]];
        }
        if(deep[u] < deep[v]){
            swap(u,v);
        }
        //边权转化为点权
        // if(u != v){
        //     tree.rangeUpdate(dfn[v] + 1,dfn[u],{val});
        // }
        // if(k == -4 && b == 5){
        //     cout << u << ' ' << v << '\n';
        //     cout << dfn[v] << ' ' << dfn[u] << '\n';
        // }
        tree.insert_segment(dfn[v],dfn[u],k,b);
    }
    int queryLCA(int u,int v){
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            u = fa[top[u]];
        }
        return dfn[u] < dfn[v] ? u : v;
    }
    int getdis(int x, int y) {
        return deep[x] + deep[y] - 2 * deep[queryLCA(x, y)];
    }
    ll querymi(int u,int v){
        ll res = 123456789123456789;
        while(top[u] != top[v]){
            if(deep[top[u]] < deep[top[v]]){
                swap(u,v);
            }
            res = min(res,tree.Rangequery(dfn[top[u]],dfn[u]));
            u = fa[top[u]];
        }
        if(deep[u] < deep[v]){
            swap(u,v);
        }
        res = min(res,tree.Rangequery(dfn[v],dfn[u]));
        return res;
    }
    // void chan(int u,int val){
    //     tree.update(dfn[u],{val,1});
    // }
};
void solve(){
    int n,m;cin >> n >> m;
    LiChao<ll>li(n);
    HLD<ll> tree(n,li);
    for(int i = 1;i < n;++i){
        int u,v,w;cin >> u >> v >> w;
        mp[{min(u,v),max(u,v)}] = w;
        tree.addedge(u,v);
    }
    tree.build();
    sg = tree.seg;
    di = tree.dis;
    for(int i = 1;i <= m;++i){
        int op;cin >> op;
        if(op == 1){
            int s,t;
            ll a,b;cin >> s >> t >> a >> b;
            int lca = tree.queryLCA(s,t);
            tree.add(s,lca,-a,a * tree.dis[s] + b);
            tree.add(lca,t,a,a * (tree.dis[s] - 2 * tree.dis[lca]) + b);
        }else{
            int s,t;cin >> s >> t;
            cout << tree.querymi(s,t) << '\n';
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