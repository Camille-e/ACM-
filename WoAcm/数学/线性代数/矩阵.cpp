template<typename T>
struct Matrix {
    Matrix() : Matrix(0, 0) {};
    Matrix(int _n, int _m, T val = T{}) : n(_n), m(_m), mt(n * m, val){}
    Matrix(const initializer_list<initializer_list<T>> &v) : Matrix(v.size(), v.begin()->size()) {
        int i = 0;
        for(auto &row : v) {
            assert(row.size() == m);
            for(auto &x : row) {
                mt[i++] = x;
            }
        }
    }
    span<T> operator[](int idx) {
        return span<T>(mt.data() + idx * m, m);
    }
    span<const T> operator[](int idx) const {
        return span<const T>(mt.data() + idx * m, m);
    }
    friend Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {
        assert(A.m == B.n);
        Matrix<T> MT(A.n, B.m);
        for(int i = 0; i < MT.n; ++i) {
            for(int j = 0; j < MT.m; ++j) {
                for(int k = 0; k < A.m; ++k) {
                    MT[i][j] = (MT[i][j] + A[i][k] * B[k][j]) % mod;
                }
            }
        }
        return MT;
    }
    friend Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) {
        assert(A.n == B.n && A.m == B.m);
        Matrix<T> MT(A.n, B.m);
        for(int i = 0; i < MT.n; ++i) {
            for(int j = 0; j < MT.m; ++j) {
                MT[i][j] = (A[i][j] + B[i][j]) % mod;
            }
        }
        return MT;
    }
    friend Matrix<T> operator-(const Matrix<T>& A, const Matrix<T>& B) {
        assert(A.n == B.n && A.m == B.m);
        Matrix<T> MT(A.n, B.m);
        for(int i = 0; i < MT.n; ++i) {
            for(int j = 0; j < MT.m; ++j) {
                MT[i][j] = ((A[i][j] - B[i][j]) % mod + mod) % mod;
            }
        }
        return MT;
    }
    static Matrix<T> eye(int n) {
        Matrix<T> MT(n, n);
        for(int i = 0; i < n; ++i) {
            MT[i][i] = 1;
        }
        return MT;
    }
    static Matrix<T> qpow(Matrix<T> a, ll b) {
        Matrix<T> res(Matrix<T>::eye(a.n));
        while(b != 0) {
            if(b & 1) {
                res = res * a;
            }
            a = a * a;
            b >>= 1;
        }
        return res;
    }
    friend ostream& operator<<(ostream& os, const Matrix<T>& o) {
        for(int i = 0; i < o.n; ++i) {
            for(int j = 0; j < o.m; ++j) {
                os << o[i][j] << " \n"[j + 1 == o.m];
            }
        }
        return os;
    }
    int n, m;
    vector<T> mt;
};