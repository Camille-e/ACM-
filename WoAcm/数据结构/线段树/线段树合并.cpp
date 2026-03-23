#include <bits/stdc++.h>
using ll = long long;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://www.luogu.com.cn/problem/P3605
template<typename Info>
struct SegmentTree {
    struct Node {
        int ls = 0, rs = 0;
        Info info = Info();
    };
    SegmentTree() = default;
    SegmentTree(int n) : n(n) {
        tr.reserve(1 << 20);
        tr.push_back(Node());
    }
    int newNode() {
        tr.push_back(Node());
        return (int)tr.size() - 1;
    }
    void pushup(int id) {
        tr[id].info = tr[tr[id].ls].info + tr[tr[id].rs].info;
    }
    void update(int &id, int pos, const Info &v) {
        update(id, 1, n, pos, v);
    }
    void update(int &id, int l, int r, int pos, const Info &v) {
        if (!id) id = newNode();
        if (l == r) {
            tr[id].info = tr[id].info + v;
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
            tr[x].info = tr[x].info + tr[y].info;
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
struct Info {
    ll sum = 0;
};
Info operator+(const Info &x, const Info &y) {
    return {x.sum + y.sum};
}

void solve(){
    int n;cin >> n;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i){
        cin >> a[i];
    }
    vector<int>b = a;
    sort(b.begin() + 1,b.end());
    b.erase(unique(b.begin() + 1,b.end()),b.end());
    for(int i = 1;i <= n;++i){
        a[i] = lower_bound(b.begin() + 1,b.end(),a[i]) - b.begin();
    }
    vector<vector<int>>g(n + 1);
    vector<int>f(n + 1);
    for(int i = 2;i <= n;++i){
        int x;cin >> x;
        g[x].push_back(i);
        f[i] = x;
    }
    int mxn = b.size();
    SegmentTree<Info>tree(mxn);
    vector<int>root(n + 1),ans(n + 1);
    auto dfs = [&](auto && dfs,int i,int fa)->void
    {
        for(auto to : g[i]){
            dfs(dfs,to,i);
            root[i] = tree.merge(root[i],root[to]);
        }
        ans[i] = tree.rangeQuery(root[i],a[i] + 1,mxn).sum;
        tree.update(root[i],a[i],{1});
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
