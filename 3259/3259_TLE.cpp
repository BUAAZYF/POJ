#include <cstdio>

using namespace std;

const int MAX = 505;
const int INF = 0x3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int F, N, M, W, S, E, T;
int dp[MAX][MAX];
bool neg_cycle;

int main() {
    scanf("%d", &F);
    while (F--) {
        scanf("%d%d%d", &N, &M, &W);
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) dp[i][j] = INF;
            dp[i][i] = 0;
        }
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &S, &E, &T);
            dp[S][E] = min(dp[S][E], T);
            dp[E][S] = min(dp[E][S], T);
        }
        for (int i = 0; i < W; ++i) {
            scanf("%d%d%d", &S, &E, &T);
            dp[S][E] = min(dp[S][E], -T);
        }
        for (int k = 1; k <= N; ++k) 
            for (int i = 1; i <= N; ++i) 
                for (int j = 1; j <= N; ++j)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        neg_cycle = false;
        for (int i = 1; i <= N; ++i) {
            if (dp[i][i] < 0) {
                neg_cycle = true; 
                break;
            }
        }
        printf("%s\n", neg_cycle ? "YES" : "NO");
    }

    return 0;
}