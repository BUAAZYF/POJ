#include <algorithm>
#include <climits>
#include <cstdio>

using namespace std;

const int MAX = 1005;

int n, a[MAX], ans;

int slove() {
    int t, ans = INT_MIN, pos;
    sort(a, a + n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == j) continue;
            for (int k = 0; k < j; ++k) {
                t = a[i] - a[j] - a[k];
                pos = lower_bound(a, a + n, t) - a;
                if (k < pos && pos < j && a[pos] == t) return a[i];
            }
        }
    }
    return INT_MIN;
}

int main() {
    while (scanf("%d", &n) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        if (n <= 3) {
            printf("no solution\n");
            continue;
        }
        ans = slove();
        if (ans == INT_MIN) printf("no solution\n");
        else printf("%d\n", ans);
    }

    return 0;
}