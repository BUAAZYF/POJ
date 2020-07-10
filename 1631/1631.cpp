#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 40005;
const int INF = 0x3f3f3f3f;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, p, port;
int dp[MAX];

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    while(n-- > 0){
        scanf("%d", &p);
        fill(dp, dp + p, INF);
        for(int i = 0; i < p; ++i) {
            scanf("%d", &port);
            *lower_bound(dp, dp + p, port) = port;
        }
        printf("%d\n", int(lower_bound(dp, dp + p, INF) - dp));
    }

    return 0;
}