//Pass test cases in forums but WA
#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair<ll, int> Pr;

const int MAX = 50005;

inline int min(int a, int b) {
    return a <= b ? a : b;
}

inline int max(int a, int b) {
    return a >= b ? a : b;
}

int N, M, R, C, minidx, ans[MAX];
ll x1, y11, x2, y2, mindis;
struct line {
    int idx;
    ll span, low, high;
    line(int id, ll s, ll l, ll h) : idx(id), span(s), low(l), high(h) {}
    line() {}
    bool friend operator<(const line& r1, const line& r2) {
        return r1.span < r2.span || r1.span == r2.span && (r1.low < r2.low || r1.low == r2.low && r1.high < r2.high);
    }
} cur, rows[MAX], cols[MAX];
struct node {
    ll low, high;
    node(ll l, ll h) : low(l), high(h) {}
    node() {}
} rowseg[MAX * 4], colseg[MAX * 4];

void build(line a[], node t[], int v, int tl, int tr) {
    if (tl == tr) t[v] = node(a[tl].low, a[tl].high);
    else {
        int tm = (tl + tr) / 2;
        build(a, t, v << 1, tl, tm);
        build(a, t, (v << 1) + 1, tm + 1, tr);
        t[v] = node(min(t[v << 1].low, t[(v << 1) + 1].low), max(t[v << 1].high, t[(v << 1) + 1].high));
    }
}

Pr query(line a[], node t[], int v, int tl, int tr, int l, int r, ll theshold, ll val, bool lowfirst) {
    if (l > r || t[v].high < theshold || t[v].low > theshold) return Pr(LLONG_MAX, -1);
    if (l == r) return Pr(llabs(val - a[l].span), a[l].idx);
    int tm = (tl + tr) / 2;
    if (lowfirst) {
        if (t[v << 1].low <= theshold && theshold <= t[v << 1].high)
            return query(a, t, v << 1, tl, tm, l, min(r, tm), theshold, val, lowfirst);
        else
            return query(a, t, (v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, theshold, val, lowfirst);
    } else {
        if (t[(v << 1) + 1].low <= theshold && theshold <= t[(v << 1) + 1].high)
            return query(a, t, (v << 1) + 1, tm + 1, tr, max(l, tm + 1), r, theshold, val, lowfirst);
        else
            return query(a, t, v << 1, tl, tm, l, min(r, tm), theshold, val, lowfirst);
    }
}

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        R = C = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%lld%lld%lld%lld", &x1, &y11, &x2, &y2);
            if (x1 == x2) {
                if (y11 > y2) swap(y11, y2);
                cols[C++] = line(i, x1, y11, y2);
            } else {
                if (x1 > x2) swap(x1, x2);
                rows[R++] = line(i, y11, x1, x2);
            }
        }
        sort(rows, rows + R);
        sort(cols, cols + C);
        if (R > 0) build(rows, rowseg, 1, 0, R - 1);
        if (C > 0) build(cols, colseg, 1, 0, C - 1);
        memset(ans, 0, sizeof(ans));
        int lb, ub;
        for (int i = 0; i < M; ++i) {
            scanf("%lld%lld", &x1, &y11);
            mindis = LLONG_MAX;
            minidx = -1;
            if (R > 0) {
                cur = line(-1, y11, x1, x1);
                lb = lower_bound(rows, rows + R, cur) - rows - 1;
                if (lb >= 0 && rows[lb].span == y11 && llabs(x1 - rows[lb].high) < mindis) {
                    mindis = llabs(x1 - rows[lb].high);
                    minidx = rows[lb].idx;
                }
                ub = upper_bound(rows, rows + R, cur) - rows;
                if (rows[ub].span == y11 && llabs(x1 - rows[ub].low) < mindis) {
                    mindis = llabs(x1 - rows[ub].low);
                    minidx = rows[ub].idx;
                }
                cur = line(-1, y11, LLONG_MIN, LLONG_MIN);
                lb = lower_bound(rows, rows + R, cur) - rows - 1;
                Pr tmp = query(rows, rowseg, 1, 0, R - 1, 0, lb, x1, y11, false);
                if (tmp.first < mindis) {
                    mindis = tmp.first;
                    minidx = tmp.second;
                }
                cur = line(-1, y11, LLONG_MAX, LLONG_MAX);
                ub = upper_bound(rows, rows + R, cur) - rows;
                tmp = query(rows, rowseg, 1, 0, R - 1, ub, R - 1, x1, y11, true);
                if (tmp.first < mindis) {
                    mindis = tmp.first;
                    minidx = tmp.second;
                }
            }
            if (C > 0) {
                cur = line(-1, x1, y11, y11);
                lb = lower_bound(cols, cols + C, cur) - cols - 1;
                if (lb >= 0 && cols[lb].span == x1 && llabs(y11 - cols[lb].high) < mindis) {
                    mindis = llabs(y11 - cols[lb].high);
                    minidx = cols[lb].idx;
                }
                ub = upper_bound(cols, cols + C, cur) - cols;
                if (cols[ub].span == x1 && llabs(y11 - cols[ub].low) < mindis) {
                    mindis = llabs(y11 - cols[ub].low);
                    minidx = cols[ub].idx;
                }
                cur = line(-1, x1, LLONG_MIN, LLONG_MIN);
                lb = lower_bound(cols, cols + C, cur) - cols - 1;
                Pr tmp = query(cols, colseg, 1, 0, C - 1, 0, lb, y11, x1, false);
                if (tmp.first < mindis) {
                    mindis = tmp.first;
                    minidx = tmp.second;
                }
                cur = line(-1, x1, LLONG_MAX, LLONG_MAX);
                ub = upper_bound(cols, cols + C, cur) - cols;
                tmp = query(cols, colseg, 1, 0, C - 1, ub, C - 1, y11, x1, true);
                if (tmp.first < mindis) {
                    mindis = tmp.first;
                    minidx = tmp.second;
                }
            }
            if (minidx != -1) ++ans[minidx];
        }
        for (int i = 0; i < N; ++i) printf("%d\n", ans[i]);
    }

    return 0;
}