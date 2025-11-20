#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
template<typename T>
struct ST{
    int n,m;
    vector<vector<T>>stmi,stmx,stgcd;
    vector<T>b;
    // 传 n + 1 数组
    ST (const int &_n,vector<T>a) : n(_n){
        m = __lg(n + 1);
        b = a;
    };
    void buildmi(){
        stmi = vector<vector<T>>(n + 1,vector<T>(m + 1));
        for(int i = 1;i <= n;++i){
            stmi[i][0] = b[i];
        }
        for(int p = 1;p <= m;++p){
            for(int i = 1;i + (1 << p) - 1 <= n;++i){
                stmi[i][p] = min(stmi[i][p - 1],stmi[i + (1 << (p - 1))][p - 1]);
            }
        }
    }
    void buildmx(){
        stmx = vector<vector<T>>(n + 1,vector<T>(m + 1));
        for(int i = 1;i <= n;++i){
            stmx[i][0] = b[i];
        }
        for(int p = 1;p <= m;++p){
            for(int i = 1;i + (1 << p) - 1 <= n;++i){
                stmx[i][p] = max(stmx[i][p - 1],stmx[i + (1 << (p - 1))][p - 1]);
            }
        }
    }
    void buildgcd(){
        stgcd = vector<vector<T>>(n + 1,vector<T>(m + 1));
        for(int i = 1;i <= n;++i){
            stgcd[i][0] = b[i];
        }
        for(int p = 1;p <= m;++p){
            for(int i = 1;i + (1 << p) - 1 <= n;++i){
                stgcd[i][p] = gcd(stgcd[i][p - 1],stgcd[i + (1 << (p - 1))][p - 1]);
            }
        }
    }
    T querymi(int l,int r){
        int p = __lg(r - l + 1);
        return min(stmi[l][p],stmi[r - (1 << p) + 1][p]);
    }
    T querymx(int l,int r){
        int p = __lg(r - l + 1);
        return max(stmx[l][p],stmx[r - (1 << p) + 1][p]);
    }
    T querygcd(int l,int r){
        int p = __lg(r - l + 1);
        return gcd(stgcd[l][p],stgcd[r - (1 << p) + 1][p]);
    }
};
void solve(){
    int n,m;
    cin >> n >> m;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;++i)cin >> a[i];
    ST st(n,a);
    st.buildmx();
    st.buildmi();
    
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