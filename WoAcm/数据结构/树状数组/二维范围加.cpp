template<typename T>
struct Fenwick2D {
    Fenwick2D(int n, int m)
        : n(n), m(m),
          a(n + 1, vector<T>(m + 1)),
          b(n + 1, vector<T>(m + 1)),
          c(n + 1, vector<T>(m + 1)),
          d(n + 1, vector<T>(m + 1)) {}
    void update(vector<vector<T>>& v, int x, int y, T dx) {
        for(int i = x; i <= n; i += (i & -i)) {
            for(int j = y; j <= m; j += (j & -j)) {
                v[i][j] += dx;
            }
        }
    }
    void add(int x, int y, T dx) {
        update(a, x, y, dx);
        update(b, x, y, dx * (x - 1));
        update(c, x, y, dx * (y - 1));
        update(d, x, y, dx * (x - 1) * (y - 1));
    }
    // 矩形 [x1, y1] ~ [x2, y2] 加 dx
    void range_add(int x1, int y1, int x2, int y2, T dx) {
        add(x1, y1, dx);
        add(x1, y2 + 1, -dx);
        add(x2 + 1, y1, -dx);
        add(x2 + 1, y2 + 1, dx);
    }
    T query(vector<vector<T>>& v, int x, int y) {
        T res{};
        for(int i = x; i > 0; i -= (i & -i)) {
            for(int j = y; j > 0; j -= (j & -j)) {
                res += v[i][j];
            }
        }
        return res;
    }
    // 查询前缀和 [1,1] ~ [x,y]
    T prefix(int x, int y) {
        if(x <= 0 || y <= 0) return T{};
        return query(a, x, y) * x * y
             - query(b, x, y) * y
             - query(c, x, y) * x
             + query(d, x, y);
    }
    // 查询矩形 [x1, y1] ~ [x2, y2] 的和
    T range(int x1, int y1, int x2, int y2) {
        return prefix(x2, y2)
             - prefix(x1 - 1, y2)
             - prefix(x2, y1 - 1)
             + prefix(x1 - 1, y1 - 1);
    }
    int n, m;
    vector<vector<T>> a, b, c, d;
};
