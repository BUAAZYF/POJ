#include <cstdio>

using namespace std;

const int MAX = 355;

inline int max(int a, int b) {
    return a >= b ? a : b;
}
int n, val, ans;
int dp[2][MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        if (i == 1)
            scanf("%d", &dp[i & 1][0]);
        else {
            for (int j = 0; j < i; ++j) {
                scanf("%d", &val);
                if (j - 1 >= 0) dp[i & 1][j] = dp[(i - 1) & 1][j - 1];
                if (j < i - 1) dp[i & 1][j] = max(dp[i & 1][j], dp[(i - 1) & 1][j]);
                dp[i & 1][j] += val;
            }
        }
    }
    ans = 0;
    for (int i = 0; i < n; ++i) ans = max(ans, dp[n & 1][i]);
    printf("%d\n", ans);

    return 0;
}