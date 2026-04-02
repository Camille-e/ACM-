#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
const int N = 1e4 + 5, M = 2e5 + 5;
int n, m, s, t, tot = 1, lnk[N], ter[M], nxt[M], val[M], dep[N], cur[N];

void add(int u, int v, int w) {
    ter[++tot] = v, nxt[tot] = lnk[u], lnk[u] = tot, val[tot] = w;
}
void addedge(int u, int v, int w) { 
    add(u, v, w);
    add(v, u, 0);
}
int bfs(int s, int t) {
    memset(dep, 0, sizeof(dep));
    memcpy(cur, lnk, sizeof(lnk));
    std::queue<int> q;
    q.push(s), dep[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = lnk[u]; i; i = nxt[i]) {
            int v = ter[i];
            if (val[i] && !dep[v]) q.push(v), dep[v] = dep[u] + 1;
        }
    }
    return dep[t];
}
int dfs(int u, int t, int flow) {
    if (u == t) return flow;
    int ans = 0;
    for (int &i = cur[u]; i && ans < flow; i = nxt[i]) {
        int v = ter[i];
        if (val[i] && dep[v] == dep[u] + 1) {
            int x = dfs(v, t, std::min(val[i], flow - ans));
            if (x) val[i] -= x, val[i ^ 1] += x, ans += x;
        }
    }
    if (ans < flow) dep[u] = -1;
    return ans;
}
int dinic(int s, int t) {
    int ans = 0;
    while (bfs(s, t)) {
        int x;
        while ((x = dfs(s, t, 1 << 30))) ans += x;
    }
    return ans;
}
void solve(){
    
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
