#include <bits/stdc++.h>
using namespace std;
template <class T>
struct Hamilton {
    T INF;
    int n;
    vector<vector<T>> w;
    vector<vector<T>> dp;
    vector<vector<int>> pre;
    Hamilton(int n, T inf) : n(n), INF(inf) {
        w.assign(n, vector<T>(n, INF));
        for (int i = 0; i < n; i++) w[i][i] = T(0);
    }
    // 无向图加边
    void addEdge(int u, int v, T cost) {
        w[u][v] = min(w[u][v], cost);
        w[v][u] = min(w[v][u], cost);
    }
    // 有向图加边
    void addDirectedEdge(int u, int v, T cost) {
        w[u][v] = min(w[u][v], cost);
    }
    void initDP(int st) {
        int N = 1 << n;
        dp.assign(N, vector<T>(n, INF));
        pre.assign(N, vector<int>(n, -1));
        dp[1 << st][st] = T(0);
        for (int mask = 0; mask < N; mask++) {
            for (int u = 0; u < n; u++) {
                if (dp[mask][u] == INF) continue;
                for (int v = 0; v < n; v++) {
                    if ((mask >> v) & 1) continue;
                    if (w[u][v] == INF) continue;
                    int nmask = mask | (1 << v);
                    T nd = dp[mask][u] + w[u][v];
                    if (nd < dp[nmask][v]) {
                        dp[nmask][v] = nd;
                        pre[nmask][v] = u;
                    }
                }
            }
        }
    }
    vector<int> restorePath(int last) {
        vector<int> path;
        int mask = (1 << n) - 1;
        int cur = last;
        while (cur != -1) {
            path.push_back(cur);
            int p = pre[mask][cur];
            mask ^= (1 << cur);
            cur = p;
        }
        reverse(path.begin(), path.end());
        return path;
    }
    // 最短哈密顿路径：从 st 出发，走完所有点，不要求回到 st
    // 返回 {最小代价, 路径}
    // 无解返回 {INF, {}}
    pair<T, vector<int>> solvePath(int st = 0) {
        initDP(st);
        int full = (1 << n) - 1;
        T ans = INF;
        int last = -1;
        for (int u = 0; u < n; u++) {
            if (dp[full][u] < ans) {
                ans = dp[full][u];
                last = u;
            }
        }
        if (ans == INF) return {INF, {}};
        return {ans, restorePath(last)};
    }
    // 最短哈密顿回路：从 st 出发，走完所有点，最后回到 st
    // 返回 {最小代价, 回路}
    // 无解返回 {INF, {}}
    pair<T, vector<int>> solveCycle(int st = 0) {
        initDP(st);
        int full = (1 << n) - 1;
        T ans = INF;
        int last = -1;
        for (int u = 0; u < n; u++) {
            if (u == st) continue;
            if (dp[full][u] == INF || w[u][st] == INF) continue;
            T cand = dp[full][u] + w[u][st];
            if (cand < ans) {
                ans = cand;
                last = u;
            }
        }
        if (ans == INF) return {INF, {}};
        vector<int> path = restorePath(last);
        path.push_back(st); // 回到起点
        return {ans, path};
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    using T = long long;
    const T INF = (T)4e18;
    Hamilton<T> solver(n, INF);
    for (int i = 0; i < m; i++) {
        int u, v;
        T c;
        cin >> u >> v >> c;
        // 如果题目是 1-indexed，这里改成 --u, --v;
        solver.addEdge(u, v, c);
    }
    // 最短哈密顿路径
    auto [ans1, path1] = solver.solvePath(0);
    if (path1.empty()) {
        cout << "No Hamilton Path\n";
    } else {
        cout << "Hamilton Path cost = " << ans1 << '\n';
        for (int i = 0; i < (int)path1.size(); i++) {
            cout << path1[i] << (i + 1 == (int)path1.size() ? '\n' : ' ');
        }
    }
    // 最短哈密顿回路
    auto [ans2, path2] = solver.solveCycle(0);
    if (path2.empty()) {
        cout << "No Hamilton Cycle\n";
    } else {
        cout << "Hamilton Cycle cost = " << ans2 << '\n';
        for (int i = 0; i < (int)path2.size(); i++) {
            cout << path2[i] << (i + 1 == (int)path2.size() ? '\n' : ' ');
        }
    }
    return 0;
}
