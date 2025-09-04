#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t ;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
template<typename T>
inline void read(T &x){
	T w=1; x=0; 
	char c=getchar(); 
	while(!isdigit(c)){ w|=(c=='-'); c=getchar();}  
	while(isdigit(c)){ x=(x<<1)+(x<<3)+(c^48); c=getchar();} 
	x=x*w;
}

template<typename T>
inline void write1(T x){
    if(x<0){ putchar('-'); x=(~x)+1;}
    if(x>=10){ write(x/10);}
    write(x%10^48); //+'0'是为了让数字类型的x%10变成字符输出
}

inline void write2(ll x){
    static int st[64] = {0}; // int 最多32位
    int top = 0; // 指向栈顶的指针
    do{
        st[top++]=x%10;
        x/=10;
    }while(x>0);
    while(top>0){ putchar(st[--top]^48);}
}

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