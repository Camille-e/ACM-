#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
typedef struct point{
    double x,y;
    bool operator<(const point & b)const{
        if(x != b.x){
            return x < b.x;
        }
        return y < b.y;
    }
}P;
auto calc(P a,P b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
auto cross(P a,P b,P c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
//存凸包点
int st[maxn];
void solve(){
    int n;
    cin >> n;
    vector<P>a(n);
    for(auto & [x,y] :a)cin >> x >> y;
    sort(a.begin(),a.end());
    int top = 0;
    st[++top] = 0;
    //构建上下凸包
    for(int i = 1;i < n;++i){
        while(top > 1 && cross(a[st[top - 1]],a[st[top]],a[i]) <= 0.0){
            top--;
        }
        st[++top] = i;
    }
    int t = top;
    for(int i = n - 2;i >= 0;--i){
        while(top > t && cross(a[st[top - 1]],a[st[top]],a[i]) <= 0.0){
            top--;
        }
        st[++top] = i;
    }
    
    double dis = 0;
    //从1开始到top
    for(int i = 1;i < top;++i){
        dis += calc(a[st[i]],a[st[i + 1]]);
    }
    cout << fixed << setprecision(2) << dis  << '\n';
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