#include<bits/stdc++.h>
using ll = long long;
using namespace std;
struct Point {
    ll x, y;
};
Point O;
ll cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}
ll dis2(Point a, Point b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy;
}
bool cmp(Point a, Point b) {
    ll c = cross(O, a, b);
    if (c != 0)
        return c > 0;
    return dis2(O, a) < dis2(O, b);
}