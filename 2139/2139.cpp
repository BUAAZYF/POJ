#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 305;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b){
    return a <= b ? a : b;
}

int N, M, n, x, y, ans;
int xs[MAXN];
bool mat[MAXN][MAXN];
int dp[MAXN][MAXN];

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        fill(*mat, *mat + MAXN * MAXN, false);
        fill(*dp, *dp + MAXN * MAXN, INF);
        for (int i = 0; i < M; ++i) {
            scanf("%d", &n);
            for(int i = 0;i < n; ++i) scanf("%d", &xs[i]);   
            for(int i = 0; i < n; ++i){
                x = xs[i];
                for(int j = i + 1; j < n; ++j){
                    y = xs[j];
                    mat[x][y] = mat[y][x] = true;
                    dp[x][y] = dp[y][x] = 1;
                }
            }
        }
        for(int k = 1; k <= N; ++k){
            for(int i = 1; i <= N; ++i){
                for(int j = 1; j <= N; ++j){
                    if(dp[i][k] != INF && dp[k][j] != INF)
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
        ans = INF;
        int cur;
        for(int i = 1; i <= N; ++i){
            cur = 0;
            for(int j = 1; j <= N; ++j){
                if(i != j && dp[i][j] != INF) cur += dp[i][j];
            }
            ans = min(ans, cur);
        }
        printf("%d\n", int(double(ans) / (N - 1) * 100));
    }

    return 0;
}