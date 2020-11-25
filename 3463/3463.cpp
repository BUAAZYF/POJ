#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1005;
const int MAXM = 10005;
const int INF = 0x3f3f3f3f;

int t, N, M, S, F, A, B, L;
int head[MAXM];
struct Edge {
    int v;
    int weight;
    int nxt;
} edge[MAXM];

int dijkstra() {
    int u, d, flag;
    bool used[MAXN][2];
    int dis[MAXN][2], cnt[MAXN][2];
    memset(used, false, sizeof(used));
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; ++i) dis[i][0] = dis[i][1] = INF;
    dis[S][0] = 0;
    cnt[S][0] = 1;
    while (true) {
        d = INF;
        u = 0;
        for (int v = 1; v <= N; ++v) {
            if (!used[v][0] && dis[v][0] < d)
                d = dis[v][0], u = v, flag = 0;
            else if (!used[v][1] && dis[v][1] < d)
                d = dis[v][1], u = v, flag = 1;
        }
        if (u == 0) break;
        used[u][flag] = true;
        for (int j = head[u]; j != -1; j = edge[j].nxt) {
            int v = edge[j].v;
            int w = edge[j].weight;
            if (dis[u][flag] + w < dis[v][0]) {
                dis[v][1] = dis[v][0];
                cnt[v][1] = cnt[v][0];
                dis[v][0] = dis[u][flag] + w;
                cnt[v][0] = cnt[u][flag];
            } else if (dis[u][flag] + w == dis[v][0]) {
                cnt[v][0] += cnt[u][flag];
            } else if (dis[u][flag] + w < dis[v][1]) {
                dis[v][1] = dis[u][flag] + w;
                cnt[v][1] = cnt[u][flag];
            } else if (dis[u][flag] + w == dis[v][1]) {
                cnt[v][1] += cnt[u][flag];
            }
        }
    }
    int ans = cnt[F][0];
    if (dis[F][1] - dis[F][0] == 1) ans += cnt[F][1];
    return ans;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &N, &M);
        memset(head, -1, sizeof(head));
        for (int i = 1; i <= M; ++i) {
            scanf("%d%d%d", &A, &B, &L);
            edge[i].v = B;
            edge[i].weight = L;
            edge[i].nxt = head[A];
            head[A] = i;
        }
        scanf("%d%d", &S, &F);
        printf("%d\n", dijkstra());
    }

    return 0;
}
