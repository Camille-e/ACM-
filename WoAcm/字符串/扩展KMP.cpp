#include<bits/stdc++.h>
#define ll long long
#define int ll
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 2;
//https://www.luogu.com.cn/problem/P5410
void solve() {
    string a,b;
    cin >> a >> b;
    //z[i]代表下标为i的字符串后缀匹配自己前缀的最长长度
    //z[0] : aab z[1] : aab
    //       aab        ab
    //       3          1
    vector<int>z(b.size());
    for(int i = 0,c = 0,r = 0,len;i < b.size();++i){
        len = i < r ? min(z[i - c],r - i) : 0;
        while(i + len < b.size() && b[i + len] == b[len]){
            len++;
            r = i + len;
            c = i;
        }
        z[i] = len;
    }
    int ans = 0;
    for(int i = 0;i < z.size();++i){
        ans ^= (i + 1) * (z[i] + 1);
    }
    cout<< ans <<'\n';
    //p[i]代表a字符串从下标i开始的后缀匹配b字符串的最长长度
    vector<int>p(a.size());
    for(int i = 0,c = 0,r = 0,len;i < a.size();++i){
        len = i < r ? min(z[i - c],r - i) : 0;
        while(i + len < a.size() && len < b.size() && a[i + len] == b[len]){
            len++;
            r = i + len;
            c = i;
        }
        p[i] = len;
    }
    ans = 0;
    for(int i = 0;i < p.size();++i){
        ans ^= (i + 1) * (p[i] + 1);
    }
    cout<< ans <<'\n';
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