#include<bits/stdc++.h>
#define ll long long
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://www.luogu.com.cn/problem/P5960
void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>>g(n + 1);
    int u,v,w;
    for(int i = 0;i < m;++i){
        cin >> u >> v >> w;
        g[v].push_back({u,w});
    }
    for(int i = 1;i <= n;++i){
        g[0].push_back({i,0});
    }
    vector<int>dis(n + 1,1e9 + 7);
    vector<int>vis(n + 1);
    queue<int>q;
    q.push(0),dis[0] = 0;
    vector<int>cnt(n + 1);
    while(q.size()){
        int cur = q.front();
        q.pop(),vis[cur] = 0;
        for(auto [to,val]: g[cur]){
            if(dis[cur] + val < dis[to]){
                dis[to] = dis[cur] + val;
                if(vis[to] == 0){
                    if(++cnt[to] == n + 1){
                        cout << "NO\n";
                        return;
                    }
                    vis[to] = 1,q.push(to);
                }
            }
        }
    }
    for(int i = 1;i <= n;++i){
        cout << dis[i] << " \n"[i == n];
    }
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