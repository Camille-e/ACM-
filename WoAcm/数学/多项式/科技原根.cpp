#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128_t;
ll qpow(ll a, ll b, ll mod) {
    ll res = 1 % mod;
    a %= mod;
    while (b) {
        if (b & 1) res = (i128)res * a % mod;
        a = (i128)a * a % mod;
        b >>= 1;
    }
    return res;
}
bool isPrime(ll n) {     // Miller-Rabin 素性测试
    if (n < 2) return false;
    static const ll p[] = {2,3,5,7,11,13,17,19,23,29,31,37};
    for (ll x : p) {
        if (n % x == 0) return n == x;
    }
    ll d = n - 1, r = 0;
    while ((d & 1) == 0) d >>= 1, ++r;
    for (ll a : p) {
        if (a >= n) continue;
        ll x = qpow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (ll i = 0; i < r - 1; ++i) {
            x = (i128)x * x % n;
            if (x == n - 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}
ll pollard_rho(ll n) { //找一个非平凡因子
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ll> dist(2, n - 1);
    ll c = dist(rng), x = dist(rng), y = x, d = 1;
    auto f = [&](ll v) { return ((i128)v * v + c) % n; };
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(abs(x - y), n);
    }
    return d == n ? pollard_rho(n) : d;
}
void factor(ll n, vector<ll>& fac) {   //质因数分解（结果可重复）
    if (n <= 1) return;
    if (isPrime(n)) { fac.push_back(n); return; }
    ll d = pollard_rho(n);
    factor(d, fac);
    factor(n / d, fac);
}
vector<ll> getPrimeFactors(ll n) {   // 返回不同质因子
    vector<ll> fac;
    factor(n, fac);
    sort(fac.begin(), fac.end());
    fac.erase(unique(fac.begin(), fac.end()), fac.end());
    return fac;
}
ll phi(ll n) { //	欧拉函数
    if (n <= 1) return n;
    auto ps = getPrimeFactors(n);
    ll res = n;
    for (ll p : ps) res = res / p * (p - 1);
    return res;
}
bool hasRoot(ll n) {    // 是否存在原根
    if (n <= 1) return false;
    if (n == 2 || n == 4) return true;
    if (n % 2 == 0) {
        if (n % 4 == 0) return false;
        n /= 2;
    }
    return getPrimeFactors(n).size() == 1;
}
ll minRoot(ll n) {      // 最小原根，不存在返回 -1
    if (!hasRoot(n)) return -1;
    ll ph = phi(n);
    auto ps = getPrimeFactors(ph);
    for (ll g = 1; g < n; ++g) {
        if (gcd(g, n) != 1) continue;
        bool ok = true;
        for (ll p : ps) {
            if (qpow(g, ph / p, n) == 1) { ok = false; break; }
        }
        if (ok) return g;
    }
    return -1;
}
vector<ll> allRoots(ll n) { // 所有原根（升序），不存在返回空
    ll g = minRoot(n);
    if (g == -1) return {};
    ll ph = phi(n);
    vector<ll> roots;
    ll cur = 1;
    for (ll s = 1; s <= ph; ++s) {
        cur = (i128)cur * g % n;    // cur = g^s mod n
        if (gcd(s, ph) == 1) roots.push_back(cur);
    }
    sort(roots.begin(), roots.end());
    return roots;
}
ll rootCount(ll n) {    // 原根个数
    if (!hasRoot(n)) return 0;
    return phi(phi(n));
}
void solve(){
    ll n,d;
    cin >> n >> d;
    auto roots = allRoots(n);
    cout << roots.size() <<"\n";
    for(int i = 1;i < roots.size();i ++){
        cout << roots[i] <<" ";
    }
    cout <<"\n";
}
int main() {
    int _ = 1;
    cin >> _;
    while(_--){
        solve();
    }
    return 0;
}