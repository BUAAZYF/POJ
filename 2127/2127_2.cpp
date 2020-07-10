#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 505;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int N, M;
int a[MAX], b[MAX], ans_idx;
int ans[MAX];
int dp[MAX][MAX];
int pre[MAX][MAX];

void cal_ans(int x, int y, int idx) {
    int k;
    if (x > 1) {
        if (dp[x][y] == dp[x - 1][y])
            cal_ans(x - 1, y, idx);
        else {
            for (k = x - 1; k >= 1; --k)
                if (b[k] < b[y] && dp[x - 1][k] == dp[x][y] - 1) break;
            cal_ans(x - 1, k, idx - 1);
            ans[idx] = b[y];
        }
    } else if (dp[1][y] == 1)
        ans[idx] = b[y];
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", &a[i]);
    scanf("%d", &M);
    for (int i = 1; i <= M; ++i) scanf("%d", &b[i]);
    memset(dp, 0, sizeof(dp));
    memset(pre, 0, sizeof(pre));
    for (int i = 1, curmax, last; i <= N; ++i) {
        curmax = 0, last = 0;
        for (int j = 1; j <= M; ++j) {
            if (a[i] == b[j]) {
                dp[i][j] = curmax + 1;
                pre[i][j] = last;
            } else
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            if (b[j] < a[i] && curmax < dp[i - 1][j]) {
                curmax = dp[i - 1][j];
                last = j;
            }
        }
    }
    int ans_cnt = -1, x = N, y, p = 0;
    for (int j = 1; j <= N; ++j)
        for (int i = 1; i <= M; ++i)
            if (ans_cnt < dp[j][i]) {
                ans_cnt = dp[j][i];
                y = i;
            }
    printf("%d\n", ans_cnt);

    while (ans_cnt-- > 0) {
        ans[++p] = b[y];
        while (a[x] != b[y]) --x;
        y = pre[x][y];
        --x;
    }
    for (int i = p; i >= 1; --i) printf("%d ", ans[i]);

    return 0;
}