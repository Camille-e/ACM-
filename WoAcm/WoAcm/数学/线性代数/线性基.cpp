#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://ac.nowcoder.com/acm/contest/120563/I
template <class T>
struct LB {
    using ull = unsigned long long;
    static constexpr int BASE = sizeof(T) * 8 - 1;
    //简单基,高斯消元基
    vector<T> basis, p;
    int cnt, zero;
    //每个基向量由哪些原始向量得到
    vector<ull> mask;
    //基的原位置
    vector<int> rep;
 
    LB() {
        basis.assign(BASE + 1, 0);
        p.assign(BASE + 1, 0);
        mask.assign(BASE + 1, 0);
        cnt = zero = 0;
    }
    bool insert(T val, int idx) {
        ull cur = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if (val & (1ll << i)) {
                if (!basis[i]) {
                    basis[i] = val;
                    mask[i] = cur | (1ull << rep.size());
                    rep.push_back(idx);
                    return true;
                }
                val ^= basis[i];
                cur ^= mask[i];
            }
        }
        zero = 1;
        return false;
    }
    //检查能否异或出val
    pair<bool, ull> check(T val) {
        ull res = 0;
        for (int i = BASE - 1; i >= 0; --i) {
            if (val & (1ll << i)) {
                if (!basis[i])
                    return {false, 0ull};
                val ^= basis[i];
                res ^= mask[i];
            }
        }
        return {true, res};
    }
    ll ask_max() {
        ll res = 0;
        for (int i = BASE - 1; i >= 0; i--) {
            if ((res ^ basis[i]) > res)
                res ^= basis[i];
        }
        return res;
    }
    ll ask_min() {
        if (zero)
            return 0;
        for (int i = 0; i <= BASE - 1; i++) {
            if (basis[i])
                return basis[i];
        }
    }
    //高斯消元
    void rebuild() {
        for (int i = BASE - 1; i >= 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                if (basis[i] & (1ll << j))
                    basis[i] ^= basis[j];
            }
        }
        for (int i = 0; i <= BASE - 1; i++) {
            if (basis[i])
                p[cnt++] = basis[i];
        }
    }
    //第k大(第k小异或值)
    ll kthquery(ll k) {
        if (zero)
            k--;
        if (!k)
            return 0;
        ll res = 0;
        if (k >= (1ll << cnt))
            return -1;
        for (int i = BASE - 1; i >= 0; i--) {
            if (k & (1LL << i))
                res ^= p[i];
        }
        return res;
    }
    //合并两个线性基
    void Merge(const LB &b) {
        for (int i = BASE - 1; i >= 0; i--) {
            if (b.basis[i]) {
                insert(b.basis[i]);
            }
        }
    }
    //路径还原对应索引
    vector<int> choose(ull mask) {
        vector<int> res;
        for (int i = 0; i < rep.size(); ++i) {
            if (mask & (1ull << i)) {
                res.push_back(rep[i]);
            }
        }
        return res;
    }
};
void solve() {
    int n;cin >> n;
    vector<int>a(n + 1),b(n + 1);
    int t = 0;
    for(int i = 1;i <= n;++i){
        cin >> a[i];
        t ^= a[i];
    }
    for(int i = 1;i <= n;++i)cin >> b[i];
    LB<int>lb;
    for(int i = 1;i <= n;++i){
        lb.insert(a[i] ^ b[i],i);
    }
    auto [ok,mask] = lb.check(t);
    if(!ok){
        cout << -1 << '\n';
        return;
    }
    vector<int>ans(n + 1);
    for(int x : lb.choose(mask)){
        ans[x] = 1;
    }
    for(int i = 1;i <= n;++i){
        if(ans[i])cout << b[i] << " \n"[i == n];
        else cout << a[i] << " \n"[i == n];
    }
}
signed main() {
    IOS;
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}