#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
const int N = 3e6 + 1;
// https://acm.hdu.edu.cn/showproblem.php?pid=2824
int Phi(int n){
    int res = n;
    for(int i = 2;i * i <= n;++i){
        if(n % i == 0){
            res = res / i * (i - 1);
            while(n % i == 0){
                n /= i;
            }
        }
    }
    if(n > 1)res = res / n * (n - 1);
    return res;
}
vector<ll>phi(N + 1);
vector<int>pri;
bitset<N>vis;
void get_phi(int n){
    phi[1] = 1;
    for(int i = 2;i <= n;++i){
        if(!vis[i]){
            pri.push_back(i);
            phi[i] = i - 1;
        }
        for(int j = 0;1ll * pri[j] * i <= n;++j){
            int cur = i * pri[j];
            vis[cur] = 1;
            if(i % pri[j] == 0){
                phi[cur] = phi[i] * pri[j];break;
            }else{
                phi[cur] = phi[i] * (pri[j] - 1);
            }
        }
    }
}
void solve(){
    get_phi(3e6);
    for(int i = 1;i <= 3e6; ++i){
        phi[i] += phi[i - 1];
    }
    int a,b;
    while(cin >> a >> b){
        cout << phi[b] - phi[a - 1] << '\n';
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