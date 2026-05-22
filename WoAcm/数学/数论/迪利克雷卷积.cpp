#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
void Dirichlet(vector<ll>& f,vector<ll>&g,ll n){
    vector<ll>h(n + 1,0);
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j+=i){
            h[j] = (h[j] + f[i] * g[j / i]) % mod;
        }
    }
    for(int i = 1;i <= n;i++){
        f[i] = h[i];
    }
}//卷积（f*g）(n)    nlogn
vector<ll> ksm(vector<ll>&res,vector<ll>&g,ll b,ll n){
    while(b){
        if(b & 1){
            Dirichlet(res,g,n);
        }
         Dirichlet(g,g,n);
        b >>= 1;
    }
    return res;
};//卷积快速幂
void solve(){
    ll n,k;
    cin >> n >> k;
    vector<ll>f(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> f[i];
    }
    vector<ll>g(n + 1,1);
    vector<ll>res(n + 1,0);
    res[1] = 1;
    //任何数对res进行迪利克雷卷积不变 
    ksm(res,g,k,n);
    Dirichlet(f,res,n);
    for(int i = 1;i <= n;i++){
        cout << f[i] <<" ";
    }
    cout <<"\n";
}
int main(){ 
       int _ = 1;
       cin >> _;
       while(_--){
        solve();
       }
}