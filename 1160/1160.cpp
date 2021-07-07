#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXV = 305;
const int MAXP = 35;

int inline min(int x, int y) { return x <= y ? x : y; }

int V, P, villages[MAXV], presum[MAXV], dp[MAXV][MAXP], ans;

int main() {
    while (scanf("%d%d", &V, &P) != EOF) {
        memset(dp, 0, sizeof(dp));
        memset(presum, 0, sizeof(presum));
        for (int i = 0; i < V; ++i) {
            scanf("%d", &villages[i]);
            presum[i + 1] = presum[i] + villages[i];
        }
        for (int i = 0; i < V; ++i) {
            dp[i][1] = villages[i] * i - presum[i];
            for (int j = 0; j < i; ++j) {
                for (int k = 2; k <= min(P, j + 1); ++k) {
                    int t = upper_bound(villages, villages + V, (villages[i] + villages[j]) / 2) - villages - 1;
                    int cur = dp[j][k - 1];
                    if (j + 1 <= t) cur += presum[t + 1] - presum[j + 1] - (t - j) * villages[j];
                    if (t + 1 <= i - 1) cur += (i - t - 1) * villages[i] - (presum[i] - presum[t + 1]);
                    if (dp[i][k] == 0) dp[i][k] = cur;
                    else dp[i][k] = min(dp[i][k], cur);
                }
            }
        }
        ans = dp[V - 1][P];
        for (int i = P - 1; i < V - 1; ++i) {
            int cur = dp[i][P];
            for (int t = i + 1; t < V; ++t) cur += villages[t] - villages[i];
            ans = min(ans, cur);
        }
        printf("%d\n", ans);
    }

    return 0;
}