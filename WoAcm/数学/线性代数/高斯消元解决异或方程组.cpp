#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e3 + 2;
//https://www.luogu.com.cn/problem/P2447
//n 行 m 列
//O(n * n * n / 64)
int goss(int n,int m,vector<bitset<maxn>>&g){
    bool ok = 1;
    //在前id式子中能够消元出答案,-1表示无解
    int id = -1;
    for(int i = 0;i < m;++i){
        for(int j = 0;j < n;++j){
            if(j < i && g[j][j] == 1)continue;
            else if(g[j][i] == 1){
                id = max(j,id);
                swap(g[i],g[j]);
                break;
            }
        }
        if(g[i][i] == 1){
            for(int j = 0;j < n;++j){
                if(j != i && g[j][i]){
                    g[j] ^= g[i];
                }
            }
        }else{
            return -1;
        }
    }
    return id + 1;
}
void solve() {
    int n,m;
    cin >> m >> n;
    vector<string>g1(n);
    vector<int>t(n);
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
    int id = goss(n,m,g);
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