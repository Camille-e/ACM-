#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// 可持久化 01 字典树
// 支持：
// 1. 单点插入生成历史版本
// 2. 查询区间 (versionl, versionr] 中与 x 异或最大的值
template<typename Info>
struct PersistentTrie {
    struct Node {
        int ch[2] = {0, 0};
        Info info;
    };
    static constexpr int H = 30; // 如果值域到 1e9，用 30；若到 int 全范围可改 31
#define ls(x) (node[x].ch[0])
#define rs(x) (node[x].ch[1])
    PersistentTrie() {
        node.reserve(1 << 20);
        node.push_back(Node()); // 0 号空节点
        root.push_back(0);      // 初始版本
    }
    // 基于某个版本插入一个数，返回新版本编号
    int insert(int version, int x) {
        root.push_back(insert(root[version], H, x));
        return (int)root.size() - 1;
    }
    // 查询区间 (versionl, versionr] 中，任选一个数与 x 的最大异或值
    int queryMax(int versionl, int versionr, int x) {
        return queryMax(root[versionl], root[versionr], H, x);
    }
    // 最大异或值对应的那个数
    int queryVal(int versionl, int versionr, int x) {
        return queryVal(root[versionl], root[versionr], H, x, 0);
    }
#undef ls
#undef rs
    vector<Node> node;
    vector<int> root;
private:
    int newNode() {
        node.push_back(Node());
        return (int)node.size() - 1;
    }
    int insert(int lst, int bit, int x) {
        int id = newNode();
        node[id] = node[lst];
        node[id].info = node[id].info + Info(1);
        if(bit < 0) return id;
        int b = (x >> bit) & 1;
        node[id].ch[b] = insert(node[lst].ch[b], bit - 1, x);
        return id;
    }
    int queryMax(int vl, int vr, int bit, int x) {
        if(bit < 0) return 0;
        int b = (x >> bit) & 1;
        int want = b ^ 1;
        int cnt = node[node[vr].ch[want]].info.cnt - node[node[vl].ch[want]].info.cnt;
        if(cnt > 0) {
            return (1 << bit) + queryMax(node[vl].ch[want], node[vr].ch[want], bit - 1, x);
        } else {
            return queryMax(node[vl].ch[b], node[vr].ch[b], bit - 1, x);
        }
    }
    int queryVal(int vl, int vr, int bit, int x, int res) {
        if(bit < 0) return res;
        int b = (x >> bit) & 1;
        int want = b ^ 1;
        int cnt = node[node[vr].ch[want]].info.cnt - node[node[vl].ch[want]].info.cnt;
        if(cnt > 0) {
            return queryVal(node[vl].ch[want], node[vr].ch[want], bit - 1, x, res | (want << bit));
        } else {
            return queryVal(node[vl].ch[b], node[vr].ch[b], bit - 1, x, res | (b << bit));
        }
    }
};

struct Info {
    int cnt = 0;
    Info(int cnt = 0) : cnt(cnt) {}
};

Info operator+(const Info &x, const Info &y) {
    return Info(x.cnt + y.cnt);
}
