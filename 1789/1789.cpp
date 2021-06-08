#include <cstdio>

using namespace std;

const int MAXC = 8;
const int MAXN = 2005;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) { return a <= b ? a : b; }

int N;
char trunks[MAXN][MAXC + 1];
int graph[MAXN][MAXN], mincost[MAXN];
bool used[MAXN];

int caldis(int x, int y) {
    int dis = 0;
    for (int i = 0; i < MAXC; ++i) dis += trunks[x][i] != trunks[y][i];
    return dis;
}

int prim() {
    for (int u = 0; u < N; ++u) {
        mincost[u] = INF;
        used[u] = false;
    }
    mincost[0] = 0;
    int ans = 0;
    while (true) {
        int v = -1;
        for (int u = 0; u < N; ++u)
            if (!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
        if (v == -1) break;
        used[v] = true;
        ans += mincost[v];
        for (int u = 0; u < N; ++u) mincost[u] = min(mincost[u], graph[u][v]);
    }
    return ans;
}

int main() {
    while (scanf("%d", &N) != EOF && N) {
        for (int i = 0; i < N; ++i) {
            scanf("%s", trunks[i]);
            graph[i][i] = INF;
        }
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j) graph[i][j] = graph[j][i] = caldis(i, j);
        printf("The highest possible quality is 1/%d.\n", prim());
    }
    return 0;
}