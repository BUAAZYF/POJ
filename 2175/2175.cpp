#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 105;
const int MAXV = 210;
const int INF = 0x3f3f3f3f;

struct point {
    int x, y, cap;
};

int N, M, V, cost;
point buildings[MAXN], shelters[MAXN];
int E[MAXN][MAXN], prevv[MAXV][MAXV], graph[MAXV][MAXV];
bool used[MAXV];

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        V = N + M + 1;
        fill(&graph[0][0], &graph[0][0] + MAXV * MAXV, INF);
        for (int i = 0; i < N; ++i) scanf("%d%d%d", &buildings[i].x, &buildings[i].y, &buildings[i].cap);
        for (int j = 0; j < M; ++j) scanf("%d%d%d", &shelters[j].x, &shelters[j].y, &shelters[j].cap);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) scanf("%d", &E[i][j]);
        for (int j = 0; j < M; ++j) {
            int cs = 0;
            for (int i = 0; i < N; ++i) {
                cost = abs(buildings[i].x - shelters[j].x) + abs(buildings[i].y - shelters[j].y) + 1;
                graph[i][N + j] = cost;
                if (E[i][j] > 0) graph[N + j][i] = -cost;
                cs += E[i][j];
            }
            if (cs > 0) graph[N + M][N + j] = 0;
            if (cs < shelters[j].cap) graph[N + j][N + M] = 0;
        }
        for (int i = 0; i < V; ++i)
            for (int j = 0; j < V; ++j) prevv[i][j] = i;
        bool issub = false;
        for (int k = 0; k < V; ++k) {
            if (issub) break;
            for (int i = 0; i < V; ++i) {
                if (issub) break;
                for (int j = 0; j < V; ++j) {
                    if (graph[i][j] > graph[i][k] + graph[k][j]) {
                        graph[i][j] = graph[i][k] + graph[k][j];
                        prevv[i][j] = prevv[k][j];
                        if (i == j && graph[i][i] < 0) {
                            issub = true;
                            fill(used, used + V, false);
                            for (int v = i; !used[v]; v = prevv[i][v]) {
                                used[v] = true;
                                if (v != N + M && prevv[i][v] != N + M) {
                                    if (v >= N) ++E[prevv[i][v]][v - N];
                                    else --E[v][prevv[i][v] - N];
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }
        if (issub) {
            printf("SUBOPTIMAL\n");
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < M; ++j) printf("%d%c", E[i][j], j == M ? '\n' : ' ');
        } else printf("OPTIMAL\n");
    }
    return 0;
}