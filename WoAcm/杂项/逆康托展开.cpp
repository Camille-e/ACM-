#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
//https://www.luogu.com.cn/problem/U72177
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
int tree[maxn << 2];
void up(int i){
    tree[i] = tree[i << 1] + tree[i << 1 | 1];
}
void build(int l,int r,int i){
    if(l == r){
        tree[i] = 1;
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,i << 1),build(mid + 1,r,i << 1 | 1);
    up(i);
}
int querysum(int l,int r,int i,int val){
    if(l == r){
        return r;
    }
    int mid = l + r >> 1;
    if(tree[i << 1] >= val){
        return querysum(l,mid,i << 1,val);
    }
    return querysum(mid + 1,r,i << 1 | 1,val - tree[i << 1]);
}
void del(int tl,int tr,int l,int r,int i){
    if(tl <= l && r <= tr){
        tree[i] = 0;
        return;
    }
    int mid = l + r >> 1;
    if(tl <= mid){
        del(tl,tr,l,mid,i << 1);
    }
    if(tr > mid){
        del(tl,tr,mid + 1,r,i << 1 | 1);
    }
    up(i);
}
void solve(){
    int n,x;
    cin >> n;
    ll diff;cin >> diff;
    vector<ll>fac(n + 1);
    vector<int>tree(n + 1);
    auto query = [&](int x){
        ll res = 0;
        while(x){
            res += tree[x];
            x -= (x & -x);
        }
        return res;
    };
    auto add = [&](int x,int val){
        while(x <= n){
            tree[x] += val;
            x += (x & -x);
        }
    };
    for(int i = 1;i <= n;++i){
        add(i,1);
    }
    for(int i = n - 1;i >= 0;--i){
        cin >> x;
        fac[i] = query(x - 1);
        add(x,-1);
    }
    fac[0] = diff;
    for(int i = 1;i <= n;++i){
        fac[i] += fac[i - 1] / i;
        fac[i - 1] %= i;
    }
    build(1,n,1);
    vector<int>ans(n + 1);
    for(int i = n - 1;i >= 0;--i){
        ans[i + 1] = querysum(1,n,1,fac[i] + 1);
        //cout << ans[i + 1] << '\n';
        del(ans[i + 1],ans[i + 1],1,n,1);
    }
    for(int i = n;i >= 1;--i){
        cout << ans[i] << " \n"[i == 1];
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