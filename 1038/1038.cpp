#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 155;
const int MAXS = 1025;

inline int max(int a, int b) {
    return a >= b ? a : b;
}

int D, N, M, K, S, x, y, ans;
int mask[MAXN];
int dp[2][MAXS][MAXS];

bool check23(int c, int x) {
    if (c + 2 < M) {
        x >>= c;
        if (!(x & 1)) return false;
        x >>= 1;
        if (!(x & 1)) return false;
        x >>= 1;
        if (!(x & 1)) return false;
        return true;
    }
    return false;
}

bool check32(int c, int x) {
    if (c + 1 < M) {
        x >>= c;
        if (!(x & 1)) return false;
        x >>= 1;
        if (!(x & 1)) return false;
        return true;
    }
    return false;
}

void dfs(int r, int c, int m1, int m2, int m3, int num) {
    if (c >= M) {
        dp[r][m1][m2] = max(dp[r][m1][m2], num);
        ans = max(ans, dp[r][m1][m2]);
        return;
    }
    int tm1, tm2, tm3;
    if (check23(c, m1 & m2)) {
        tm1 = m1;
        tm1 ^= (7 << c);
        tm2 = m2;
        tm2 ^= (7 << c);
        tm3 = m3;
        dfs(r, c + 3, tm1, tm2, tm3, num + 1);
    }
    if (check32(c, m1 & m2 & m3)) {
        tm1 = m1;
        tm1 ^= (3 << c);
        tm2 = m2;
        tm2 ^= (3 << c);
        tm3 = m3;
        tm3 ^= (3 << c);
        dfs(r, c + 2, tm1, tm2, tm3, num + 1);
    }
    dfs(r, c + 1, m1, m2, m3, num);
}

int main() {
    scanf("%d", &D);
    while (D--) {
        scanf("%d%d%d", &N, &M, &K);
        memset(mask, 0, sizeof(mask));
        memset(dp, -1, sizeof(dp));
        for (int i = 0; i < K; ++i) {
            scanf("%d%d", &x, &y);
            --y;
            mask[x] |= 1 << y;
        }
        ans = 0;
        S = 1 << M;
        mask[0] = S - 1;
        for (int i = 0; i < S; ++i)
            if (!(i & mask[1])) dp[0][i][0] = 0;
        int now = 1, last = 0;
        for (int i = 2; i <= N; ++i) {
            memset(dp[now], -1, sizeof(dp[now]));
            for (int j = 0; j < S; ++j) {
                if (j & mask[i - 1]) continue;
                for (int k = 0; k < S; ++k) {
                    if (k & mask[i - 2] || dp[last][j][k] == -1) continue;
                    x = (~mask[i]) & mask[0];
                    dfs(now, 0, x, j, k, dp[last][j][k]);
                }
            }
            now = 1 - now;
            last = 1 - last;
        }
        printf("%d\n", ans);
    }

    return 0;
}