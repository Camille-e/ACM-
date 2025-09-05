#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
template<typename T>
vector<pair<T,int>>divpricount(T k){
    vector<pair<T, int>> fact;
    for (T i = 2; i * i <= k; i++){
        int cnt = 0;
        while (k % i == 0){
            k /= i;
            cnt++;
        }
        if(cnt)
        fact.emplace_back(i, cnt);
    }
    if (k > 1){
        fact.emplace_back(k, 1);
    }
    return fact;
}
template<typename T>
vector<T> divpri(T k){
    vector<T> fact;
    for (T i = 2; i * i <= k; i++){
        while (k % i == 0){
            k /= i;
        }
        fact.emplace_back(i);
    }
    if (k > 1){
        fact.emplace_back(k);
    }
    return fact;
}
template<typename T>
vector<T> divfac(T k){
    vector<T> fact;
    for (T i = 1; i * i <= k; i++){
        if(k % i == 0){
            fact.emplace_back(i);
            if(k / i != i){
                fact.emplace_back(k / i);
            }
        }
    }
    return fact;
}
//n阶乘下p的幂次
ll multiplicity_factorial(ll n, ll p) {
    ll cnt = 0;
    while (n >= p){
        cnt += n / p;
        n /= p;
    }
    return cnt;
}
void solve(){
    
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