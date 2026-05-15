#include <bits/stdc++.h>
using namespace std;
struct Hungarian {
    int n1, n2;
    vector<vector<int>> g;
    vector<int> match, vis;
    Hungarian(int _n1, int _n2) {
        init(_n1, _n2);
    }
    void init(int _n1, int _n2) {
        n1 = _n1;
        n2 = _n2;
        g.assign(n1 + 1, {});
        match.assign(n2 + 1, 0);
        vis.assign(n2 + 1, 0);
    }
    void addEdge(int x, int y) {
        g[x].push_back(y);
    }
    bool dfs(int x) {
        for (int y : g[x]) {
            if (vis[y]) continue;
            vis[y] = 1;
            if (!match[y] || dfs(match[y])) {
                match[y] = x;
                return true;
            }
        }
        return false;
    }
    int solve() {
        int ans = 0;
        fill(match.begin(), match.end(), 0);
        //从后往前遍历可以改变对应的右边点匹配的字典序大小
        for (int i = 1; i <= n1; i++) {
            fill(vis.begin(), vis.end(), 0);
            if (dfs(i)) ans++;
        }
        return ans;
    }
    vector<pair<int, int>> getMatching() {
        vector<pair<int, int>> res;
        for (int y = 1; y <= n2; y++) {
            if (match[y]) {
                res.push_back({match[y], y});
            }
        }
        return res;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n1, n2, m;
    cin >> n1 >> n2 >> m;
    Hungarian hg(n1, n2);
    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        hg.addEdge(x, y);
    }
    cout << hg.solve() << '\n';
    return 0;
}