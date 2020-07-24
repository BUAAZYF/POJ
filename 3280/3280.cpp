#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 2005;
const int ALPHA = 26;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, M, ac, dc;
char c, tags[MAX];
int cost[ALPHA];
int dp[MAX][MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d\n", &N, &M);
    for (int i = 0; i < M; ++i) scanf("%c", &tags[i]);
    getchar();
    for (int i = 0; i < N; ++i) {
        scanf("%c%d%d\n", &c, &ac, &dc);
        cost[c - 'a'] = min(ac, dc);
    }
    memset(dp, 0, sizeof(dp));
    for (int step = 1; step < M; ++step) {
        for (int i = 0; i < M - step; ++i) {
            dp[i][i + step] = min(dp[i][i + step - 1] + cost[tags[i + step] - 'a'], dp[i + 1][i + step] + cost[tags[i] - 'a']);
            if (tags[i] == tags[i + step]) dp[i][i + step] = min(dp[i][i + step], dp[i + 1][i + step - 1]);
        }
    }
    printf("%d\n", dp[0][M - 1]);

    return 0;
}