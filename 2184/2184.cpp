#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX = 100000;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, ans;
int s, f, csmax;
int dps[2 * MAX + 2];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    fill(dps, dps + 2 * MAX + 2, INT_MIN);
    dps[MAX] = 0;
    csmax = MAX;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &s, &f);
        if (s <= 0 && f <= 0) continue;
        if (s > 0) {
            for (int j = csmax; j >= 0; --j)
                if (dps[j] != INT_MIN) dps[j + s] = max(dps[j + s], f + dps[j]);
            csmax += s;
        } else {
            for (int j = -s; j <= csmax; ++j)
                if (dps[j] != INT_MIN) dps[j + s] = max(dps[j + s], f + dps[j]);
        }
    }
    ans = 0;
    for (int i = MAX; i <= csmax; ++i)
        if (dps[i] >= 0 && i + dps[i] - MAX > ans) ans = i + dps[i] - MAX;
    printf("%d\n", ans);

    return 0;
}