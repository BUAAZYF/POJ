#include <cstdio>

using namespace std;

const int MAXN = 35;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, maxn, dp[MAXN], A[MAXN], C[MAXN];

int main() {
    // freopen("in.txt", "r", stdin);
    dp[0] = 1, dp[1] = 0, dp[2] = 3;
    A[1] = 1, A[2] = 0;
    C[1] = 0, C[2] = 1;
    maxn = 2;
    while (scanf("%d", &n) != EOF && n != -1) {
        for (int i = maxn + 1; i <= n; ++i) {
            dp[i] = dp[i - 2] + 2 * A[i - 1];
            A[i] = dp[i - 1] + C[i - 1];
            C[i] = dp[i - 2] + C[i - 2];
        }
        maxn = max(maxn, n);
        printf("%d\n", dp[n]);
    }

    return 0;
}