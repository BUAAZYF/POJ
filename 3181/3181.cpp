#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1005;
const long long MOD = (long long)1E18;

int N, K;
long long dp_low[2][MAXN], dp_high[2][MAXN];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &N, &K);
    memset(dp_low, 0, 2 * MAXN);
    memset(dp_high, 0, 2 * MAXN);
    dp_low[0][0] = 1;
    for (int i = 1; i <= K; ++i) {
        dp_low[i & 1][0] = 1;
        for (int j = 1; j <= N; ++j) {
            if (j >= i) {
                dp_high[i & 1][j] = dp_high[(i - 1) & 1][j] + dp_high[i & 1][j - i] + (dp_low[(i - 1) & 1][j] + dp_low[i & 1][j - i]) / MOD;
                dp_low[i & 1][j] = (dp_low[(i - 1) & 1][j] + dp_low[i & 1][j - i]) % MOD;
            } else {
                dp_high[i & 1][j] = dp_high[(i - 1) & 1][j];
                dp_low[i & 1][j] = dp_low[(i - 1) & 1][j];
            }
        }
    }
    if (dp_high[K & 1][N] != 0) printf("%lld", dp_high[K & 1][N]);
    printf("%lld\n", dp_low[K & 1][N]);

    return 0;
}