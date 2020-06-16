#include <cstdio>

using namespace std;

const int MAXN = 50005;

int N, K, D, X, Y, ans;
int uni[3 * MAXN];

int find(int x) {
    if (x == uni[x])
        return x;
    else
        return uni[x] = find(uni[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    x > y ? uni[x] = y : uni[y] = x;
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    scanf("%d%d", &N, &K);
    ans = 0;
    for (int i = 0; i <= 3 * N; ++i) uni[i] = i;
    while (K-- > 0) {
        scanf("%d%d%d", &D, &X, &Y);
        if (X <= 0 || X > N || Y <= 0 || Y > N || D == 2 && X == Y) {
            ++ans;
            continue;
        }
        --X, --Y;
        if (D == 1) {
            if (same(X, Y + N) || same(X, Y + 2 * N)) {
                ++ans;
            } else {
                merge(X, Y);
                merge(X + N, Y + N);
                merge(X + 2 * N, Y + 2 * N);
            }
        } else {
            if (same(X, Y) || same(X, Y + 2 * N)) {
                ++ans;
            } else {
                merge(X, Y + N);
                merge(X + N, Y + 2 * N);
                merge(X + 2 * N, Y);
            }
        }
    }
    printf("%d\n", ans);

    return 0;
}