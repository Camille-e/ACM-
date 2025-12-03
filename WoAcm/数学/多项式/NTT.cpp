#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr ll P = 998244353;
constexpr ll G = 3;
constexpr ll INVG = 332748118;

ll qpow(ll a, ll b) {
    ll res = 1;
    while(b) {
        if(b & 1) {
            res = res * a % P;
        }
        b >>= 1;
        a = a * a % P;
    }
    return res;
}

void NTT(vector<ll> &A, int opt = 1) {
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
        ll g1 = qpow(opt == 1 ? G : INVG, (P - 1) / len);
        for(int i = 0; i < n; i += len) {
            ll gk = 1;
            for(int j = 0; j < len / 2; ++j) {
                ll x = A[i + j];
                ll y = A[i + j + len / 2] * gk % P;
                A[i + j] = (x + y) % P;
                A[i + j + len / 2] = (x - y + P) % P;
                gk = (gk * g1) % P;
            }
        }
    }
}

vector<ll> multiply(const vector<ll> &A, const vector<ll> &B) {
    int n = bit_ceil(A.size() + B.size() - 1);
    vector<ll> va(A.begin(), A.end());
    vector<ll> vb(B.begin(), B.end());
    va.resize(n), vb.resize(n);
    NTT(va), NTT(vb);
    for (int i = 0; i < n; ++i) {
        va[i] = va[i] * vb[i] % P;
    }
    NTT(va, -1);
    ll invn = qpow(n, P - 2);
    va.resize(A.size() + B.size() - 1);
    for (auto &x : va) {
        x = x * invn % P;
    }
    return va;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    //一共(n + 1)项,从下标0开始
    vector<ll> a(n + 1), b(m + 1);
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