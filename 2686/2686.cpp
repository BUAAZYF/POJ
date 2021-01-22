#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 10;
const int MAXM = 35;
const double INF = 0x3f3f3f3f3f3fLL;

int n, m, p, a, b, x, y, z, tickets[MAXN], mat[MAXM][MAXM];
double dp[1 << MAXN][MAXM], ans;

int main() {
    while (scanf("%d%d%d%d%d", &n, &m, &p, &a, &b) != EOF && n) {
        for (int i = 0; i < n; ++i) scanf("%d", &tickets[i]);
        fill(&mat[0][0], &mat[0][0] + MAXM * MAXM, -1);
        for (int i = 0; i < p; ++i) {
            scanf("%d%d%d", &x, &y, &z);
            --x, --y;
            mat[x][y] = mat[y][x] = z;
        }
        fill(&dp[0][0], &dp[0][0] + (1 << MAXN) * MAXM, INF);
        ans = INF;
        dp[(1 << n) - 1][a - 1] = 0;
        for (int S = (1 << n) - 1; S >= 0; --S) {
            ans = min(ans, dp[S][b - 1]);
            for (int v = 0; v < m; ++v) {
                for (int i = 0; i < n; ++i) {
                    if ((S >> i) & 1) {
                        for (int u = 0; u < m; ++u)
                            if (mat[v][u] >= 0) dp[S & ~(1 << i)][u] = min(dp[S & ~(1 << i)][u], dp[S][v] + double(mat[v][u]) / tickets[i]);
                    }
                }
            }
        }
        if (ans == INF) printf("Impossible\n");
        else printf("%.3f\n", ans);
    }

    return 0;
}