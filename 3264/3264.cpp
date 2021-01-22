#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 50005;
const int INF = 0x3f3f3f3f;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, Q, A, B, cows[MAX];
Pr ans, t[MAX * 4];

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) t[v] = Pr(a[tl], a[tl]);
    else {
        int tm = (tl + tr) / 2;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        t[v] = Pr(max(t[v * 2].first, t[v * 2 + 1].first), min(t[v * 2].second, t[v * 2 + 1].second));
    }
}

Pr query(int v, int tl, int tr, int l, int r) {
    if (l > r) return Pr(0, INF);
    if (l == tl && r == tr) return t[v];
    int tm = (tl + tr) / 2;
    Pr left = query(v * 2, tl, tm, l, min(r, tm)), right = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
    return Pr(max(left.first, right.first), min(left.second, right.second));
}

int main() {
    while (scanf("%d%d", &N, &Q) != EOF) {
        for (int i = 0; i < N; ++i) scanf("%d", &cows[i]);
        build(cows, 1, 0, N - 1);
        while (Q--) {
            scanf("%d%d", &A, &B);
            --A, --B;
            ans = query(1, 0, N - 1, A, B);
            printf("%d\n", ans.first - ans.second);
        }
    }

    return 0;
}