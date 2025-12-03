#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
//https://www.luogu.com.cn/problem/P3812
template<typename T>
struct Basis{
    int n,m;vector<T>basis,gossbasis;bool zero;
    Basis (const int& _n,vector<T> vc,const int &_m) : n(_n),m(_m) {
        gossbasis = vc;
        basis = vector<T>(m + 1);
        zero = 0;
    };
    void build(){
        for(int i = 0;i < n;++i){
            T num = gossbasis[i];
            bool ok = 0;
            for(int j = m;j >= 0;--j){
                if((num >> j) & 1ll){
                    if(basis[j] == 0){
                        basis[j] = num;
                        ok = 1;
                        break;
                    }else{
                        num ^= basis[j];
                    }
                }
            }
            if(ok == 0){
                zero = 1;
            }
        }
    }
    //goss数组长度
    int len = 0;
    void buildgoss(){
        for(int i = m;i >= 0;--i){
            for(int j = len;j < n;++j){
                if((gossbasis[j] >> i) & 1ll){
                    swap(gossbasis[j],gossbasis[len]);
                    break;
                }
            }
            if((gossbasis[len] >> i) & 1ll){
                for(int j = 0; j < n; ++j){
                    if(j != len && (gossbasis[j] >> i) & 1ll)
                        gossbasis[j] ^= gossbasis[len];
                }
                len++;
            }
        }
        zero = n != len;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<ll>a(n);
    for(ll & x : a)cin >> x;
    Basis B(n,a,50);
    B.buildgoss();
    ll ans = 0;
    for(int i = B.len - 1;i >= 0;--i){
        ans ^= B.gossbasis[i];
    }
    cout << ans << '\n';
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