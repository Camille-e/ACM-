#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 998244353;
const int maxn = 1e5 + 2;
struct DSU{
    DSU(int n) : fa(n + 1),sz(n + 1,1){
        iota(fa.begin(),fa.end(),0);
    }
    vector<int>fa,sz;
    int find(int x){
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool same(int u,int v){
        return find(u) == find(v);
    }
    int merge(int f,int z){
        f = find(f),z = find(z);
        if(sz[f] < sz[z])swap(f,z);
        sz[f] += sz[z];
        fa[z] = f;
        return f;
    }
    int size(int x){
        return sz[find(x)];
    }
};
void solve(){
    int n,m;
    cin >> n >> m;
    int op,u,v;
    DSU e(n);
    for(int i = 0;i < m;++i){
        cin >> op >> u >> v;
        if(op == 1){
            e.merge(u,v);
        }else{
            cout << (e.same(u,v) ? "Y" : "N") << '\n';
        }
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