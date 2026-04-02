#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://www.luogu.com.cn/problem/P7771
// 无向图欧拉回路or通路
struct Euler {
    int id = 0;
    vector<int> edg;           // 存储边
    vector<vector<int>> g; // 存储图
    // 初始化
    Euler(int n, int m) {
        g.resize(n + 1);
        edg.resize(m + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        id++;
        g[u].push_back(id);
        g[v].push_back(id);
        edg[id] = u ^ v;
    }
    // 判断是否存在欧拉通路and返回小起点
    int is_semiEuler() {
        int n = g.size() - 1;
        int odd = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (g[i].size() & 1) {
                odd++;
                if(start == 0)start = i;
            }
            
        }
        if (odd == 0) return 1;
        if (odd == 2) return start;
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        int n = g.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (g[i].size() & 1) {
                return false;
            }
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<int> Euler_tour(int start) {
        vector<int> tour;
        function<void(int)> dfs = [&](int u) {
            while (!g[u].empty()) {
                int i = g[u].back();
                g[u].pop_back();
                if (edg[i] == -1) continue;
                int v = edg[i] ^ u;
                edg[i] = -1;
                dfs(v);
            }
            tour.push_back(u);
        };
        dfs(start);
        return tour;
    }
};
// 有向图欧拉回路or通路
struct Directed_Euler {
    vector<int> inE, outE;     // 存储入,出度
    vector<vector<int>> g; // 存储图
    int n;
    // 初始化
    Directed_Euler(int n) : n(n) {
        g.resize(n + 1);
        inE.resize(n + 1);
        outE.resize(n + 1);
    }
    // 添加边
    void add_edge(int u, int v) {
        g[u].push_back(v);
        outE[u]++;
        inE[v]++;
    }
    // 判断是否存在欧拉通路and返回起点(需判断图是强连通的)
    int is_semiEuler() {
        int odd = 0, neodd = 0, start = 0;
        for (int i = 1; i <= n; i++) {
            if (outE[i] - inE[i] == 1) {
                odd++;
                start = i;
            } else if (inE[i] - outE[i] == 1) {
                neodd++;
            } else if (inE[i] != outE[i]) {
                return 0;
            }
        }
        if (odd == 1 && neodd == 1) {
            return start;
        }
        if (odd == 0 && neodd == 0) {
            return 1;
        }
        return 0;
    }
    // 判断是否存在欧拉回路
    bool is_Euler() {
        int n = g.size() - 1;
        for (int i = 1; i <= n; i++) {
            if (inE[i] != outE[i])
                return false;
        }
        return true;
    }
    // 求解欧拉回路or通路
    vector<int> Euler_tour(int start) {
        vector<int> tour;
        function<void(int)> dfs = [&](int u) {
            while (!g[u].empty()) {
                auto v = g[u].back();
                g[u].pop_back();
                dfs(v);
            }
            tour.push_back(u);
        };
        dfs(start);
        return tour; // 返回的是逆序的欧拉回路or通路
    }
};
void solve(){
    int n,m;cin >> n >> m;
    Directed_Euler d(n);
    for(int i = 1;i <= m;++i){
        int u,v;cin >> u >> v;
        d.add_edge(u,v);
    }
    for(int i = 1;i <= n;++i){
        sort(d.g[i].begin(),d.g[i].end(),greater<>());
    }
    int st = d.is_semiEuler();
    if(st == 0){
        cout << "No\n";
        return;
    }
    auto ans = d.Euler_tour(st);
    if(ans.size() != m + 1){
        cout << "No\n";
        return;
    }
    for(int i = ans.size() - 1;i >= 0;--i){
        cout << ans[i] << " \n"[i == 0];
    }
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