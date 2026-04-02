#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//O(pow(n,5/3))
//块长一般设置为ceil(pow(n,0.2 / 0.3)),过不了设置为最优的ceil(pow(n,2.0 / 3) * pow(t,1.0 / 3) / pow(m,1.0 / 3))
void solve(){
    int n, m;
    cin >> n >> m;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i)cin >> a[i];
    int kind = 0;
    //看情况改数据范围;
    vector<int>cnt(1e6 + 1);
    int unit = ceil(pow(n,0.2 / 0.3));
    //l,r,time,id;
    vector<array<int,4>>q(m + 1);
    vector<array<int,2>>chan(m + 1);
    int cntq = 0,cntr = 0;
    for(int i = 0;i < m;++i){
        char op;int x,y;
        cin >> op;cin >> x >> y;
        if(op == 'Q'){
            ++cntq,q[cntq] = {x,y,cntr,cntq};
        }else{
            ++cntr,chan[cntr] = {x,y};
        }
    }
    sort(q.begin() + 1,q.begin() + 1 + cntq,[&](array<int,4>&a,array<int,4>&b){
        if(a[0] / unit != b[0] / unit){
            return a[0] < b[0];
        }else if(a[1] / unit != b[1] / unit){
            return a[1] < b[1];
        }
        return a[2] < b[2];
    });
    //看情况改这个
    auto update = [&](const int& x,const int& num){
        if(num == -1){
            if(--cnt[x] == 0){
                kind--;
            }
        }else{
            if(++cnt[x] == 1){
                kind++;
            }
        }
    };
    //窗口左右边界,当前时间
    int winl = 1,winr = 0,curt = 0;
    vector<int>ans(m);
    for(int i = 1;i <= cntq;++i){
        auto [l,r,time,id] = q[i];
        while(winl > l)update(a[--winl],1);
        while(winr < r)update(a[++winr],1);
        while(winl < l)update(a[winl++],-1);
        while(winr > r)update(a[winr--],-1);
        while(curt < time){
            curt++;
            //注意这里传引用,不要随意修改update的传参
            auto &[pos,val] = chan[curt];
            if(pos >= l && pos <= r){
                update(val,1);
                update(a[pos],- 1);
            }
            swap(val,a[pos]);
        }
        while(curt > time){
            //注意这里传引用,不要随意修改update的传参
            auto &[pos,val] = chan[curt];
            if(pos >= l && pos <= r){
                update(val,1);
                update(a[pos],-1);
            }
            curt--;
            swap(val,a[pos]);
        }
        ans[id] = kind;
    }
    for(int i = 1;i <= cntq;++i){
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