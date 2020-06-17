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

int T, A, S, B, label, ans, cnt;
int family[MAXT];
int dp[2][MAXN * MAXT];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d%d%d", &T, &A, &S, &B);
    for (int i = 0; i < A; ++i) {
        scanf("%d", &label);
        ++family[label];
    }
    cnt = 0;
    dp[0][0] = 1;
    for (int i = 1; i <= T; ++i) {
        memset(dp[i & 1], 0, MAXN * MAXT);
        dp[i & 1][0] = 1;
        cnt += family[i];
        for (int j = 1, bound = min(B, cnt); j <= bound; ++j) {
            if (j - 1 - family[i] >= 0)
                dp[i & 1][j] = (dp[i & 1][j - 1] + dp[(i - 1) & 1][j] - dp[(i - 1) & 1][j - 1 - family[i]] + MOD) % MOD;
            else
                dp[i & 1][j] = (dp[i & 1][j - 1] + dp[(i - 1) & 1][j]) % MOD;
        }
    }
    ans = 0;
    for (int j = S; j <= B; ++j) ans = (ans + dp[T & 1][j]) % MOD;
    printf("%d\n", ans);

    return 0;
}