#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 510;
const int INF = 0x3f3f3f3f;

int min(int a, int b) {
    return a <= b ? a : b;
}

int N, M, graph[MAX][MAX];
int v[MAX], w[MAX];
bool visited[MAX];

int stoer_wagner() {
    int mincut = INF;
    for (int i = 0; i < N; ++i) v[i] = i;
    while (N > 1) {
        int pre = 0;
        memset(visited, 0, sizeof(visited));
        memset(w, 0, sizeof(w));
        for (int i = 1; i < N; ++i) {
            int k = -1;
            for (int j = 1; j < N; ++j) {
                if (!visited[v[j]]) {
                    w[v[j]] += graph[v[pre]][v[j]];
                    if (k == -1 || w[v[k]] < w[v[j]]) {
                        k = j;
                    }
                }
            }
            visited[v[k]] = true;
            if (i == N - 1) {
                const int s = v[pre], t = v[k];
                mincut = min(mincut, w[t]);
                for (int j = 0; j < N; ++j) {
                    graph[s][v[j]] += graph[v[j]][t];
                    graph[v[j]][s] += graph[v[j]][t];
                }
                v[k] = v[--N];
            }
            pre = k;
        }
    }
    return mincut;
}

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        memset(graph, 0, sizeof(graph));
        while (M--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            graph[u][v] += w;
            graph[v][u] += w;
        }
        printf("%d\n", stoer_wagner());
    }
    return 0;
}