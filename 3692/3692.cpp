#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 500;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int G, B, M, V, t, u, v;
vector<int> graph[2 * MAX];
int matched[2 * MAX];
bool connect[MAX][MAX], used[2 * MAX];

void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool dfs(int v) {
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        int u = graph[v][i], w = matched[u];
        if (w < 0 || !used[w] && dfs(w)) {
            matched[v] = u;
            matched[u] = v;
            return true;
        }
    }
    return false;
}

int bipartite_matching() {
    int ans = 0;
    memset(matched, -1, sizeof(matched));
    for (int v = 0; v < V; ++v) {
        if (matched[v] >= 0) continue;
        memset(used, false, sizeof(used));
        if (dfs(v)) ++ans;
    }
    return ans;
}

int main() {
    t = 1;
    while (scanf("%d%d%d", &G, &B, &M) != EOF && G) {
        V = G + B;
        memset(connect, false, sizeof(connect));
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &u, &v);
            connect[u - 1][v - 1] = true;
        }
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 0; i < G; ++i)
            for (int j = 0; j < B; ++j)
                if (!connect[i][j]) add_edge(i, j + G);
        printf("Case %d: %d\n", t++, V - bipartite_matching());
    }

    return 0;
}