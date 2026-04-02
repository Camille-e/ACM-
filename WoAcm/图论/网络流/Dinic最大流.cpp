#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
const int inf = 1e9;
//https://www.luogu.com.cn/problem/P3376
template <typename T> struct Flow_ {
    const int n;
    const T inf = std::numeric_limits<T>::max();
    struct Edge {
        int to;
        T w;
        Edge(int to, T w) : to(to), w(w) {}
    };
    vector<Edge> ver;
    vector<vector<int>> h;
    vector<int> cur, d;
    
    Flow_(int n) : n(n + 1), h(n + 1) {}
    void add(int u, int v, T c) {
        h[u].push_back(ver.size());
        ver.emplace_back(v, c);
        h[v].push_back(ver.size());
        ver.emplace_back(u, 0);
    }
    bool bfs(int s, int t) {
        d.assign(n, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            auto x = q.front();
            q.pop();
            for (auto it : h[x]) {
                auto [y, w] = ver[it];
                if (w && d[y] == -1) {
                    d[y] = d[x] + 1;
                    if (y == t) return true;
                    q.push(y);
                }
            }
        }
        return false;
    }
    T dfs(int u, int t, T f) {
        if (u == t) return f;
        auto r = f;
        for (int &i = cur[u]; i < h[u].size(); i++) {
            auto j = h[u][i];
            auto &[v, c] = ver[j];
            auto &[u, rc] = ver[j ^ 1];
            if (c && d[v] == d[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                c -= a;
                rc += a;
                r -= a;
                if (!r) return f;
            }
        }
        return f - r;
    }
    T work(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, inf);
        }
        return ans;
    }
};
using Flow = Flow_<int>;
// 最小路径覆盖还原
// int p = flow.work(s,t);
// vector<int>next(n + 1),pre(n + 1);
// for(int i = 1;i <= n;++i){
//     for (int idx : flow.h[i]) {
//         auto& e = flow.ver[idx];
//         int v = e.to;
//         if (v >= n + 1 && v <= 2 * n && e.w == 0) {
//             next[i] = v - n;
//             pre[v - n] = i;
//             break;
//         }
//     }
// }
// for(int i = 1;i <= n;++i){
//     if(pre[i] == 0){
//         cout << i << ' ';
//         int cur = i;
//         while(next[cur]){
//             cout << next[cur] << ' ';
//             cur = next[cur];
//         }
//         cout << '\n';
//     }
// }
void solve(){
    int n,m,s,t;cin >> n >> m >> s >> t;
    Flow_<ll> di(n);
    for(int i = 1;i <= m;++i){
        int u,v,c;cin >> u >> v >> c;
        di.add(u,v,c);
    }
    cout << di.work(s,t) << '\n';
}
signed main() {
    IOS;
    int _ = 1;
    // cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}