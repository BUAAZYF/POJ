#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 55;
const int INF = (1 << 30);

double inline max(int a, int b) {
    return a >= b ? a : b;
}

double inline min(int a, int b) {
    return a <= b ? a : b;
}

struct coord {
    int x, y;
} coords[MAX];

int t, n;
int dp[MAX][MAX];

inline int multiply(int x, int y) {
    return coords[x].x * coords[y].y - coords[x].y * coords[y].x;
}

inline int area(int i, int j, int k) {
    int size = multiply(i, j) + multiply(j, k) + multiply(k, i);
    return size > 0 ? size : (-size);
}

inline bool judge(int i, int j, int k) {
    int size = area(i, j, k);
    for (int t = 0; t < n; ++t) {
        if (t == i || t == j || t == k) continue;
        if (size == area(i, j, t) + area(i, k, t) + area(j, k, t)) return false;
    }
    return true;
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) scanf("%d%d", &coords[i].x, &coords[i].y);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i <= n - 3; ++i) dp[i][i + 2] = area(i, i + 1, i + 2);
        for (int step = 3; step < n; ++step) {
            for (int i = 0; i < n - step; ++i) {
                int j = i + step;
                dp[i][j] = INF;
                if(judge(i, i + 1, j))
                    dp[i][j] = min(dp[i][j], max(area(i, i + 1, j), dp[i + 1][j]));
                if(judge(i, j - 1, j))
                    dp[i][j] = min(dp[i][j], max(area(i, j - 1, j), dp[i][j - 1]));
                for (int k = i + 2; k < j - 1; ++k) {
                    if (!judge(i, k, j)) continue;
                    dp[i][j] = min(dp[i][j], max(area(i, k, j), max(dp[i][k], dp[k][j])));
                }
            }
        }
        printf("%d", dp[0][n - 1] / 2);
        if (dp[0][n - 1] & 1) printf(".5\n");
        else printf(".0\n");
    }

    return 0;
}