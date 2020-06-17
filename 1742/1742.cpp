#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXM = 100005;
const int MAXN = 105;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, ans;
int dp[2][MAXM];
int value[MAXN], cnt[MAXN];

int main() {
    while (scanf("%d%d", &n, &m) != EOF && n != 0) {
        for (int i = 0; i < n; ++i) scanf("%d", &value[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &cnt[i]);
        if (m <= 0) {
            printf("\n");
            continue;
        }
        for (int i = 0; i < n; ++i) {
            fill(dp[i & 1], dp[i & 1] + MAXM, -1);
            for (int j = 0, bound = min(cnt[i], m / value[i]); j <= bound; ++j)
                dp[i & 1][value[i] * j] = cnt[i] - j;
            if (i == 0) continue;
            for (int j = 1; j <= m; ++j) {
                if (dp[(i + 1) & 1][j] >= 0) {
                    dp[i & 1][j] = cnt[i];
                    continue;
                }
                if (j >= value[i] && dp[i & 1][j - value[i]] > 0) dp[i & 1][j] = max(dp[i & 1][j], dp[i & 1][j - value[i]] - 1);
            }
        }
        ans = 0;
        for (int i = 1; i <= m; ++i) {
            if (dp[(n + 1) & 1][i] >= 0) ++ans;
        }
        printf("%d\n", ans);
    }

    return 0;
}