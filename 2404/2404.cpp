#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 16;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, degree[MAX], graph[MAX][MAX], dp[1 << MAX - 1], odd[MAX], ans;

int main() {
    while (scanf("%d%d", &n, &m) != EOF && n) {
        memset(graph, 63, sizeof(graph));
        memset(degree, 0, sizeof(degree));
        ans = 0;
        for (int i = 1; i <= n; ++i) graph[i][i] = 0;
        int u, v, w;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            ++degree[u], ++degree[v];
            graph[u][v] = graph[v][u] = min(graph[u][v], w);
            ans += w;
        }
        for (int k = 1; k <= n; ++k)
            for (int i = 0; i <= n; ++i)
                for (int j = 1; j <= n; ++j) graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (degree[i] & 1) odd[++cnt] = i;
        memset(dp, 63, sizeof(dp));
        dp[0] = 0;
        int S = 1 << cnt;
        for (int s = 0; s < S; ++s) {
            int x = 1;
            while ((1 << x - 1) & s) ++x;
            for (int y = x + 1; y <= cnt; ++y)
                if (!(s & 1 << y - 1))
                    dp[s | (1 << x - 1) | (1 << y - 1)] = min(dp[s | (1 << x - 1) | (1 << y - 1)], dp[s] + graph[odd[x]][odd[y]]);
        }
        printf("%d\n", ans + dp[S - 1]);
    }

    return 0;
}