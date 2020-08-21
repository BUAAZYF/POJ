#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 105;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

const int cost[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};

char c;
int t, g1, g2, ans;
int gene1[MAX], gene2[MAX];
int dp[MAX][MAX];

int main() {
    scanf("%d", &t);
    while(t--){
        scanf("%d", &g1);
        getchar();
        for (int i = 0; i < g1; ++i) {
           c = getchar();
           if (c == 'A') gene1[i] = 0;
           else if (c == 'C') gene1[i] = 1;
           else if (c == 'G') gene1[i] = 2;
           else gene1[i] = 3;
        }
        gene1[g1] = 4;
        scanf("%d", &g2);
        getchar();
        for (int i = 0; i < g2; ++i) {
           c = getchar();
           if (c == 'A') gene2[i] = 0;
           else if (c == 'C') gene2[i] = 1;
           else if (c == 'G') gene2[i] = 2;
           else gene2[i] = 3;
        }
        gene2[g2] = 4;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= g1; ++i) dp[i][0] = dp[i - 1][0] + cost[4][gene1[i - 1]];
        for (int j = 1; j <= g2; ++j) dp[0][j] = dp[0][j - 1] + cost[4][gene2[j - 1]];
        for (int i = 1; i <= g1 + 1; ++i) {
            for (int j = 1; j <= g2 + 1; ++j) {
                dp[i][j] = max(dp[i - 1][j - 1] + cost[gene1[i - 1]][gene2[j - 1]], 
                max(dp[i - 1][j] + cost[4][gene1[i - 1]], dp[i][j - 1] + cost[4][gene2[j - 1]]));
            }
        }
        ans = max(dp[g1][g2], max(dp[g1 + 1][g2], dp[g1][g2 + 1]));
        printf("%d\n", ans);
    }

    return 0;
}