#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://loj.ac/p/121
struct DSU {
    vector<int> siz,edges;
    vector<int> f;
    vector<array<int, 2>> his;
    
    DSU(int n) : siz(n + 1, 1), edges(n + 1), f(n + 1) {
        iota(f.begin(), f.end(), 0);
    }
    
    int find(int x) {
        while (f[x] != x) {
            x = f[x];
        }
        return x;
    }
    
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        his.push_back({x, y});
        siz[x] += siz[y];
        edges[x] += edges[y] + 1;
        f[y] = x;
        return true;
    }
    
    bool same(int a,int b){
        return find(a) == find(b);
    }

    int time() {
        return his.size();
    }
    
    void revert(int tm) {
        while (his.size() > tm) {
            auto [x, y] = his.back();
            his.pop_back();
            f[y] = y;
            siz[x] -= siz[y];
            edges[x] -= edges[y] + 1;
        }
    }
};
template<typename Info>
struct SegmentTree {
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree() = default;
    SegmentTree(int n) : n(n), info((n + 1) << 2) {}
    void rangeUpdate(int l, int r, pair<int,int> dx) {
        rangeUpdate(1, 1, n, l, r, dx);
    }
    void rangeUpdate(int id, int l, int r, int x, int y,pair<int,int> a) {
        if(x <= l && r <= y) {
            info[id].edges.push_back(a);
            return;
        }
        int mid = (l + r) / 2;
        if(x <= mid) {
            rangeUpdate(ls, l, mid, x, y, a);
        }
        if(y > mid) {
            rangeUpdate(rs, mid + 1, r, x, y, a);
        }
    }
#undef ls
#undef rs
    const int n;
    vector<Info> info;
};

constexpr ll INF = 1E18;

struct Info {
    vector<pair<int,int>>edges;
    //记得输入长度
};
void solve(){
    int n,m;cin >> n >> m;
    DSU dsu(n);
    vector<vector<int>>last(n + 1,vector<int>(n + 1));
    SegmentTree<Info> tree(m);
    vector<array<int,3>>ops(m + 1);
    for(int i = 1;i <= m;++i){
        int op,x,y;cin >> op >> x >> y;
        ops[i] = {op,x,y};
        if(x > y)swap(x,y);
        if(op == 0){
            last[x][y] = i;
        }else if(op == 1){
            tree.rangeUpdate(last[x][y],i - 1,pair<int,int>{x,y});
            last[x][y] = 0;
        }
    }
    for(int i = 1;i <= n;++i){
        for(int j = i;j <= n;++j){
            if(last[i][j] != 0){
                tree.rangeUpdate(last[i][j],m,pair<int,int>{i,j});
            }
        }
    }
    vector<int>ans;
    auto &info = tree.info;
    auto dfs = [&](auto && dfs,int id,int l,int r)->void
    {
        int t = dsu.his.size();
        for(auto [x,y] : info[id].edges){
            dsu.merge(x,y);
        }
        if(l == r){
            auto [op,x,y] = ops[l];
            if(op == 2){
                if(dsu.same(x,y)){
                    ans.push_back(1);
                }else{
                    ans.push_back(0);
                }
            }
        }else{
            int mid = (l + r) >> 1;
            if(mid >= l)
            dfs(dfs,(id << 1),l,mid);
            if(mid < r)
            dfs(dfs,(id << 1 | 1),mid + 1,r);
        }
        dsu.revert(t);
    };
    dfs(dfs,1,1,m);
    for(int x : ans){
        if(x)cout << "Y\n";
        else cout << "N\n";
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