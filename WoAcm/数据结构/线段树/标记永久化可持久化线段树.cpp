#include<bits/stdc++.h>
using ll = long long;
using namespace std;
// https://www.spoj.com/problems/TTM/
template<typename Info, typename Tag>
struct PersistentTree {
    struct Node {
        int l = 0, r = 0;
        Info info;
        Tag tag;
    };
#define ls(x) (node[x].l)
#define rs(x) (node[x].r)
    PersistentTree(int n) : n(n) {}
    PersistentTree(const vector<Info> &init) : PersistentTree((int)init.size() - 1) {
        node.reserve(n << 4);
        auto build = [&](auto self, int l, int r) ->int {
            node.push_back(Node());
            int id = node.size() - 1;
            if(l == r) {
                node[id].info = init[l];
            } else {
                int mid = (l + r) / 2; 
                ls(id) = self(self, l, mid);  
                rs(id) = self(self, mid + 1, r);  
                node[id].info = node[ls(id)].info + node[rs(id)].info;
            }
            return id;
        };
        root.push_back(build(build, 1, n));
    };
    int update(int version, int t, const Tag &dx) {
        return rangeUpdate(version, t, t, dx);
    }
    Info query(int version, int t) {
        return rangeQuery(version, t, t);
    }
    int rangeUpdate(int version, int l, int r, const Tag &dx) {
        root.push_back(rangeUpdate(root[version], 1, n, l, r, dx));
        return root.size() - 1;
    }
    Info rangeQuery(int version, int l, int r) {
        return rangeQuery(root[version], 1, n, l, r);
    }
    int rangeUpdate(int lst, int l, int r, const int &x, const int &y, const Tag &dx) {
        node.push_back(node[lst]);
        int id = node.size() - 1;
        node[id].info.apply(min(r, y) - max(l, x) + 1, dx);
        if(x <= l && r <= y) {
            node[id].tag.apply(dx);
        } else {
            int mid = (l + r) / 2;
            if(x <= mid) {
                ls(id) = rangeUpdate(ls(lst), l, mid, x, y, dx);
            }
            if(y > mid) {
                rs(id) = rangeUpdate(rs(lst), mid + 1, r, x, y, dx);
            }
        }
        return id;
    }
    Info rangeQuery(int id, int l, int r, const int &x, const int &y) {
        if(x <= l && r <= y) {
            return node[id].info;
        }
        int mid = (l + r) / 2;
        Info res;
        if(x <= mid) {
            res = res + rangeQuery(ls(id), l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs(id), mid + 1, r, x, y);
        }
        res.apply(min(r, y) - max(l, x) + 1, node[id].tag);
        return res;
    }
#undef ls
#undef rs
    const int n;
    vector<Node> node;
    vector<int> root;
};

struct Tag {
    Tag(int dx = 0) : add(dx) {}
    int add = 0;
    void apply(const Tag &dx) {
        add += dx.add;
    }
};

struct Info {
    ll sum = 0;
    void apply(int len, const Tag &dx) {
        sum += 1LL * len * dx.add;
    }
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    while(cin >> n >> q){
        vector<Info> a(n + 1);
        for(int i = 1; i <= n; ++i) {
            cin >> a[i].sum;
        }
        PersistentTree<Info, Tag> tree(a);
        vector<int> version(q + 1);
        version[0] = tree.root[0];
        int cur = 0;
        char op;int l,r,d;
        for(int i = 1; i <= q; ++i) {
            cin >> op;
            if(op == 'C'){
                cin >> l >> r >> d;
                version[cur + 1] = tree.rangeUpdate(version[cur],l,r,Tag{d});
                cur++;
            }else if(op == 'Q'){
                cin >> l >> r;
                cout << tree.rangeQuery(version[cur],l,r).sum << '\n';
            }else if(op == 'H'){
                cin >> l >> r >> d;
                cout << tree.rangeQuery(version[d],l,r).sum << '\n';
            }else{
                cin >> d;
                cur = d;
            }
        }
    }
    return 0;
}