#include<bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(0), cin.tie(0)
using namespace std;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 2;
//https://www.luogu.com.cn/problem/P5357
void solve() {
    int n;
    cin >> n;
    vector<string>a(n);
    vector<vector<int>>tree(maxn,vector<int>(26));
    vector<int>ed(maxn),ok(maxn,-1);//以序号i结尾的模式串所在结点,当前结点是否是模式串结尾结点
    int cn = 0;
    //添加模式串
    auto ad = [&](int k,string a){
        int cur = 0;
        for(int i = 0,path;i < a.size();++i){
            path = a[i] - 'a';
            if(tree[cur][path] == 0){
                tree[cur][path] = ++cn;
            }
            cur = tree[cur][path];
        }
        ed[k] = cur;
        ok[cur] = k;
    };
    for(int i = 0;i < n;++i){
        cin >> a[i];
        ad(i,a[i]);
    }
    //结点出现次数
    vector<int>times(maxn);
    vector<int>fail(maxn);
    auto bfs = [&](){
        queue<int>q;
        for(int i = 0;i < 26; ++i){
            if(tree[0][i] > 0){
                q.push(tree[0][i]);
            }
        }
        while(q.size()){
            int x = q.front();
            q.pop();
            for(int i = 0;i < 26;++i){
                if(tree[x][i] == 0){
                    tree[x][i] = tree[fail[x]][i];
                }else{
                    fail[tree[x][i]] = tree[fail[x]][i];
                    q.push(tree[x][i]); 
                }
            }
        }
    };
    bfs();

    string s;cin >> s;
    int cur = 0;
    for(int i = 0;i < s.size();++i){
        int path = s[i] - 'a';
        cur = tree[cur][path];
        times[cur]++;
    }
    vector<vector<int>>g(maxn);
    for(int i = 1;i <= cn;++i){
        g[fail[i]].push_back(i);
    }
    auto dfs = [&](auto && dfs,int i)->void
    {
        for(auto to : g[i]){
            dfs(dfs,to);
            times[i] += times[to];
        }
    };
    dfs(dfs,0);
    for(int i = 0;i < n; ++i){
        cout << times[ed[i]] <<'\n';
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