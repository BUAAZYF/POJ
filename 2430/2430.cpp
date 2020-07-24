#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 1010;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, K, B, M, ans;
Pr cows[MAX];
int dp[2][MAX][4];

struct col {
    int col_idx;
    bool row[3];
} cols[MAX];

void init_dp(int idx) {
    for (int i = 0; i <= K + 5; ++i)
        dp[idx][i][0] = dp[idx][i][1] = dp[idx][i][2] = dp[idx][i][3] = INF;
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d%d", &N, &K, &B);
    for (int i = 0; i < N; ++i)
        scanf("%d%d", &cows[i].second, &cows[i].first);
    if (K >= N) {
        printf("%d\n", N);
        return 0;
    }
    sort(cows, cows + N);
    M = 0;
    for (int i = 0; i < N; ++i) {
        if (M == 0 || cols[M - 1].col_idx != cows[i].first) {
            cols[M].col_idx = cows[i].first;
            cols[M].row[1] = cols[M].row[2] = false;
            cols[M].row[cows[i].second] = true;
            ++M;
        } else
            cols[M - 1].row[cows[i].second] = true;
    }
    init_dp(0);
    dp[0][K - 1][0] = 2;
    if (!cols[0].row[1])
        dp[0][K - 1][2] = 1;
    else if (!cols[0].row[2])
        dp[0][K - 1][1] = 1;
    if (cols[0].row[1] && cols[0].row[2] && K >= 2) dp[0][K - 2][3] = 2;
    for (int i = 1; i < M; ++i) {
        init_dp(i & 1);
        for (int j = K - 1; j >= 0; --j) {
            int minA = min(dp[(i + 1) & 1][j + 1][0], min(dp[(i + 1) & 1][j + 1][1], min(dp[(i + 1) & 1][j + 1][2], dp[(i + 1) & 1][j + 1][3])));
            int minB = min(dp[(i + 1) & 1][j + 2][0], min(dp[(i + 1) & 1][j + 2][1], min(dp[(i + 1) & 1][j + 2][2], dp[(i + 1) & 1][j + 2][3])));
            dp[i & 1][j][0] = dp[(i + 1) & 1][j][0] + 2 * (cols[i].col_idx - cols[i - 1].col_idx);
            dp[i & 1][j][0] = min(dp[i & 1][j][0], minA + 2);
            dp[i & 1][j][3] = dp[(i + 1) & 1][j][3] + 2 * (cols[i].col_idx - cols[i - 1].col_idx);
            dp[i & 1][j][3] = min(dp[i & 1][j][3], minB + 2);
            dp[i & 1][j][3] = min(dp[i & 1][j][3], dp[(i + 1) & 1][j + 1][1] + 1 + (cols[i].col_idx - cols[i - 1].col_idx));
            dp[i & 1][j][3] = min(dp[i & 1][j][3], dp[(i + 1) & 1][j + 1][2] + 1 + (cols[i].col_idx - cols[i - 1].col_idx));
            if (cols[i].row[1] && cols[i].row[2]) continue;
            for (int row = 1; row <= 2; ++row) {
                if (!cols[i].row[row]) continue;
                dp[i & 1][j][row] = dp[(i + 1) & 1][j][row] + (cols[i].col_idx - cols[i - 1].col_idx);
                dp[i & 1][j][row] = min(dp[i & 1][j][row], minA + 1);
                dp[i & 1][j][row] = min(dp[i & 1][j][row], dp[(i + 1) & 1][j][3] + (cols[i].col_idx - cols[i - 1].col_idx));
            }
        }
    }
    ans = INF;
    for (int j = 0; j <= K; ++j) {
        for (int r = 0; r < 4; ++r)
            ans = min(ans, dp[(M - 1) & 1][j][r]);
    }
    printf("%d\n", ans);

    return 0;
}