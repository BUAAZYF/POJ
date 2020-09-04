#include <cstdio>
#include <cstring>

using namespace std;

const int MAXV = 505;
const int MAXE = 5205;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int F, N, M, W, S, E, T, elen;
int dis[MAXV];
int graph[MAXV][MAXV];
struct edge{
    int from, to, cost;
    edge():from(0), to(0), cost(0){}
    edge(int f, int t, int c):from(f), to(t), cost(c){}
}edges[MAXE];

bool has_neg_cycle() {
    memset(dis, 0, sizeof(dis));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < elen; ++j) {
            edge e = edges[j];
            if (dis[e.to] > dis[e.from] + e.cost) {
                dis[e.to] = dis[e.from] + e.cost;
                if (i == N - 1) return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &F);
    while (F--) {
        scanf("%d%d%d", &N, &M, &W);
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) graph[i][j] = INF;
        }
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &S, &E, &T);
            graph[S][E] = min(graph[S][E], T);
            graph[E][S] = min(graph[E][S], T);
        }
        for (int i = 0; i < W; ++i) {
            scanf("%d%d%d", &S, &E, &T);
            graph[S][E] = min(graph[S][E], -T);
        }
        elen = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (graph[i][j] != INF) edges[elen++] = edge(i, j, graph[i][j]);
            }
        }
        printf("%s\n", has_neg_cycle() ? "YES" : "NO");
    }

    return 0;
}