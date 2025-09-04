#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using ll = long long;
using namespace std;
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
    std::vector<int> fa, sz;//父节点，到父节点的权值，集合大小
    vector<T>val;
};
void solve(){
    
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