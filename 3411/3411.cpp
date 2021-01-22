#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 10;
const int INF = 0x3f3f3f3f;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int n, m, ans, visited[MAX];
struct road {
    int a, b, c, p, r;
} roads[MAX];

void dfs(int node, int state, int cost) {
    if (visited[node] > 4 || cost >= ans) return;
    if (node == n) {
        ans = min(ans, cost);
        return;
    }
    state |= (1 << node);
    for (int i = 0; i < m; ++i) {
        if (roads[i].a != node) continue;
        ++visited[roads[i].b];
        if ((state >> roads[i].c) & 1) dfs(roads[i].b, state, cost + roads[i].p);
        dfs(roads[i].b, state, cost + roads[i].r);
        --visited[roads[i].b];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d%d%d", &roads[i].a, &roads[i].b, &roads[i].c, &roads[i].p, &roads[i].r);
    memset(visited, 0, sizeof(visited));
    ans = INF;
    dfs(1, 0, 0);
    if (ans == INF) printf("impossible\n");
    else printf("%d\n", ans);

    return 0;
}