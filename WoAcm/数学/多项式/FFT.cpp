#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr double PI = numbers::pi_v<double>;
//一般用这个
//https://www.luogu.com.cn/problem/P3803
void FFT(vector<complex<double>> &A, int opt = 1) {
    int n = A.size();
    vector<int> p(n);
    for(int i = 0; i < n; ++i) {
        p[i] = p[i / 2] / 2 + (n / 2) * (i & 1);
    }
    for(int i = 0; i < n; ++i) {
        if(i < p[i]) {
            swap(A[i], A[p[i]]);
        }
    }
    for(int len = 2; len <= n; len <<= 1) {
        complex<double> w1 = {cos(2 * PI / len), sin(2 * PI / len) * opt};
        for(int i = 0; i < n; i += len) {
            complex<double> wk = {1, 0};
            for(int j = 0; j < len / 2; ++j) {
                complex<double> x = A[i + j];
                complex<double> y = A[i + j + len / 2] * wk;
                A[i + j] = x + y;
                A[i + j + len / 2] = x - y;
                wk *= w1;
            }
        }
    }
}

template<typename T>
vector<T> multiply(const vector<T> &A, const vector<T> &B) {
    int n = bit_ceil(A.size() + B.size() - 1);
    vector<complex<double>> v(n);
    for(int i = 0; i < A.size(); ++i) {
        v[i].real(A[i]);
    }
    for(int i = 0; i < B.size(); ++i) {
        v[i].imag(B[i]);
    }
    v.resize(n);
    FFT(v);
    for(int i = 0; i < n; ++i) {
        v[i] *= v[i];
    }
    FFT(v, -1);
    vector<T> res(A.size() + B.size() - 1);
    for(int i = 0; i < res.size(); ++i) {
        res[i] = (T)round(v[i].imag() / 2 / n);
    }
    return res;
}

template<typename T>
vector<T> convolution(const vector<T> &A, vector<T> kernel) {
    reverse(kernel.begin(), kernel.end());
    auto res = multiply(A, kernel);
    return vector(res.begin() + kernel.size() - 1, res.begin() + A.size());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    //一共(n + 1)项,从下标0开始
    vector<int> a(n + 1), b(m + 1);
    for(int i = 0; i <= n; ++i) {
        cin >> a[i];
    }
    for(int i = 0; i <= m; ++i) {
        cin >> b[i];
    }
    auto c = multiply(a, b);
    for(int i = 0; i < c.size(); ++i) {
        cout << c[i] << " \n"[i + 1 == c.size()];
    }
    return 0;
}
