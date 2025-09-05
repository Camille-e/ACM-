#include <bits/stdc++.h>
using ll = long long;
using namespace std;
// https://www.luogu.com.cn/problem/P3372
template<typename Info, typename Tag>
struct SegmentTree {
#define ls (id<<1)
#define rs (id<<1|1)
    SegmentTree() = default;
    SegmentTree(int n) : n(n), info(n << 2) , tag(n << 2){}
    //传(n + 1)数组
    SegmentTree(const vector<Info> &init) : SegmentTree((int)init.size() - 1) {
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
    const int n;
    vector<Info> info;
    vector<Tag> tag;
};

constexpr ll INF = 1E18;

struct Tag {
    ll add = 0;
    void apply(const Tag &dx) {
        add += dx.add;
    }
};

struct Info {
    ll mn = INF;
    ll mx = -INF;
    ll sum = 0;
    //记得输入长度
    ll len = 0;
    void apply(const Tag &dx) {
        mn += dx.add;
        mx += dx.add;
        sum += len * dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.mn = min(x.mn, y.mn);
    res.mx = max(x.mx, y.mx);
    res.sum = x.sum + y.sum;
    res.len = x.len + y.len;
    return res;
}

void solve(){
    int n,m;
    cin >> n >> m;
    vector<Info>a(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> a[i].sum;
        a[i].len = 1;
    }
    SegmentTree<Info,Tag> tree(a);
    for(int i = 0;i < m;++i){
        int op,x,y;ll k;
        cin >> op >> x >> y;
        if(op == 1){
            cin >> k;
            tree.rangeUpdate(x,y,{k});
        }else{
            cout << tree.rangeQuery(x,y).sum << '\n';
        }
    }
}
signed main() {
    ios::sync_with_stdio(0),cin.tie(0);
    int _ = 1;
    //cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}