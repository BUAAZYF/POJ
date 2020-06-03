#include <cmath>
#include <cstdio>

using namespace std;

int main() {
    int n;
    long long m;
    while (scanf("%d %lld", &n, &m)) {
        if (n == -1) break;
        int ans[n];
        long long k = (long long)((sqrt(1 + 8 * m) - 1) / 2);
        ans[n - 1 - k] = n;
        m -= k * (k + 1) / 2;
        if (n - 2 - k >= 0) {
            ans[n - 2 - k] = n - 1 - k + m;
            int cur = n - 1;
            for (int i = n - k; i < n; ++i) {
                if (cur == ans[n - 2 - k]) --cur;
                ans[i] = cur;
                --cur;
            }
        }
        for (int i = 0; i < n - 2 - k; ++i) ans[i] = i + 1;
        for (int i = 0; i < n - 1; ++i) printf("%d ", ans[i]);
        printf("%d\n", ans[n - 1]);
    }

    return 0;
}