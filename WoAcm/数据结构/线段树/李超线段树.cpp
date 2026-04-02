#include<bits/stdc++.h>
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using db = double;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
//https://www.luogu.com.cn/problem/P4097
using namespace std;
const int maxn = 50003;
const int mod = 1e9 + 1;
const db EPS = 1e-7;
const db INF = 1e9;
template<typename T>
struct line{
    T k,b;
};
template<class T, class S> bool equal(T x, S y) { //判断两个浮点数是否相等
    return -EPS < x - y && x - y < EPS;
}
//插入线段时要注意垂直的线段特判一下
template<typename T>
struct LiChao{
    #define ls q << 1
    #define rs q << 1 | 1
    int tot = 0,n = 0;
    vector<int>tag;
    vector<line<T>>fun;
    vector<T>val;
    LiChao(int _n) : n(_n){
        tag = vector<int>(_n << 2,0);
        val = vector<T>(_n << 2,-INF);
        fun.push_back({0,-INF});
        tot = 0;
    }
    //大于代表最大值
    inline bool check(int id1, int id2, int x){
        T y1 = Y(x, id1), y2 = Y(x, id2);
        if (!equal(y1, y2)) return y1 > y2;
        return id1 < id2;
    };
    inline bool check(T a,T b){
        return a > b;
    };
    inline T Y(T x,int id){
        return fun[id].k * x + fun[id].b;
    }
    inline void insert_segment(int L,int R,T k,T b){
        fun.push_back({k,b});
        tot = fun.size() - 1;
        seg_update(1,1,n,L,R,tot);
    }
    //改
    inline void push_up(int q,int l,int r){
        T ans = max(Y(l,tag[q]),Y(r,tag[q]));
        if(l == r){
            val[q] = ans;
            return;
        }
        val[q] = max({ans,val[ls],val[rs]});
    }
    inline void seg_update(int q,int l,int r,int L,int R,int id){
        if(L <= l && r <= R){
            change(q,l,r,id);
            return;
        }
        int mid = (l + r) >> 1;
        if(L <= mid) seg_update(ls,l,mid,L,R,id);
        if(R > mid) seg_update(rs,mid + 1,r,L,R,id);
        push_up(q,l,r);
    }
    void change(int q, int l, int r, int id) {
        int m = (l + r) >> 1;
        int t = tag[q];
        if (check(id,t,m)) {
            swap(tag[q], id);
        }
        if (l == r) {
            val[q] = Y(l, tag[q]);
            return;
        }
        if (check(id,tag[q],l)) {
            change(ls, l, m, id);
        } else if (check(id,tag[q],r)) {
            change(rs, m + 1, r, id);
        }
        push_up(q,l,r);
    }
    inline pair<T,int> query(int q,int l,int r,int x){
        if(l == r) return {Y(l,tag[q]),tag[q]};
        int mid = (l + r) >> 1;
        T ans = Y(x,tag[q]);
        int id = tag[q];
        if(x <= mid) {
            auto [lans,lid] = query(ls,l,mid,x);
            if(check(lans,ans)){
                ans = lans;
                id = lid;
            }else if(equal(ans,lans)){
                id = min(id,lid);
            }
        }else{
            auto [rans,rid] = query(rs,mid + 1,r,x);
            if(check(rans,ans)){
                ans = rans;
                id = rid;
            }else if(equal(ans,rans)){
                id = min(id,rid);
            }
        }
        return {ans,id};
    }
    inline pair<T,int> query(int x){
        return query(1,1,n,x);
    }
    inline T Rangequery(int q,int l,int r,int L,int R){
        if(L <= l && r <= R) return val[q];
        int mid = (l + r) >> 1;
        T ans = 0;
        T a1 = Y(max(l,L),tag[q]);
        T a2 = Y(min(r,R),tag[q]);
        if(check(a1,a2)){
            ans = a1;
        }else{
            ans = a2;
        }
        if(L <= mid) {
            auto lans = Rangequery(ls,l,mid,L,R);
            if(check(lans,ans)){
                ans = lans;
            }
        }
        if(R > mid){
            auto rans = Rangequery(rs,mid + 1,r,L,R);
            if(check(rans,ans)){
                ans = rans;
            }
        }
        return ans;
    }
    inline T Rangequery(int L,int R){
        return Rangequery(1,1,n,L,R);
    }
};
void solve(){
    int n;cin >> n;
    LiChao<db> tree(maxn);
    int lastans = 0;
    auto calcx = [&](int num){
        return (num + lastans - 1) % 39989 + 1;
    };
    auto calcy = [&](int num){
        return (num + lastans - 1) % mod + 1;
    };
    for(int i = 1;i <= n;++i){
        int op;cin >> op;
        if(op == 1){
            int x1,x2,y1,y2;cin >> x1 >> y1 >> x2 >> y2;
            x1 = calcx(x1),x2 = calcx(x2);
            y1 = calcy(y1),y2 = calcy(y2);
            db k = 1.0 * (y1 - y2) / (x1 - x2);
            db b = 1.0 * y1 - k * x1;
            if(x1 != x2)
            tree.insert_segment(min(x1,x2),max(x1,x2),k,b);
            else
            tree.insert_segment(min(x1,x2),max(x1,x2),0,max(y1,y2));
        }else{
            int x;cin >> x;
            x = (x + lastans - 1) % 39989 + 1;
            auto [ans,id] = tree.query(x);
            cout << id << '\n';
            lastans = id;
        }
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