#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
const int maxn = 1e6 + 7;
const int mod = 1e9 + 7;
//https://ac.nowcoder.com/acm/contest/116435/C
struct Trie{
    int n,m;
    int pass[maxn],end[maxn];
    int tree[maxn][26];
    int cn = 1;
    void in(string w){
        int cur = 1;
        pass[cur]++;
        for (int i = 0; i < w.size();++i)
        {
            int path = w[i] - 'a';
            if(tree[cur][path]==0){
                tree[cur][path] = ++cn;
            }
            cur = tree[cur][path];
            pass[cur]++;
        }
        end[cur]++;
    };
    int query(string w){
        int cur = 1;
        for(int i = 0;i < w.size();++i)
        {
            int path = w[i] - 'a';
            if(!tree[cur][path]){
                return 0;
            }
            cur = tree[cur][path];
        }
        return end[cur];
    };
    void del(string w){
        if(query(w)){
            int cur = 1;
            pass[cur]--;
            for (int i = 0;i < w.size();++i){
                int path = w[i] - 'a';
                if(--pass[tree[cur][path]] == 0){
                    tree[cur][path] = 0;
                    return;
                }
                cur = tree[cur][path];
            }
            end[cur]--;
        }
    };
    int fpre(string w) {
        int cur = 1,path;
        for (int i = 0;i < w.size();++i){
            path = w[i] - 'a';
            if(tree[cur][path]==0){
                return 0;
            }
            cur = tree[cur][path];
        }
        return pass[cur];
    };
}tree;
void solve(){
    int n;cin >> n;
    vector<string>k(n);
    for(int i = 0;i < n;++i){
        cin >> k[i];tree.in(k[i]);
    }
    int ans = 0;
    for(int i = 0;i < n;++i){
        ans = max(ans,tree.fpre(k[i]));
    }
    cout << ans << '\n';
}
signed main(){
    IOS;
    int _ = 1;
    //cin >> _;
    while(_--){
        solve();
    }
    return 0;
}