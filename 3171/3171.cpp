#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 10005;
const int SECONDS = 86399 + 1;
const long INF = 5000000000L;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, e;
long tree[SECONDS * 4];
struct cow {
    int t1, t2, s;
    bool friend operator<(const cow c1, const cow c2) {
        return c1.t2 < c2.t2 || c1.t2 == c2.t2 && c1.t1 < c2.t1;
    }
} cows[MAX];

void build(int v, int tl, int tr) {
    if (tl == tr) tree[v] = INF;
    else {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }
}

void update(int v, int tl, int tr, int pos, long new_val) {
    if (tl == tr)
        tree[v] = min(new_val, tree[v]);
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
    while (scanf("%d%d%d", &n, &m, &e) != EOF && n) {
        int i = 0;
        while (n--) {
            scanf("%d%d%d", &cows[i].t1, &cows[i].t2, &cows[i].s);
            if (cows[i].t2 < m || cows[i].t1 > e) continue;
            ++i;
        }
        n = i;
        sort(cows, cows + n);
        build(1, 0, SECONDS - 1);
        for (int i = 0; i < n; ++i) {
            long nv = INF;
            if (cows[i].t1 == m) nv = cows[i].s;
            nv = min(nv, query(1, 0, SECONDS - 1, max(m, cows[i].t1 - 1), min(e, cows[i].t2 - 1)) + cows[i].s);
            update(1, 0, SECONDS - 1, cows[i].t2, nv);
        }
        long ans = query(1, 0, SECONDS - 1, e, e);
        printf("%ld\n", ans == INF ? -1 : ans);
    }

    return 0;
}