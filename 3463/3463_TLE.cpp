#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 1005;
const int INF = 0x3f3f3f3f;

struct edge {
    int l1, l2, t1, t2;
    void reset() {
        l1 = l2 = INF;
        t1 = t2 = 0;
    }
} mat[MAX][MAX];

int t, N, M, A, B, L, S, F, mindis, ans;
int dis[MAX];
bool used[MAX];
vector<int> graph[MAX];

int inline min(int a, int b) {
    return a <= b ? a : b;
}

void dfs(int node, int cnt, int path, int threshold) {
    if (path <= threshold && F == node) {
        ans += cnt;
        return;
    }
    if (path >= threshold) return;
    for (int i = 0; i < graph[node].size(); ++i) {
        if (used[graph[node][i]]) continue;
        used[graph[node][i]] = true;
        dfs(graph[node][i], cnt * mat[node][graph[node][i]].t1, path + mat[node][graph[node][i]].l1, threshold);
        dfs(graph[node][i], cnt * mat[node][graph[node][i]].t2, path + mat[node][graph[node][i]].l2, threshold);
        used[graph[node][i]] = false;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &N, &M);
        for (int i = 0; i < N; ++i) {
            graph[i].clear();
            for (int j = 0; j < N; ++j) mat[i][j].reset();
        }
        for (int i = 0; i < M; ++i) {
            scanf("%d%d%d", &A, &B, &L);
            --A; --B;
            if (mat[A][B].l1 == INF) {
                graph[A].push_back(B);
                mat[A][B].l1 = L;
                mat[A][B].t1 = 1;
            } else if (L < mat[A][B].l1) {
                mat[A][B].l2 = mat[A][B].l1;
                mat[A][B].t2 = mat[A][B].t1;
                mat[A][B].l1 = L;
                mat[A][B].t1 = 1;
            } else if (L < mat[A][B].l2) {
                mat[A][B].l2 = L;
                mat[A][B].t2 = 1;
            } else if (L == mat[A][B].l1) {
                ++mat[A][B].t1;
            } else if (L == mat[A][B].l2) {
                ++mat[A][B].t2;
            }
        }
        scanf("%d%d", &S, &F);
        --S; --F;
        fill(dis, dis + N, INF);
        fill(used, used + N, false);
        dis[S] = 0;
        while (true) {
            int v = -1;
            for (int u = 0; u < N; ++u)
                if (!used[u] && (v == -1 || dis[u] < dis[v])) v = u;
            if (v == -1) break;
            used[v] = true;
            for (int u = 0; u < N; ++u) dis[u] = min(dis[u], dis[v] + mat[v][u].l1);
        }
        mindis = dis[F] + 1;
        ans = 0;
        fill(used, used + N, false);
        used[S] = true;
        dfs(S, 1, 0, mindis);
        printf("%d\n", ans);
    }

    return 0;
}