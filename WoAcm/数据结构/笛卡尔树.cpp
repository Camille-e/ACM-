#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
template<typename T>
struct CT{
    int n;
    vector<T> a,st;
    vector<int>left,right;
    // 传(n + 1)数组
    CT (const int& _n,vector<T>&b) : n(_n){
        a = b;
        st = vector<T>(n + 1);
        left = right = vector<T>(n + 1);
    };
    void build(){
        for(int i = 1,top = 0,pos = 0;i <= n;++i){
            pos = top;
            //按照小根堆组织
            while(pos && a[st[pos]] > a[i]){
                pos--;
            }
            if(pos)right[st[pos]] = i;
            if(pos < top)left[i] = st[pos + 1];
            st[++pos] = i;
            top = pos;
        }
    }
};
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