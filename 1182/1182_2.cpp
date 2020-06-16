#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 50005;

int N, K, D, X, Y, ans;
int uni[MAXN], rel[MAXN];

int find(int x) {
    if (x == uni[x])
        return uni[x];
    else {
        int t = uni[x];
        uni[x] = find(t);
        rel[x] = (rel[x] + rel[t]) % 3;
        return uni[x];
    }
}

bool merge(int d, int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) {
        return (rel[x] - rel[y] + 3) % 3 + 1 == d;
    } else {
        uni[rx] = ry;
        rel[rx] = (d - rel[x] + rel[y] + 2) % 3;
        return true;
    }
}

int main() {
    scanf("%d%d", &N, &K);
    ans = 0;
    memset(rel, 0, N * sizeof(int));
    for (int i = 0; i < N; ++i) uni[i] = i;
    while (K-- > 0) {
        scanf("%d%d%d", &D, &X, &Y);
        if (X <= 0 || X > N || Y <= 0 || Y > N || D == 2 && X == Y) {
            ++ans;
            continue;
        }
        --X, --Y;
        if (!merge(D, X, Y)) ++ans;
    }
    printf("%d\n", ans);

    return 0;
}