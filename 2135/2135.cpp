#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const int MAXM = 10005;
const int INF = 0x3f3f3f3f;

int N, M, A, B, L, ans;
vector<int> graph[MAXN][MAXN];
bool used[MAXN];
int dis[MAXN], pre[MAXN];

int dijkstra(int t) {
    memset(used, false, sizeof(used));
    memset(pre, 0, sizeof(pre));
    for (int i = 1; i <= N; ++i) dis[i] = INF;
    dis[1] = 0;
    while (true) {
        int v = 0;
        for (int u = 1; u <= N; ++u)
            if (!used[u] && (v == 0 || dis[u] < dis[v])) v = u;
        if (v == 0) break;
        used[v] = true;
        for (int u = 1; u <= N; ++u) {
            if (!graph[v][u].empty() && dis[u] > dis[v] + graph[v][u][0]) {
                dis[u] = dis[v] + graph[v][u][0];
                pre[u] = v;
            }
        }
    }
    if (t == 0) {
        int v = N;
        while (pre[v] != 0) {
            graph[v][pre[v]].push_back(-graph[v][pre[v]][0]);
            sort(graph[v][pre[v]].begin(), graph[v][pre[v]].end());
            v = pre[v];
        }
    }
    return dis[N];
}

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; ++i) {
        scanf("%d%d%d", &A, &B, &L);
        graph[A][B].push_back(L);
        graph[B][A].push_back(L);
    }
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            sort(graph[i][j].begin(), graph[i][j].end());
    ans = 0;
    ans += dijkstra(0);
    ans = ans * 2 + dijkstra(1);
    printf("%d\n", ans);

    return 0;
}
