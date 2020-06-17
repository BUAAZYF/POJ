#include <cstdio>
#include <cstring>

using namespace std;

const int MAXT = 1005;
const int MAXN = 105;
const int MOD = 1000000;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

inline int min(int a, int b) {
    return a <= b ? a : b;
}

int T, A, S, B, label, ans;
int family[MAXT];
int dp[2][MAXN * MAXT];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d%d%d", &T, &A, &S, &B);
    for (int i = 0; i < A; ++i) {
        scanf("%d", &label);
        ++family[label];
    }
    for (int i = 1; i <= T; ++i) {
        memset(dp[i & 1], 0, MAXN * MAXT);
        for (int j = 1; j <= B; ++j) {
            if (j <= family[i]) dp[i & 1][j] = 1;
            dp[i & 1][j] += dp[(i - 1) & 1][j];
            for (int k = 1, bound = min(family[i], j); k <= bound; ++k)
                dp[i & 1][j] = (dp[i & 1][j] + dp[(i - 1) & 1][j - k]) % MOD;
        }
    }
    ans = 0;
    for (int j = S; j <= B; ++j) ans = (ans + dp[T & 1][j]) % MOD;
    printf("%d\n", ans);

    return 0;
}