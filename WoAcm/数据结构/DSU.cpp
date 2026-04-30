#include<bits/stdc++.h>
using namespace std;
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
    // 链式并查集遍历
    // t = l;
    // while(t <= r){
    //     int nxt = dsu.find(t) + 1;
    //     if(nxt == t + 1){
    //         pos++;
    //         dsu.merge(t,nxt);
    //     }
    //     t = find(t);
    // }
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