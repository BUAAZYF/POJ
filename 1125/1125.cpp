#include <algorithm>
#include <cstdio>

using namespace std;

const int MAX = 105;
const int INF = 0x3f3f3f3f;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int n, m, dst, cost, src;
int dis[MAX][MAX];

int main() {
    while (scanf("%d", &n) != EOF && n) {
        fill(&dis[0][0], &dis[0][0] + MAX * MAX, INF);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &m);
            while (m--) {
                scanf("%d%d", &dst, &cost);
                dis[i][dst] = cost;
            }
        }
        for (int i = 1; i <= n; ++i) dis[i][i] = 0;
        for (int k = 1; k <= n; ++k)
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        src = -1, cost = INF;
        for (int i = 1; i <= n; ++i) {
            int curmin = 0;
            for (int j = 1; j <= n; ++j) curmin = max(curmin, dis[i][j]);
            if (curmin < cost) src = i, cost = curmin;
        }
        if (src == -1) printf("disjoint\n");
        else printf("%d %d\n", src, cost);
    }

    return 0;
}