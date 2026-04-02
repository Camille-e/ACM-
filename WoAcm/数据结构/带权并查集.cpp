#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using ll = long long;
using namespace std;
//https://www.luogu.com.cn/problem/P1196
template<typename T>
struct DSUT {
    DSUT(int n) : fa(n + 1), sz(n + 1, 1) { 
        iota(fa.begin(), fa.end(), 0);
        val = vector<T>(n + 1);
    };
    int find(int id) {
        if(id == fa[id]) return id;
        int root = find(fa[id]);
        val[id] += val[fa[id]];
        return fa[id] = root;
    }
    void merge(int x, int y, T v) { //要依据题意修改
        int fx = find(x), fy = find(y);
        if(fx == fy)return;
        fa[fx] = fy;
        val[fx] = val[y] - val[x] + v;
        sz[fy] += sz[fx];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    T queryval(int x,int y){
        return val[x] - val[y];
    }
    vector<int> fa, sz;//父节点，集合大小
    //到父亲节点的权值
    vector<T>val;
};
void solve(){
    int n;cin >> n;
    DSUT<int> dsu(3e4);
    for(int i = 1;i <= n;++i){
        char op;int x,y;
        cin >> op >> x >> y;
        if(op == 'M'){
            if(!dsu.same(x,y))
            dsu.merge(x,y,dsu.sz[dsu.find(y)] - dsu.val[y] + dsu.val[x]);
        }else{
            if(dsu.same(x,y)){
                cout << max(abs(dsu.queryval(x,y)) - 1,0) << '\n';
            }else{
                cout << -1 << '\n';
            }
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