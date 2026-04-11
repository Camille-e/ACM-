#include <bits/stdc++.h>
using ll = long long;
using namespace std;
//https://www.luogu.com.cn/problem/P3834
template<typename Info, typename Tag>
struct PersistentTree {
#define ls(x) lson[x]
#define rs(x) rson[x]
    PersistentTree(int n, int q = 0) : n(n) {
        int lg = 1;
        while((1 << lg) <= max(1, n)) lg++;
        int need = 1 + max(1, q) * (lg + 1);
        lson.reserve(need);
        rson.reserve(need);
        info.reserve(need);
        root.reserve(q + 1);
        lson.push_back(0);
        rson.push_back(0);
        info.push_back(Info());

        root.push_back(0);
    }
    PersistentTree(const vector<Info> &init) : n((int)init.size() - 1) {
        lson.reserve((n << 2) + 5);
        rson.reserve((n << 2) + 5);
        info.reserve((n << 2) + 5);
        lson.push_back(0);
        rson.push_back(0);
        info.push_back(Info());
        auto build = [&](auto self, int l, int r) -> int {
            int id = newNode();
            if(l == r) {
                info[id] = init[l];
            } else {
                int mid = (l + r) >> 1;
                ls(id) = self(self, l, mid);
                rs(id) = self(self, mid + 1, r);
                pull(id);
            }
            return id;
        };
        root.push_back(build(build, 1, n));
    }
    int update(int version, int pos, const Info &val) {
        root.push_back(update(root[version], 1, n, pos, val));
        return (int)root.size() - 1;
    }
    int update(int version, int pos, const Tag &dx) {
        root.push_back(update(root[version], 1, n, pos, dx));
        return (int)root.size() - 1;
    }
    Info query(int version, int pos) {
        return rangeQuery(version, pos, pos);
    }
    Info rangeQuery(int version, int l, int r) {
        return rangeQuery(root[version], 1, n, l, r);
    }
    int update(int lst, int l, int r, const int &pos, const Info &val) {
        int id = clone(lst);
        if(l == r) {
            info[id] = val;
        } else {
            int mid = (l + r) >> 1;
            if(pos <= mid) {
                ls(id) = update(ls(id), l, mid, pos, val);
            } else {
                rs(id) = update(rs(id), mid + 1, r, pos, val);
            }
            pull(id);
        }
        return id;
    }
    int update(int lst, int l, int r, const int &pos, const Tag &dx) {
        int id = clone(lst);
        if(l == r) {
            info[id].apply(dx);
        } else {
            int mid = (l + r) >> 1;
            if(pos <= mid) {
                ls(id) = update(ls(id), l, mid, pos, dx);
            } else {
                rs(id) = update(rs(id), mid + 1, r, pos, dx);
            }
            pull(id);
        }
        return id;
    }
    Info rangeQuery(int id, int l, int r, const int &x, const int &y) {
        if(!id) return Info();
        if(x <= l && r <= y) {
            return info[id];
        }
        int mid = (l + r) >> 1;
        Info res;
        if(x <= mid) {
            res = res + rangeQuery(ls(id), l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs(id), mid + 1, r, x, y);
        }
        return res;
    }
    int kth(int versionl, int versionr, int k) {
        return kth(root[versionl], root[versionr], 1, n, k);
    }
    int treekth(int versionu, int versionv, int versionlca, int versionflca, int k) {
        return treekth(root[versionu], root[versionv], root[versionlca], root[versionflca], 1, n, k);
    }
    int kth(int vl, int vr, int l, int r, int k) { // 静态区间第 k 小，不支持修改
        if(l == r) return l;
        int mid = (l + r) >> 1;
        int dx = info[ls(vr)].sum - info[ls(vl)].sum;
        if(dx >= k) {
            return kth(ls(vl), ls(vr), l, mid, k);
        } else {
            return kth(rs(vl), rs(vr), mid + 1, r, k - dx);
        }
    }
    int treekth(int vu, int vv, int vlca, int vflca, int l, int r, int k) { // 静态路径第 k 小，不支持修改
        if(l == r) return l;
        int mid = (l + r) >> 1;
        int dx = info[ls(vu)].sum + info[ls(vv)].sum - info[ls(vlca)].sum - info[ls(vflca)].sum;
        if(dx >= k) {
            return treekth(ls(vu), ls(vv), ls(vlca), ls(vflca), l, mid, k);
        } else {
            return treekth(rs(vu), rs(vv), rs(vlca), rs(vflca), mid + 1, r, k - dx);
        }
    }
#undef ls
#undef rs

    const int n;
    vector<int> lson, rson;
    vector<Info> info;
    vector<int> root;

    int newNode() {
        lson.push_back(0);
        rson.push_back(0);
        info.push_back(Info());
        return (int)info.size() - 1;
    }

    int clone(int x) {
        int id = newNode();
        lson[id] = lson[x];
        rson[id] = rson[x];
        info[id] = info[x];
        return id;
    }

    void pull(int id) {
        info[id] = info[ls(id)] + info[rs(id)];
    }
};

struct Tag {
    Tag(int dx = 0) : add(dx) {}
    int add = 0;
};

struct Info {
    int sum = 0;
    void apply(const Tag &dx) {
        sum += dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

void slove(){
    int n, q;
    cin >> n >> q;
    vector<int> v(n + 1), tmp(n + 1);
    for(int i = 1; i <= n; ++i) {
        cin >> v[i];
        tmp[i] = v[i];
    }
    sort(tmp.begin() + 1, tmp.end());
    tmp.erase(unique(tmp.begin() + 1, tmp.end()), tmp.end());
    int m = tmp.size() - 1;
    PersistentTree<Info, Tag> tr(vector<Info>(m + 1));
    vector<int> version(n + 1);
    version[0] = tr.root.size() - 1;
    for(int i = 1; i <= n; ++i) {
        int pos = lower_bound(tmp.begin() + 1, tmp.end(), v[i]) - tmp.begin();
        version[i] = tr.update(version[i - 1], pos, Tag{1});
    }
    for(int i = 1; i <= q; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        int pos = tr.kth(version[l - 1], version[r], k);
        cout << tmp[pos] << '\n';
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _ = 1;
    // cin >> _;
    while(_--){
        slove();
    }
    return 0;
}