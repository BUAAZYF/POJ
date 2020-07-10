#include <cstdio>

using namespace std;

const int MAX = 40005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, p, ans;
int port[MAX], dp[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    while(n-- > 0){
        scanf("%d", &p);
        ans = 0;
        for (int i = 0; i < p; ++i) scanf("%d", &port[i]);
        for(int i = 0; i < p; ++i) {
            dp[i] = 1;
            for(int j = 0; j < i; ++j){
                if (port[j] < port[i]) dp[i] = max(dp[i], dp[j] + 1);
            }
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }

    return 0;
}