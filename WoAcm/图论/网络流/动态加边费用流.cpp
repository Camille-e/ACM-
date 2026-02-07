#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
int m,sum;
int g1[102][42];
auto node(int d,int f){
    return (d - 1) * m + f;
};
struct MinCostFlow {
    using LL = long long;
    using PII = pair<LL, int>;
    const LL INF = numeric_limits<LL>::max();
    struct Edge {
        int v, c, f;
        Edge(int v, int c, int f) : v(v), c(c), f(f) {}
    };
    const int n;
    int pren;
    vector<Edge> e;
    vector<vector<int>> g;
    vector<LL> h, dis;
    vector<int> pre;
    vector<int> top,next;
    MinCostFlow(int n) : n(n + 1), g(n + 1),top(m + 1,1),next(n + 1) {
        
    }
    void add(int u, int v, int c, int f) {
        g[u].push_back(e.size());
        e.emplace_back(v, c, f);
        g[v].push_back(e.size());
        e.emplace_back(u, 0, -f);
    }
    bool dijkstra(int s, int t) {
        dis.assign(n, INF);
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
        return dis[t] != INF;
    }
    pair<int, LL> flow(int s, int t) {
        int flow = 0;
        LL cost = 0;
        h.assign(n, 0);
        while (dijkstra(s, t)) {
            for (int i = 0; i < n; ++i) h[i] += dis[i];
            int aug = numeric_limits<int>::max();
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                aug = min(aug, e[pre[i]].c);
                next[i] = 1;
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].v) {
                e[pre[i]].c -= aug;
                e[pre[i] ^ 1].c += aug;
            }
            flow += aug;
            cost += LL(aug) * h[t];
            for(int i = 1;i <= m;++i){
                if(top[i] < sum && next[node(top[i],i)]){
                    top[i]++;
                    for(int j = 1;j <= pren;++j){
                        add(sum * m + j,node(top[i],i),1,top[i] * g1[i][j]);
                    }
                    add(node(top[i],i),t,1,0);
                }
            }
        }
        return {flow, cost};
    }
};
void solve(){
    int n;cin >> n >> m;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i)cin >> a[i];
    sum = accumulate(a.begin() + 1,a.end(),0);
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= m;++j){
            cin >> g1[j][i];
        }
    }
    int s = sum * m + n + 1,t = sum * m + n + 2;
    MinCostFlow flow(t);
    flow.pren = n;
    for(int i = 1;i <= n;++i){
        flow.add(s,sum * m + i,a[i],0);
    }
    for(int j = 1;j <= m;++j){
        for(int k = 1;k <= n;++k){
            flow.add(sum * m + k,node(1,j),1,g1[j][k] * 1);
        }
        flow.add(node(1,j),t,1,0);
    }
    auto [fi,val] = flow.flow(s,t);
    // cout << fi << ' ' << val << '\n';
    cout << val << '\n';
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