#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 13;
const int MOD = 100000000;

int N, M, x, ans, dp[MAX][1 << MAX];
bool canform, fields[MAX][MAX];

bool hascontinuousone(int x) {
    return (x & (x << 1)) > 0;
}

void caldp(int idx, int cs) {
    for (int ls = 1; ls < 1 << N; ++ls) {
        if (hascontinuousone(ls) || cs & ls) continue;
        dp[idx][cs] = (dp[idx][cs] + dp[idx - 1][ls]) % MOD;
    }
    for (int ls = 1; ls < 1 << N; ++ls) {
        for (int j = idx - 2; j >= 0; --j) dp[idx][cs] = (dp[idx][cs] + dp[j][ls]) % MOD;
    }
}

int main() {
    while (scanf("%d%d", &M, &N) != EOF) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &x);
                fields[i][j] = x;
            }
        }
        memset(dp, 0, sizeof(dp));
        ans = 1;
        for (int i = 0; i < M; ++i) {
            for (int s = 1; s < 1 << N; ++s) {
                if (hascontinuousone(s)) continue;
                canform = true;
                for (int j = 0; j < N; ++j) {
                    if (!fields[i][j] && (s >> j) & 1) {
                        canform = false;
                        break;
                    }
                }
                if (canform) {
                    dp[i][s] = 1;
                    if (i > 0) caldp(i, s);
                }
            }
            for (int s = 1; s < 1 << N; ++s) ans = (ans + dp[i][s]) % MOD;
        }
        printf("%d\n", ans);
    }

    return 0;
}