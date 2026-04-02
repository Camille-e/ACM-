#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//O(1.5 * n * sqrt(m))
//一般块长设置为ceil(n / sqrt(m)),过不了设置为(n / sqrt(2 * m))
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int>a(n + 1);
    //从块1开始
    //l,r,id
    vector<array<int,3>>q(m);
    for(int i = 1;i <= n;++i)cin >> a[i];
    //离散化
        vector<int>b = a;
        sort(b.begin() + 1,b.end());
        b.erase(unique(b.begin() + 1,b.end()),b.end());
        map<int,int>hash;vector<int>val(n + 1);
        for(int i = 1;i < b.size();++i){
            hash[b[i]] = i;
            val[i] = b[i];
        }
        for(int i = 1;i <= n;++i)a[i] = hash[a[i]];
    for(int i = 0;i < m;++i)cin >> q[i][0] >> q[i][1],q[i][2] = i;
    int unit = ceil(n / sqrt(m));
    vector<int>pos(n + 1),L(n + 1),R(n + 1);
    int tot = n / unit;
    for (int i = 1; i <= tot; i++) {
        L[i] = (i - 1) * unit + 1;
        R[i] = i * unit;
    }
    if (R[tot] < n) {
        ++tot;
        L[tot] = R[tot - 1] + 1;
        R[tot] = n;
    }
    for(int i = 1;i <= tot;++i){
        for(int j = L[i];j <= R[i];++j)pos[j] = i;
    }
    sort(q.begin(),q.end(),[&](array<int,3>&a,array<int,3>&b){
        if(pos[a[0]] != pos[b[0]]){
            return pos[a[0]] < pos[b[0]];
        }
        return a[1] < b[1];
    });
    ll kind = 0;
    //看情况改数据范围;
    vector<int>cnt(n + 1),forcecnt(n + 1);
    //看情况改这个
    auto del = [&](int x){
        --cnt[x];
    };
    //看情况改传参
    auto add = [&](int x,ll &ans){
        ++cnt[x];
        ans = max(1ll * cnt[x] * val[x],ans);
    };
    int winl = 1,winr = 0,cur_block = 0;
    vector<ll>ans(m);
    for(int i = 0;i < m;++i){
        auto [l,r,id] = q[i];
        if(pos[l] == pos[r]){
            for(int j = l;j <= r;++j)forcecnt[a[j]]++;
            //改暴力判断
            for(int j = l;j <= r;++j)ans[id] = max(ans[id],1ll * val[a[j]] * forcecnt[a[j]]);
            for(int j = l;j <= r;++j)forcecnt[a[j]]--;
            continue;
        }
        //不属于同一个块,初始化窗口
        if(pos[l] != cur_block){
            for(int j = 1;j <= n;++j){
                cnt[j] = 0;
            }
            winr = R[pos[l]];
            winl = R[pos[l]] + 1;
            //这里要改
            kind = 0;
            cur_block = pos[l];
        }
        while(winr < r)add(a[++winr],kind);
        //改回滚状态
        ll tmp = kind;
        int curl = winl;
        while(curl > l)add(a[--curl],tmp);
        //改答案条件
        ans[id] = tmp;
        while(curl < winl)del(a[curl++]);
    }
    for(int i = 0;i < m;++i){
        cout << ans[i] << '\n';
    }
}
signed main() {
    IOS;
    int _ = 1;
    //cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}