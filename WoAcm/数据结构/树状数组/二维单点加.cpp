template<typename T>
struct Fenwick2D {
    Fenwick2D(int n, int m) : n(n), m(m), v(n + 1, vector<T>(m + 1)) {}
    // 单点加：在 (x, y) 加上 dx
    void update(int x, int y, T dx) {
        for(int i = x; i <= n; i += (i & -i)) {
            for(int j = y; j <= m; j += (j & -j)) {
                v[i][j] += dx;
            }
        }
    }
    // 查询 (1,1) 到 (x,y) 的前缀和
    T query(int x, int y) {
        T res{};
        for(int i = x; i > 0; i -= (i & -i)) {
            for(int j = y; j > 0; j -= (j & -j)) {
                res += v[i][j];
            }
        }
        return res;
    }
    // 查询矩形 (x1,y1) 到 (x2,y2)
    T range(int x1, int y1, int x2, int y2) {
        return query(x2, y2)
             - query(x1 - 1, y2)
             - query(x2, y1 - 1)
             + query(x1 - 1, y1 - 1);
    }
    int n, m;
    vector<vector<T>> v;
};
