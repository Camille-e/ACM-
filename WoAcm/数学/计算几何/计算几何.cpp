#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define db double
#define i128 __int128_t 
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
//https://www.luogu.com.cn/problem/P2742
const int mod = 1e9 + 7;
const int maxn = 1e5 + 2;
const double eps = 1e-9;
const double PI = acos(-1);
typedef struct point{
    ll x,y;
    bool operator<(const point & b)const{
        double k = atan2(y,x);
        if(k < 0)k = 2 * PI + k;
        double k1 = atan2(b.y,b.x);
        if(k1 < 0)k1 = 2 * PI + k1;
        return k < k1;
    }
}P;
P operator-(point & a,point & b){
    return {a.x - b.x,a.y - b.y};
}
P operator+(point & a,point & b){
    return {a.x + b.x,a.y + b.y};
}
bool operator==(point & a,point & b){
    return a.x == b.x && a.y == b.y;
}
//计算距离
auto calc(P a,P b){
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
auto calc2(P a,P b){
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
//计算叉积
auto cross(P a,P b){
    return a.x * b.y - b.x * a.y;
}
//b在a的左边
auto left(P a,P b){
    //线线
    return cross(a,b) > 0.0;
}
auto cross(P a,P b,P c){
    //线(a,b),点(c)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
auto left(P a,P b,P c){
    return cross(a,b,c) > 0.0;
}
//计算点积
auto dot(P a,P b){
    return a.x * b.x + a.y * b.y;
}
//计算模长
auto len(P a){
    return sqrt(a.x * a.x + a.y * a.y);
}
//计算夹角
auto angle(P a,P b){
    return acos(dot(a,b) / len(a) / len(b));
}
//是否垂直
bool vertical(P a,P b){
    return abs(dot(a,b)) <= eps;
}
//是否平行
bool horizen(P a,P b){
    return abs(abs(dot(a,b)) - abs(len(a) * len(b))) <= eps;
}
//直线ab与线段cd是否不相交
bool Disjoint(P a,P b,P c,P d){
    return cross(a,b,c) * cross(a,b,d) <= 0.0;
}
//线段ab与线段cd是否不相交
bool XDisjoint(P a,P b,P c,P d){
    return Disjoint(a,b,c,d) || Disjoint(c,d,a,b);
}
//两点式转点向式
pair<P,P> change(P a,P b){
    return {a,b - a};
}
//求两直线交点,ab,cd
P getNode(P a1,P b1,P c1, P d1){
    auto [a,u] = change(a1,b1);
    auto [b,v] = change(c1,d1);
    auto t = cross((a - b),v) / cross(v,u);
    P k = {t * u.x,t * u.y};
    return a + k;
}
double anglepoint(P a){
    double k = atan2(a.y,a.x);
    if(k < 0)k = 2 * PI + k;
    return k;
}
//点是否在线段上(a,b)
bool Point_Seg(P a,P b,P c){
    if(c.x < min(a.x,b.x) || c.x > max(a.x,b.x) || c.y < min(a.y,b.y) || c.y > max(a.y,b.y)){
        return false;
    }
    return abs(cross(b - a,c)) <= 0;
}
//计算面积(保证点按照逆时针或顺时针排序)(最后一个数是下表1)
auto calc(vector<P> a,int top){
    ll ans = 0;
    for(int i = 1;i < top;++i){
        ans += cross(a[i],a[i + 1]);
    }
    return ans / 2;
}
auto calc(vector<P>& a,vector<int>&st,int& top){
    ll ans = 0;
    for(int i = 1;i < top;++i){
        ans += cross(a[st[i]],a[st[i + 1]]);
    }
    return ans / 2;
}
int Point_Polygon(P A, vector<P> &poly){ // 点与多边形的位置关系（在外部 0，在内部 1，在边上 2，在顶点 3）
    int n = poly.size() - 1;
    for(int i = 1;i <= n;++i){ // 在顶点上
        if(poly[i] == A)return 3;
    }
    for(int i = 1;i <= n;++i){ // 在边上
        if(Point_Seg(poly[i],poly[i % n + 1],A)) return 2;
    }
    int cnt = 0;
    for (int i = 1;i <= n;++i){
        P a = poly[i];
        P b = poly[i % n + 1];
        if((a.y <= A.y) != (b.y <= A.y)){
            ll dx = b.x - a.x;
            ll dy = b.y - a.y;
            if(dy != 0){
                ll t1 = a.x * dy + (A.y - a.y) * dx;
                ll t2 = A.x * dy;
                if((dy > 0 && t1 > t2) || (dy < 0 && t1 < t2)){
                    cnt++;
                }
            }
        }
    }
    return cnt % 2;
}
//排序a数组
pair<vector<int>,int> Andrew(vector<P> &a){
    int n = a.size();
    //存凸包点
    vector<int>st(n + 2);
    sort(a.begin(),a.end(),[&](P &b,P &c){
        if(b.x != c.x){
            return b.x < c.x;
        }
        return b.y < c.y;
    });
    int top = 0;
    st[++top] = 0;
    //构建上下凸包
    for(int i = 1;i < n;++i){
        while(top > 1 && !left(a[st[top - 1]],a[st[top]],a[i])){
            top--;
        }
        st[++top] = i;
    }
    int t = top;
    for(int i = n - 2;i >= 0;--i){
        while(top > t && !left(a[st[top - 1]],a[st[top]],a[i])){
            top--;
        }
        st[++top] = i;
    }
    //从1开始到top - 1
    return {st,top};
}
void solve(){
    int n;
    cin >> n;
    vector<P>a(n);
    for(auto & [x,y] :a)cin >> x >> y;
    auto [st,top] = Andrew(a);
    double dis = 0;
    
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