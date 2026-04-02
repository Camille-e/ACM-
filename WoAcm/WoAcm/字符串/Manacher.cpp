#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 2;
//https://www.luogu.com.cn/problem/P3805
void solve() {
    string a;
    cin >> a;
    string b(a.size() * 2 + 1,'#');
    for(int i = 1;i < b.size();i += 2){
        b[i] = a[i / 2];
    }
    int n = b.size();
    vector<int>p(n);
    int maxv = 1;
    //i:当前来到的位置,c:回文中心,r:最长回文半径
    //i - len,i + len为将要对比的位置
    //(i - len,i + len)双开区间
    for(int i = 0,c = 0,r = 0,len;i < n;++i){
        len = i < r ? min(r - i,p[2 * c - i]) : 1;
        while(i - len >= 0 && i + len < n && b[i - len] == b[i + len]){
            len ++;
            r = i + len;
            c = i;
        }
        p[i] = len;
        maxv = max(maxv,len);
    }
    cout << maxv - 1 <<'\n';
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