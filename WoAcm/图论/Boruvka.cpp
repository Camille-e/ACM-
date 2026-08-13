#include<bits/stdc++.h>
using ll = long long;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://qoj.ac/contest/2534/problem/14549
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
        if(f == z)return f;
        if(sz[f] < sz[z])swap(f,z);
        sz[f] += sz[z];
        fa[z] = f;
        return f;
    }
    int size(int x){
        return sz[find(x)];
    }
};
//每次对所有连通块找最小的那个出边然后连接两个连通块
void solve(){
    int n,k;cin >> n >> k;
    vector<ll>a(n + 1);
    set<pair<int,int>>st;
    for(int i = 1;i <= n;++i){
        cin >> a[i];
        a[i] %= k;
        st.insert({a[i],i});
    }
    DSU dsu(n);
    int cnt = n;
    ll ans = 0;
    while(cnt > 1){
        vector<int>best(n + 1,2e9);
        vector<int>tid(n + 1);
        vector<vector<int>>g(n + 1);
        for(int i = 1;i <= n;++i){
            g[dsu.find(i)].push_back(i);
        }
        for(int i = 1;i <= n;++i){
            for(auto x : g[i]){
                st.erase({a[x],x});
            }
            for(auto x : g[i]){
                auto id = st.begin();
                if(id != st.end()){
                    if((id->first + a[x]) % k < best[i]){
                        best[i] = (id->first + a[x]) % k;
                        tid[i] = id->second;
                    }
                }
                id = st.lower_bound({k - a[x],0});
                if(id != st.end()){
                    if((id->first + a[x]) % k < best[i]){
                        best[i] = (id->first + a[x]) % k;
                        tid[i] = id->second;
                    }
                }
            }
            for(auto x : g[i]){
                st.insert({a[x],x});
            }
        }
        for(int i = 1;i <= n;++i){
            if(tid[i] != 0){
                if(dsu.same(i,tid[i]))continue;
                cnt--;
                ans += best[i];
                dsu.merge(i,tid[i]);
            }
        }
    }
    cout << ans << '\n';
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