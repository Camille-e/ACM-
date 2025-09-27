#include <bits/stdc++.h>
using ll = long long;
using namespace std;
//https://www.luogu.com.cn/problem/P3834
template <class Y>
struct WaveletMatrix {
private:
    int n, bits; 
    vector<vector<int>> mat; 
    vector<int> mid;

    int rank(bool bit, int pos, int lvl) const {
        if (pos == 0) return 0;
        int ones = mat[lvl][pos - 1];
        return bit ? ones : pos - ones;
    }
public:
    WaveletMatrix() : n(0), bits(0) {}
    template <class T>
    WaveletMatrix(vector<T> V, T mx = -1) : n(V.size()) {
        if (mx == -1) {
            for (auto &v : V) mx = max(mx, v);
        }
        bits = mx > 0 ? __lg(mx) + 1 : 1;
        mat.assign(bits, vector<int>(n));
        mid.resize(bits);

        for (int d = bits - 1; d >= 0; --d) {
            vector<T> vec[2];
            for (int i = 0; auto &v : V) {
                int bit = (v >> d) & 1;
                vec[bit].push_back(v);
                mat[d][i++] = bit;
            }
            mid[d] = vec[0].size();
            V.clear();
            V.insert(V.end(), vec[0].begin(), vec[0].end());
            V.insert(V.end(), vec[1].begin(), vec[1].end());
            for (int i = 1; i < n; ++i) {
                mat[d][i] += mat[d][i - 1];
            }
        }
    }
    // [L, R) k + 1 th smallest
    Y kth(int L, int R, int k) const {
        Y res = 0;
        for (int d = bits - 1; d >= 0; --d) {
            int cnt0 = rank(0, R, d) - rank(0, L, d);
            if (k < cnt0) {
                L = rank(0, L, d);
                R = rank(0, R, d);
            } else {
                res |= ((Y)1 << d);
                k -= cnt0;
                L = mid[d] + rank(1, L, d);
                R = mid[d] + rank(1, R, d);
            }
        }
        return res;
    }
};