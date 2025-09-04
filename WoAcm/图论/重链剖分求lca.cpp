#include <bits/stdc++.h>
using namespace std;
struct HLD {
    HLD(const int &_n) : n(_n), v(_n + 1) {
        fa = dep = son = sz = top = dfn = out = seg = vector<int>(_n + 1);
    }

    void addEdge(const int &x, const int &y) {
        v[x].push_back(y);
        v[y].push_back(x);
    }

    void dfs1(int id, int &t) { 
        sz[id] = 1;
        dfn[id] = t;
        seg[t] = id;
        for(const auto &nxt : v[id]) {
            if(nxt == fa[id]) continue;
            fa[nxt] = id;
            dep[nxt] = dep[id] + 1;
            dfs1(nxt, ++t);
            sz[id] += sz[nxt];
            if(sz[son[id]] < sz[nxt]) {
                son[id] = nxt;
            }
        }
        out[id] = t;
    }
    void dfs2(int id, int t) {
        top[id] = t;
        if(son[id] == 0) return;
        dfs2(son[id], t);
        for(const auto &nxt : v[id]) {
            if(nxt == fa[id] || nxt == son[id]) continue;
            dfs2(nxt, nxt);
        }
    }
    void work(int root = 1) {
        int dfsn = 1;
        dfs1(root, dfsn);
        dfs2(root, root);
    }

    bool isAncestor(int x, int y) {
        return dfn[x] <= dfn[y] && out[x] >= out[y];
    }

    int lca(int x, int y) {
        while(top[x] != top[y]) { 
            if(dep[top[x]] < dep[top[y]]) {
                swap(x, y);
            }
            x = fa[top[x]];
        }
        return (dep[x] < dep[y] ? x : y);
    }

    int dis(int x, int y) {
        return dep[x] + dep[y] - 2 * dep[lca(x, y)];
    }

    int kth(int id, int k) {
        if(k > dep[id]) return 0;
        while(dep[id] - dep[top[id]] + 1 <= k) {
            k -= (dep[id] - dep[top[id]] + 1);
            id = fa[top[id]];
        }
        return seg[dfn[id] - k];
    }

    vector<vector<int>> v;
    vector<int> fa, dep, son, sz, top, dfn, out, seg;
    int n;
};