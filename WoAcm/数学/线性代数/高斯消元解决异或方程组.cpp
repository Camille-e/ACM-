#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
using ull = unsigned long long;
const int mod = 1e9 + 7;
const int maxn = 1e3 + 2;
//https://www.luogu.com.cn/problem/P2447
// n 个方程,m 个未知数
// g[i][j] 表示第 i 个方程是否包含 x_j
// 返回 -1 表示无解,否则返回系数矩阵的秩
// ans 存储一组解,自由变量取 0
int goss(int n,int m,vector<bitset<maxn>>&g,vector<ull>&t,vector<ull>&ans){
    // bas[i] 表示主元为第 i 个未知数的方程
    // bt[i] 表示对应方程的右侧
    vector<bitset<maxn>> bas(m);
    vector<ull> bt(m);
    vector<int> id(m,-1);
    int r = 0;
    for(int i = 0;i < n;++i){
        auto cur = g[i];
        ull v = t[i];
        bool ins = 0;
        for(int j = 0;j < m;++j){
            if(!cur[j])continue;
            if(id[j] != -1){
                cur ^= bas[j];
                v ^= bt[j];
            }else{
                bas[j] = cur;
                bt[j] = v;
                id[j] = i;
                ++r;
                ins = 1;
                break;
            }
        }
        // 出现矛盾方程
        if(!ins && v)return -1;
    }
    if(r < m)return r;
    // 回代求解
    ans.assign(m,0);
    for(int i = m - 1;i >= 0;--i){
        ans[i] = bt[i];
        for(int j = i + 1;j < m;++j){
            if(bas[i][j])ans[i] ^= ans[j];
        }
    }
    return r;
}
void solve() {
    int n,m;
    cin >> m >> n;
    vector<string>g1(n);
    vector<ull>t(n);
    for(int i = 0;i < n;++i){
        cin >> g1[i] >> t[i];
    }
    vector<bitset<maxn>>g(n);
    for(int i = 0;i < n;++i){
        for(int j = 0;j < m;++j){
            g[i][j] = (g1[i][j] == '1');
        }
        g[i][m] = t[i];
    }
    vector<ull>ans;
    int id = goss(n,m,g,t,ans);
    if(id == -1){
        cout << "Cannot Determine\n";
        return;
    }
    cout << id << '\n';
    for(int i = 0;i < m;++i){
        if(g[i][m] == 1){
            cout << "?y7M#\n";
        }else{
            cout << "Earth\n";
        }
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