#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 998244353;
const int maxn = 2e5 + 2;
//https://acm.hdu.edu.cn/contest/problem?cid=1200&pid=1003
template <class T, class F>
struct SparseTable {
    int n, K;
    vector<int> lg;
    vector<vector<T>> st;
    F func;
    SparseTable() {}
    SparseTable(const vector<T>& a, F f) : func(f) {
        build(a);
    }
    void build(const vector<T>& a) {
        n = (int)a.size() - 1;
        K = __lg(n) + 1;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
        st.assign(K, vector<T>(n + 1));
        for (int i = 1; i <= n; ++i) st[0][i] = a[i];
        for (int k = 1; k < K; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                st[k][i] = func(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return func(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
void solve(){
    int n,q;cin >> n >> q;
    vector<vector<int>>g(n + 1,vector<int>(n + 1));
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= n;++j){
            cin >> g[i][j];
        }
    }
    auto f = [](int a,int b){return (a | b);};
    vector<SparseTable<int,decltype(f)>>strow(n + 1),stcol(n + 1);
    for(int i = 1;i <= n;++i){
        strow[i] = SparseTable<int,decltype(f)>(g[i],f);
    }
    vector<int>tmp(n + 1);
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= n;++j){
            tmp[j] = g[j][i];
        }
        stcol[i] = SparseTable<int,decltype(f)>(tmp,f);
    }
    vector<int>dp(1 << 15);
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= n;++j){
            int cur = g[i][j];
            int k = min({n - i,i - 1,n - j,j - 1});
            int last = 0;
            int l = 0,r = k;
            while(l <= r){
                while(l <= r){
                    int mid = l + r >> 1;
                    if((strow[i].query(j - mid,j + mid) | stcol[j].query(i - mid,i + mid)) != cur){
                        r = mid - 1;
                    }else{
                        l = mid + 1;
                    }
                }
                dp[cur] += l - last;
                if(l <= k)
                cur = (strow[i].query(j - l,j + l) | stcol[j].query(i - l,i + l));
                last = l;
                r = k;
            }
        }
    }
    for(int i = 0;i < 15;++i){
        for(int j = 0;j < (1 << 15);++j){
            if(j >> i & 1){
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }
    for(int i = 1;i <= q;++i){
        int x;cin >> x;
        x = x & ((1 << 15) - 1);
        cout << dp[x] << '\n';
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