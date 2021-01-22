#include <cstdio>

using namespace std;

const int MAX = 100005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int n, q, A, B, a[MAX], preidx[MAX], postidx[MAX], t[MAX * 4];

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) t[v] = 1;
    else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = max(t[v * 2], t[v * 2 + 1]);
        int low = max(tl, preidx[tm]);
        int high = min(tr, postidx[tm]);
        t[v] = max(t[v], high - low + 1);
    }
}

int query(int v, int tl, int tr, int l, int r, int sl, int sr) {
    if (l > r) return 0;
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    int ans = max(query(v * 2, tl, tm, l, min(r, tm), sl, sr), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, sl, sr));
    int low = max(sl, preidx[tm]);
    int high = min(sr, postidx[tm]);
    ans = max(ans, high - low + 1);
    return ans;
}

int main() {
    while (scanf("%d%d", &n, &q) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        int last = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] == a[last])
                preidx[i] = last;
            else {
                preidx[i] = i;
                last = i;
            }
        }
        last = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] == a[last])
                postidx[i] = last;
            else {
                postidx[i] = i;
                last = i;
            }
        }
        build(a, 1, 0, n - 1);
        while (q--) {
            scanf("%d%d", &A, &B);
            --A, --B;
            printf("%d\n", query(1, 0, n - 1, A, B, A, B));
        }
    }

    return 0;
}