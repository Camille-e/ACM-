#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0), cin.tie(0)
struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        array<int, ALPHABET> next;
        Node() : len{0}, link{0}, next{} {}
    };
    vector<Node> t;
    AhoCorasick() {
        init();
    }
    void init() {
        //1是根节点
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int add(const string &a) {
        int p = 1;
        for (auto c : a) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }
    void work() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }
    int next(int p, int x) {
        return t[p].next[x];
    }
    int link(int p) {
        return t[p].link;
    }
    int len(int p) {
        return t[p].len;
    }
    int size() {
        return t.size();
    }
};
void solve(){
    int n;cin >> n;
    AhoCorasick ac;
    vector<int>id(n + 1);
    for(int i = 1;i <= n;++i){
        string a;cin >> a;
        id[i] = ac.add(a);
    }
    ac.work();
    vector<vector<int>>g(ac.size());
    vector<int>dp(ac.size());
    for(int i = 1;i < ac.size();++i){
        g[ac.t[i].link].push_back(i);
    }
    string tmp;cin >> tmp;
    int cur = 1;
    for(auto x : tmp){
        cur = ac.next(cur,x - 'a');
        dp[cur]++;
    }
    auto dfs = [&](auto && dfs,int i)->void
    {
        for(auto to : g[i]){
            dfs(dfs,to);
            dp[i] += dp[to];
        }
    };
    dfs(dfs,0);
    for(int i = 1;i <= n;++i){
        cout << dp[id[i]] << '\n';
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