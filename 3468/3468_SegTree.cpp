#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX = 100005;

ll N, Q, x, arr[MAX], t[MAX * 4], lazy[MAX * 4], l, r;
char op;

ll inline max(ll a, ll b) {
    return a >= b ? a : b;
}

ll inline min(ll a, ll b) {
    return a <= b ? a : b;
}

void build(ll a[], ll v, ll tl, ll tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        ll tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

void push(ll v, ll l, ll r) {
    if (lazy[v] == 0) return;
    ll mid = (l + r) / 2;
    t[v * 2] += lazy[v] * (mid - l + 1);
    lazy[v * 2] += lazy[v];
    t[v * 2 + 1] += lazy[v] * (r - mid);
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
}

void update(ll v, ll tl, ll tr, ll l, ll r, ll x) {
    if (l > r) return;
    if (tl >= l && tr <= r) {
        t[v] += x * (tr - tl + 1);
        lazy[v] += x;
    } else {
        push(v, tl, tr);
        ll tm = (tl + tr) / 2;
        update(v * 2, tl, tm, l, min(r, tm), x);
        update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
        t[v] = t[v * 2] + t[v * 2 + 1];
    }
}

ll query(ll v, ll tl, ll tr, ll l, ll r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return t[v];
    push(v, tl, tr);
    ll tm = (tl + tr) / 2;
    return query(v * 2, tl, tm, l, min(r, tm)) + query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
}

int main() {
    scanf("%lld%lld", &N, &Q);
    memset(t, 0, sizeof(t));
    memset(lazy, 0, sizeof(lazy));
    for (ll i = 1; i <= N; ++i) scanf("%lld", &arr[i]);
    build(arr, 1, 1, N);
    getchar();
    for (ll i = 0; i < Q; ++i) {
        scanf("%c%lld%lld", &op, &l, &r);
        if (op == 'Q') printf("%lld\n", query(1, 1, N, l, r));
        else {
            scanf("%lld", &x);
            update(1, 1, N, l, r, x);
        }
        getchar();
    }

    return 0;
}