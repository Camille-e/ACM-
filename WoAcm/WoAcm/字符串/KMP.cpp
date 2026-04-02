#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxv = 1e5 + 2;
//https://www.luogu.com.cn/problem/P3375
void solve() {
    string a,b;
    cin >> a >> b;
    int n = a.size();
    int m = b.size();
    //最长真前后子串匹配长度(核心)
    //a a b a a b c
   //-1 0 1 0 1 2 3
    vector<int>pre(m + 1);
    pre[0] = -1,pre[1] = 0;
    int i = 2;
    int cur = 0;
    //求b的pre数组
    while(i <= m){
        if(b[i - 1] == b[cur]){
            pre[i++] = ++cur;
        }else if(cur > 0){
            cur = pre[cur];
        }else{
            pre[i++] = 0;
        }
    }
    int aid = 0,bid = 0;
    //字符串b在字符串a中出现的位置
    vector<int>ans;
    while(aid < n){
        if(a[aid] == b[bid]){
            aid++,bid++;
        }else if(bid > 0){
            bid = pre[bid];
        }else{
            aid++;
        }
        if(bid == m){
            ans.push_back(aid - m + 1);
            bid = pre[bid];
        }
    }
    for(int i = 0;i < ans.size();++i){
        cout << ans[i] << '\n';
    }
    for(int i = 1;i <= m;++i){
        cout << pre[i] << " \n"[i == n];
    }
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