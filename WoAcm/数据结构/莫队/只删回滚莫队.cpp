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
        return a[1] > b[1];
    });
    int kind = 0;
    //看情况改数据范围;
    vector<int>cnt(2e5 + 2),forcecnt(2e5 + 2);
    //看情况改这个
    auto del = [&](int x,int & ans){
        if(--cnt[x] == 0){
            ans = min(ans,x);
        }
    };
    //看情况改传参
    auto add = [&](int x){
        ++cnt[x];
    };
    int winl = 1,winr = 0,cur_block = 0;
    vector<int>ans(m);
    for(int i = 0;i < m;++i){
        auto [l,r,id] = q[i];
        if(pos[l] == pos[r]){
            //改暴力判断

            for(int j = l;j <= r;++j)forcecnt[a[j]]++;
            ans[id] = 0;
            while(forcecnt[ans[id]])ans[id]++;
            for(int j = l;j <= r;++j)forcecnt[a[j]]--;
            continue;
        }
        //不属于同一个块,初始化窗口
        if(pos[l] != cur_block){
            //这里要改
            for(int j = 0;j <= n + 1;++j){
                cnt[a[j]] = 0;
            }
            for(int j = L[pos[l]];j <= n;++j){
                cnt[a[j]]++;
            }
            kind = 0;
            while(cnt[kind])kind++;
            winr = n;
            winl = L[pos[l]];
            cur_block = pos[l];
            //另一种写法,用于不能直接初始化的,preans是最开始初始化的答案(1 ~ n)范围上的
            // while(winr < n)add(a[++winr]);
            // kind = preans;
            // while(winl < L[pos[l]])del(a[winl++],kind);
            // preans = kind;
            // cur_block = pos[l];
        }
        
        while(winr > r)del(a[winr--],kind);
        //改回滚状态

        int tmp = kind;
        int curl = winl;
        while(curl < l)del(a[curl++],tmp);
        //改答案条件

        ans[id] = tmp;
        while(curl > winl)add(a[--curl]);
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