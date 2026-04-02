#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
//https://www.luogu.com.cn/problem/P1330
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for(int i = 1; i <= m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> col(n + 1); //染色值1/2，是否标记
    int cnt1 = 0,cnt2 = 0;
    auto dfs = [&](auto&& dfs, int i, int val) ->bool { //判定是否是二分图
        col[i] = val;
        if(val == 1)cnt1++;
        else cnt2++;
        for(auto to : g[i]) {
            if(!col[to]) {
                if(!dfs(dfs, to, val ^ 3)) {
                    return false;
                }
            } else if(col[to] == val) {
                return false;
            }
        }
        return true;
    };
    int ans = 0;
    for(int i = 1;i <= n;++i){
        if(!col[i]){
            cnt1 = 0,cnt2 = 0;
            if(!dfs(dfs,i,1)){
                cout << "Impossible\n";
                return 0;
            }else{
                ans += min(cnt1,cnt2);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}