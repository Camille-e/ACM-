#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://codeforces.com/problemset/problem/896/C
template<typename T>
struct ODT {
    struct node {
        int l, r;
        mutable T v;
        node(int _l, int _r = -1, T _v = T()) : l(_l), r(_r), v(_v) {}
        bool operator<(const node& o) const { return l < o.l; }
    };
    // 记得设置哨兵节点
    set<node> s;
    using IT = set<node>::iterator;
    IT split(int pos) {
        IT it = s.lower_bound(node(pos));
        if (it != s.end() && it->l == pos) return it;
        --it;
        if (it->r < pos) return next(it);
        int L = it->l, R = it->r;
        T V = it->v;
        s.erase(it);
        s.insert(node(L, pos - 1, V));
        return s.insert(node(pos, R, V)).first;
    }
    void assign(int l, int r, T x) {
        IT itr = split(r + 1), itl = split(l);
        s.erase(itl, itr);
        s.insert(node(l, r, x));
    }
    void add(int l, int r, T x) {
        IT itr = split(r + 1), itl = split(l);
        for (IT it = itl; it != itr; ++it) it->v += x;
    }
    T kth(int l, int r, int k) {
        vector<pair<T, int>> seg;
        IT itr = split(r + 1), itl = split(l);
        for (IT it = itl; it != itr; ++it)
            seg.push_back({it->v, it->r - it->l + 1});
        sort(seg.begin(), seg.end());
        for (auto &[val, len] : seg) {
            k -= len;
            if (k <= 0) return val;
        }
        //注意修改出错的返回值
        return T();
    }
    T ksm(T a, ll b, T mod) {
        a %= mod;
        T res = 1 % mod;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
    T powersum(int l, int r, T x, T mod) {
        IT itr = split(r + 1), itl = split(l);
        T ans = 0;
        for (IT it = itl; it != itr; ++it) {
            ans = (ans + ksm(it->v, x, mod) * (it->r - it->l + 1)) % mod;
        }
        return ans;
    }
};

void solve(){
    ll n,m,seed,vmax;cin >> n >> m >> seed >> vmax;
    auto rnd = [&]() {
        ll ret = seed;
        seed = (seed * 7 + 13) % 1000000007;
        return ret;
    };
    ODT<ll> tree;
    for(int i = 1;i <= n;++i){
        ll x = rnd() % vmax + 1;
        tree.s.insert(ODT<ll>::node(i,i,x));
    }
    tree.s.insert(ODT<ll>::node(n + 1,n + 1,0));
    for(int i = 1;i <= m;++i){
        ll op = (rnd() % 4) + 1;
        ll l = (rnd() % n) + 1;
        ll r = (rnd() % n) + 1;
        if(l > r)swap(l,r);
        if (op == 1) {
            ll x = rnd() % vmax + 1;
            tree.add(l, r, x);
        } else if (op == 2) {
            ll x = rnd() % vmax + 1;
            tree.assign(l, r, x);
        } else if (op == 3) {
            ll k = rnd() % (r - l + 1) + 1;
            cout << tree.kth(l, r, k) << '\n';
        } else {
            ll x = rnd() % vmax + 1;
            ll y = rnd() % vmax + 1;
            cout << tree.powersum(l, r, x, y) << '\n';
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