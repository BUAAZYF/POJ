#include <cstdio>

using namespace std;

const int MAX = 1000005 / 2;
const int MOD = 1000000000;

int n, ans;
int dp[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    if (n == 1)
        ans = 1;
    else if (n <= 3)
        ans = 2;
    else if (n <= 5)
        ans = 4;
    else {
        n /= 2;
        dp[1] = 2;
        dp[2] = 4;
        for (int i = 3; i <= n; ++i) dp[i] = (dp[i - 1] + dp[i / 2]) % MOD;
        ans = dp[n];
    }
    printf("%d\n", ans);

    return 0;
}