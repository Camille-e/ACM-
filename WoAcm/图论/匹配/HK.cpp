#include<bits/stdc++.h>
using namespace std;
struct HopcroftKarp {
    int n, m; // 左边点数, 右边点数
    vector<vector<int>> g;
    vector<int> dist, matchL, matchR;
    HopcroftKarp(int n, int m) : n(n), m(m) {
        g.assign(n + 1, {});
        dist.assign(n + 1, 0);
        matchL.assign(n + 1, 0);
        matchR.assign(m + 1, 0);
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
    }
    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (matchL[u] == 0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                int nxt = matchR[v];
                if (nxt == 0) {
                    found = true;
                } else if (dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
            }
        }
        return found;
    }
    bool dfs(int u) {
        for (int v : g[u]) {
            int nxt = matchR[v];
            int ws = nxt;
            if (ws == 0 || (dist[ws] == dist[u] + 1 && dfs(ws))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
    int work() {
        int ans = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (matchL[u] == 0 && dfs(u)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
signed main() {
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    HopcroftKarp flow(n1, n2);
    while (m--) {
        int x, y;
        cin >> x >> y;
        flow.addEdge(x, y);
    }
    cout << flow.work() << endl;
}
