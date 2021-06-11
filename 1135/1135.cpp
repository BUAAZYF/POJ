#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAXV = 505;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int t, N, M, x, y, cost;
int idx, idx1, idx2;
double max1, max2;
int mat[MAXV][MAXV];
int dis[MAXV];
vector<Pr> graph[MAXV];

void dijkstra(int s) {
    fill(dis, dis + N + 1, INF);
    dis[s] = 0;
    priority_queue<Pr, vector<Pr>, greater<Pr> > pq;
    pq.push(Pr(0, s));
    while (!pq.empty()) {
        Pr cur = pq.top();
        pq.pop();
        int v = cur.second;
        if (dis[v] < cur.first) continue;
        for (int i = 0; i < graph[v].size(); ++i) {
            Pr& e = graph[v][i];
            if (dis[e.first] > dis[v] + e.second) {
                dis[e.first] = dis[v] + e.second;
                pq.push(Pr(dis[e.first], e.first));
            }
        }
    }
}

int main() {
    t = 1;
    while (scanf("%d%d", &N, &M) != EOF && N + M != 0) {
        fill(&mat[0][0], &mat[0][0] + MAXV * MAXV, INF);
        for (int i = 1; i <= N; ++i) graph[i].clear();
        while (M--) {
            scanf("%d%d%d", &x, &y, &cost);
            graph[x].push_back(Pr(y, cost));
            graph[y].push_back(Pr(x, cost));
            mat[x][y] = mat[y][x] = min(mat[x][y], cost);
        }
        dijkstra(1);
        max1 = -1;
        for (int i = 1; i <= N; ++i)
            if (dis[i] > max1) {
                max1 = dis[i];
                idx = i;
            }
        max2 = -1;
        for (int i = 1; i <= N; ++i)
            for (int j = i + 1; j <= N; ++j)
                if (mat[i][j] != INF && max2 < (dis[i] + dis[j] + mat[i][j]) / 2.0) {
                    max2 = (dis[i] + dis[j] + mat[i][j]) / 2.0;
                    idx1 = i, idx2 = j;
                }
        printf("System #%d\n", t++);
        if (max1 >= max2) printf("The last domino falls after %0.1f seconds, at key domino %d.\n\n", max1, idx);
        else printf("The last domino falls after %.1f seconds, between key dominoes %d and %d.\n\n", max2, idx1, idx2);
    }

    return 0;
}