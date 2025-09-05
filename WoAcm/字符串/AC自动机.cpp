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
    vector<int>ed(maxn);//以序号i结尾的模式串所在结点
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
    string s;
    cin >> s;
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
    stack<int>st;
    st.push(0);
    vector<bool>vis(maxn);
    //结点警告,即发现模式串
    vector<int>alert(maxn);
    for(int i = 0;i < n;++i){
        alert[ed[i]] = 1;
    }
    while (st.size()){
        int x = st.top();
        if(vis[x] == 0){
            vis[x] = 1;
            for(int i = 0;i < g[x].size();++i){
                st.push(g[x][i]);
            }
        }else{
            st.pop();
            for(int i = 0;i < g[x].size();++i){
                times[x] += times[g[x][i]];
                alert[g[x][i]] |= alert[x];
            }
        }
    }
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