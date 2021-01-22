#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 50005;
const int MAXM = 500005;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, cur, s[MAXM], t[MAXM], dp[MAXN], tree[MAXN * 4];

void build(int v, int tl, int tr) {
    if (tl == tr) tree[v] = INF;
    else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) tree[v] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(v * 2, tl, tm, pos, new_val);
        else update(v * 2 + 1, tm + 1, tr, pos, new_val);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

long query(int v, int tl, int tr, int l, int r) {
    if (l > r) return INF;
    if (l == tl && r == tr) return tree[v];
    int tm = (tl + tr) / 2;
    return min(query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) scanf("%d%d", &s[i], &t[i]);
    build(1, 1, n);
    fill(dp, dp + n + 1, INF);
    dp[1] = 0;
    update(1, 1, n, 1, 0);
    for (int i = 0; i < m; ++i) {
        int v = min(dp[t[i]], query(1, 1, n, s[i], t[i]) + 1);
        dp[t[i]] = v;
        update(1, 1, n, t[i], v);
    }
    printf("%d\n", dp[n]);

    return 0;
}