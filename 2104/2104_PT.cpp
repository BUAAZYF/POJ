#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 100005;
const int DEPTH = 18;

int N, Q, cnt, x, y, k, a[MAX];
int t[DEPTH][MAX], left[DEPTH][MAX];

void build(int l, int r, int d) {
    if (l == r) return;
    int mid = (l + r) >> 1, lp = l, rp = mid + 1;
    for (int i = l; i <= r; ++i) {
        if (t[d][i] <= a[mid]) t[d + 1][lp++] = t[d][i];
        else t[d + 1][rp++] = t[d][i];
        left[d][i] = left[d][l - 1] + lp - l;
    }
    build(l, mid, d + 1);
    build(mid + 1, r, d + 1);
}

int query(int L, int R, int l, int r, int d, int k) {
    if (l == r) return t[d][l];
    int mid = (L + R) >> 1, cnt = left[d][r] - left[d][l - 1];
    int nl, nr;
    if (cnt >= k) {
        nl = L + left[d][l - 1] - left[d][L - 1];
        nr = nl + cnt - 1;
        return query(L, mid, nl, nr, d + 1, k);
    } else {
        nr = r + left[d][R] - left[d][r];
        nl = nr - (r - l - cnt);
        return query(mid + 1, R, nl, nr, d + 1, k - cnt);
    }
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &t[0][i]);
        a[i] = t[0][i];
    }
    sort(a + 1, a + 1 + N);
    build(1, N, 0);
    while (Q--) {
        scanf("%d%d%d", &x, &y, &k);
        printf("%d\n", query(1, N, x, y, 0, k));
    }
    return 0;
}