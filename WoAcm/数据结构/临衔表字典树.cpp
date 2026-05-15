#include <bits/stdc++.h>
using namespace std;
struct Trie {
    vector<array<int, 26>> nxt;
    vector<vector<int>> g;
    vector<int> pass;
    vector<int> end;
    vector<int> dep;
    vector<char> val;
    int root;
    Trie() {
        init();
    }
    void init() {
        nxt.clear();
        g.clear();
        pass.clear();
        end.clear();
        dep.clear();
        val.clear();

        nxt.push_back({});
        g.push_back(vector<int>());
        pass.push_back(0);
        end.push_back(0);
        dep.push_back(0);
        val.push_back('#');
        
        root = newNode('#', 0);
    }
    int newNode(char c, int d) {
        int id = nxt.size();
        nxt.push_back({});
        nxt[id].fill(0);
        g.push_back(vector<int>());
        pass.push_back(0);
        end.push_back(0);
        dep.push_back(d);
        val.push_back(c);
        return id;
    }
    int insert(const string& s) {
        int cur = root;
        pass[cur]++;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[cur][c] == 0) {
                int node = newNode(ch, dep[cur] + 1);
                nxt[cur][c] = node;
                g[cur].push_back(node);
            }
            cur = nxt[cur][c];
            pass[cur]++;
        }
        end[cur]++;
        return cur;
    }
    int query(const string& s) {
        int cur = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[cur][c] == 0) {
                return 0;
            }
            cur = nxt[cur][c];
        }
        return end[cur];
    }
    int prefixCount(const string& s) {
        int cur = root;
        for (char ch : s) {
            int c = ch - 'a';
            if (nxt[cur][c] == 0) {
                return 0;
            }
            cur = nxt[cur][c];
        }
        return pass[cur];
    }
    bool erase(const string& s) {
        if (query(s) == 0) {
            return false;
        }
        int cur = root;
        pass[cur]--;
        for (char ch : s) {
            int c = ch - 'a';
            int nxtNode = nxt[cur][c];
            pass[nxtNode]--;
            if (pass[nxtNode] == 0) {
                nxt[cur][c] = 0;
                auto &vec = g[cur];
                vec.erase(find(vec.begin(), vec.end(), nxtNode));
                return true;
            }
            cur = nxtNode;
        }
        end[cur]--;
        return true;
    }
};