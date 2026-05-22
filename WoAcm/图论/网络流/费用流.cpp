#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
// O(A * E * log V)
// A: 增广次数。若按单位流增广，最坏 A = F；
// 但本模板每次按瓶颈容量增广，实际通常远小于总流量。
template<class Cap = long long, class Cost = long long>
struct MinCostFlow {
    using PII = pair<Cost, int>;
    const Cost INF_COST = numeric_limits<Cost>::max() / 4;
    const Cap INF_CAP = numeric_limits<Cap>::max() / 4;
    struct Edge {
        int v;
        Cap c;
        Cost f;
        Edge(int v, Cap c, Cost f) : v(v), c(c), f(f) {}
    };
    const int n;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<Cost> h, dis;
    vector<int> pre;
    MinCostFlow(int n) : n(n + 1), g(n + 1) {}
    void add(int u, int v, Cap c, Cost f) {
        g[u].push_back(e.size());
        e.emplace_back(v, c, f);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -f);
    }
    bool dijkstra(int s, int t) {
        dis.assign(n, INF_COST);
        pre.assign(n, -1);
        priority_queue<PII, vector<PII>, greater<PII>> que;
        dis[s] = 0;
        que.emplace(0, s);
        while (!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if (dis[u] < d) continue;
            for (int i : g[u]) {
                auto [v, c, f] = e[i];
                if (c > 0 && dis[v] > d + h[u] - h[v] + f) {
                    dis[v] = d + h[u] - h[v] + f;
                    pre[v] = i;
                    que.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != INF_COST;
    }
    pair<Cap, Cost> flow(int s, int t, Cap need = numeric_limits<Cap>::max() / 4) {
        Cap flow = 0;
        Cost cost = 0;
        h.assign(n, 0);
        while (flow < need && dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) {
                if (dis[i] != INF_COST) h[i] += dis[i];
            }
            Cap aug = need - flow;
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                aug = min(aug, e[pre[i]].c);
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += aug * h[t];
        }
        return {flow, cost};
    }
};
void solve(){
    int n,m,s,t;cin >> n >> m >> s >> t;
    MinCostFlow flow(n);
    for(int i = 1;i <= m;++i){
        int u,v,c,f;cin >> u >> v >> c >> f;
        flow.add(u,v,c,f);
    }
    auto [f,c] = flow.flow(s,t);
    cout << f << ' ' << c << '\n';
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