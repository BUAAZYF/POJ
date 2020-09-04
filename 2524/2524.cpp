#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 50002;

int t, n, m, x, y, ans;
int uni[MAX];

void init_uni() {
    for (int i = 1; i <= n; ++i) uni[i] = i;
}

int find(int x) {
    if (x == uni[x]) return x;
    else return uni[x] = find(uni[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    x > y ? uni[x] = y : uni[y] = x;
}

int main() {
    t = 1;
    while (scanf("%d%d", &n, &m) && n) {
        init_uni();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            merge(x, y);
        }
        ans = 0;
        for (int i = 1; i <= n; ++i) if (uni[i] == i) ++ans;
        printf("Case %d: %d\n", t++, ans);
    }

    return 0;
}