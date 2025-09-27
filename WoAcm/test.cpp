#include<bits/stdc++.h>
//g++内部平衡树
//order_of_key(k)返回小于k的元素个数
//erase(find(x))删一个元素
//find_by_order(k)返回第k小的元素
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
// using namespace __gnu_pbds;
//内部平衡树
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
//随机数
//rnd(1,1e18)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
auto rnd = [](ll l, ll r) { return (l <= r ? uniform_int_distribution<ll>(l, r)(rng) : 0); };
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
ll ksm(ll a,ll b){
    ll res = 1;
    a %= mod;
    while(b){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
};
ll inv(ll a){
    return ksm(a,mod - 2);
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