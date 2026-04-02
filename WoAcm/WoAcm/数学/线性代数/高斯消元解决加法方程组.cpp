#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//预定极小值
const double mr = 1e-7;
//传递(n + 1,n + 2)二维数组
//-1代表无解,0代表有无穷多解,1代表有唯一解
//O(n * n * n)
int goss(vector<vector<double>>&g){
    int n = g.size() - 1;
    int m = g[0].size() - 1;
    for(int i = 1;i <= n;++i){
        int mx = i;
        for(int j = 1;j <= n;++j){
            if(j < i && abs(g[j][j]) >= mr){
                continue;
            }
            if(abs(g[j][i]) > abs(g[mx][i])){
                mx = j;
            }
        }
        swap(g[mx],g[i]);
        if(abs(g[i][i]) >= mr){
            double c = g[i][i];
            for(int j = i;j <= n + 1;++j){
                g[i][j] /= c;
            }
            for(int j = 1;j <= n;++j){
                if(j == i)continue;
                double rate = g[j][i] / g[i][i];
                for(int k = i;k <= n + 1;++k){
                    g[j][k] -= rate * g[i][k];
                }
            }
        }
    }
    int sign = 1;
    for(int i = 1;i <= n;++i){
        if(abs(g[i][i]) < mr && abs(g[i][n + 1]) >= mr){
            return -1;
        }
        if(abs(g[i][i]) < mr){
            sign = 0;
        }
    }
    return sign;
}
void solve() {
    int n;
    cin >> n;
    vector<vector<double>>g(n + 1,vector<double>(n + 2));
    for(int i = 1;i <= n;++i){
        for(int j = 1;j <= n + 1;j ++){
            cin >> g[i][j]; 
        }
    }
    int ok = goss(g);
    if(ok == 1){
        for(int i = 1;i <= n;++i){
            cout << 'x' << i << '=';
            cout <<  fixed << setprecision(2) << g[i][n + 1] << '\n';
        }
    }else{
        cout << ok << '\n';
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