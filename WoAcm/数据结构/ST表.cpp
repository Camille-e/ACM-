#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(false), cin.tie(nullptr)
using ll = long long;
template <class T, class F>
struct SparseTable {
    int n, K;
    vector<int> lg;
    vector<vector<T>> st;
    F func;
    SparseTable() {}
    SparseTable(const vector<T>& a, F f) : func(f) {
        build(a);
    }
    void build(const vector<T>& a) {
        // 传入 1-indexed 数组，a[0] 不用
        n = (int)a.size() - 1;
        K = __lg(n) + 1;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
        st.assign(K, vector<T>(n + 1));
        for (int i = 1; i <= n; ++i) st[0][i] = a[i];
        for (int k = 1; k < K; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                st[k][i] = func(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }
    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return func(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    auto fmin = [](int x, int y) { return min(x, y); };
    auto fmax = [](int x, int y) { return max(x, y); };
    auto fgcd = [](int x, int y) { return std::gcd(x, y); };
    SparseTable<int, decltype(fmin)> stMin(a, fmin);
    SparseTable<int, decltype(fmax)> stMax(a, fmax);
    SparseTable<int, decltype(fgcd)> stGcd(a, fgcd);
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) cout << stMin.query(l, r) << '\n';
        else if (op == 2) cout << stMax.query(l, r) << '\n';
        else if (op == 3) cout << stGcd.query(l, r) << '\n';
    }
}

int main() {
    IOS;
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}
