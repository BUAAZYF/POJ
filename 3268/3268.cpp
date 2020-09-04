#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXV = 1005;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int N, M, X, x, y, d, ans;
int ingraph[MAXV][MAXV], outgraph[MAXV][MAXV];
int indis[MAXV], outdis[MAXV];
bool visited[MAXV];

void init_graph(int graph[MAXV][MAXV]) {
    for (int i = 1; i <= N; ++i) 
        for (int j = 1; j <= N; ++j) 
            graph[i][j] = INF;
}
int dijkstra(int s, int dis[MAXV], int graph[MAXV][MAXV]) {
    fill(dis, dis + N + 1, INF);
    fill(visited, visited + N + 1, false);
    dis[s] = 0;
    while (true) {
        int v = -1;
        for (int u = 1; u <= N; ++u) 
            if (!visited[u] && (v == -1 || dis[u] < dis[v])) v = u;
        if (v == -1) break;
        visited[v] = true;
        for (int u = 1; u <= N; ++u)
            dis[u] = min(dis[u], dis[v] + graph[v][u]);
    }
}

int main() {
    scanf("%d%d%d", &N, &M, &X);
    init_graph(ingraph);
    init_graph(outgraph);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &x, &y, &d);
        ingraph[x][y] = min(ingraph[x][y], d);
        outgraph[y][x] = min(outgraph[y][x], d);
    }

    dijkstra(X, indis, ingraph);
    dijkstra(X, outdis, outgraph);
    ans = 0;
    for (int i = 1; i <= N; ++i) ans = max(ans, indis[i] + outdis[i]);
    printf("%d\n", ans);

    return 0;
}