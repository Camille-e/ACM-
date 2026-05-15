#include <bits/stdc++.h>
using namespace std;
template<class T>
struct KM {
    static constexpr T INF = numeric_limits<T>::max() / 4;
    static constexpr T NEG_INF = numeric_limits<T>::lowest() / 4;
    int n, m;
    vector<vector<T>> a;
    KM(int n, int m) : n(n), m(m) {
        assert(n <= m);
        a.assign(n + 1, vector<T>(m + 1, NEG_INF));
    }
    void addEdge(int u, int v, T w) {
        if (u < 1 || u > n || v < 1 || v > m) return;
        a[u][v] = max(a[u][v], w);
    }
    tuple<T, vector<int>, vector<int>> solve() {
        vector<T> u(n + 1), v(m + 1);
        vector<int> p(m + 1), way(m + 1);
        for (int i = 1; i <= n; ++i) {
            p[0] = i;
            int j0 = 0;
            vector<T> minv(m + 1, INF);
            vector<char> used(m + 1, false);
            do {
                used[j0] = true;
                int i0 = p[j0];
                int j1 = 0;
                T delta = INF;
                for (int j = 1; j <= m; ++j) {
                    if (used[j]) continue;
                    T cur = -a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
                for (int j = 0; j <= m; ++j) {
                    if (used[j]) {
                        u[p[j]] += delta;
                        v[j] -= delta;
                    } else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while (p[j0] != 0);
            do {
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            } while (j0 != 0);
        }
        vector<int> matchX(n + 1, 0), matchY(m + 1, 0);
        for (int j = 1; j <= m; ++j) {
            if (p[j]) {
                matchY[j] = p[j];
                matchX[p[j]] = j;
            }
        }
        T ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += a[i][matchX[i]];
        }
        return {ans, matchX, matchY};
    }
};