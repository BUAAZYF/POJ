#include <cstdio>
#include <cstring>

using namespace std;

const int MAXW = 35;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

inline int min(int a, int b) {
    return a <= b ? a : b;
}

int T, W, apple, ans;
int dp[2][MAXW][2];

int main() {
    scanf("%d%d", &T, &W);
    memset(dp, 0, 2 * MAXW * 2);
    for (int i = 1; i <= T; ++i) {
        scanf("%d", &apple);
        --apple;
        for (int j = 0, bound = min(i, W + 1); j < bound; ++j) {
            if (j > 0) {
                dp[i & 1][j][0] = max(dp[(i - 1) & 1][j][0], dp[(i - 1) & 1][j - 1][1]) + int(apple == 0);
                dp[i & 1][j][1] = max(dp[(i - 1) & 1][j][1], dp[(i - 1) & 1][j - 1][0]) + int(apple == 1);
            } else {
                dp[i & 1][j][0] = dp[(i - 1) & 1][j][0] + int(apple == 0);
                dp[i & 1][j][1] = dp[(i - 1) & 1][j][1] + int(apple == 1);
            }
        }
    }
    ans = 0;
    for (int i = 0; i <= W; ++i) ans = max(ans, max(dp[T & 1][i][0], dp[T & 1][i][1]));
    printf("%d\n", ans);

    return 0;
}