#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 100005;

int N, Q, cnt, a[MAX], b[MAX], x, y, k, ans;
int rt[MAX * 20], lson[MAX * 20], rson[MAX * 20], sum[MAX * 20];

void build(int &x, int l, int r) {
    x = ++cnt;
    sum[x] = 0;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(lson[x], l, mid);
    build(rson[x], mid + 1, r);
}

void update(int &x, int last, int l, int r, int pos) {
    x = ++cnt;
    lson[x] = lson[last];
    rson[x] = rson[last];
    sum[x] = sum[last] + 1;
    if (l == r) return;
    int mid = (l + r) >> 1;
    if (pos <= mid) update(lson[x], lson[last], l, mid, pos);
    else update(rson[x], rson[last], mid + 1, r, pos);
}

int query(int L, int R, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int cnt = sum[lson[R]] - sum[lson[L]];
    if (k <= cnt) return query(lson[L], lson[R], l, mid, k);
    else return query(rson[L], rson[R], mid + 1, r, k - cnt);
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + N);
    cnt = 0;
    build(rt[0], 1, N);
    for (int i = 1; i <= N; ++i) a[i] = lower_bound(b + 1, b + 1 + N, a[i]) - b;
    for (int i = 1; i <= N; ++i) update(rt[i], rt[i - 1], 1, N, a[i]);
    while (Q--) {
        scanf("%d%d%d", &x, &y, &k);
        ans = query(rt[x - 1], rt[y], 1, N, k);
        printf("%d\n", b[ans]);
    }
    return 0;
}