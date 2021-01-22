#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 22;

int N, M, P, dp[2][1 << MAX], ans;

int main() {
    scanf("%d%d", &N, &M);
    ++M;
    memset(dp, 0, sizeof(dp));
    for (int i = 0, j, s; i < N; ++i) {
        scanf("%d", &P);
        while (P--) {
            scanf("%d", &j);
            if (i == 0) {
                dp[0][1 << j] = 1;
                continue;
            }
            s = (1 << (i + 1)) - 1;
            while (s < 1 << M) {
                if (s >> j && 1) dp[i & 1][s] += dp[(i + 1) & 1][s & ~(1 << j)];
                int x = s & -s, y = s + x;
                s = ((s & ~y) / x >> 1) | y;
            }
        }
    }
    ans = 0;
    int s = (1 << N) - 1;
    while (s < 1 << M) {
        ans += dp[(N - 1) & 1][s];
        int x = s & -s, y = s + x;
        s = ((s & ~y) / x >> 1) | y;
    }
    printf("%d\n", ans);

    return 0;
}