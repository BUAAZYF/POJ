#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 505;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, uid, M, nei;
char c;
vector<int> graph[2 * MAX];
int matched[2 * MAX];
bool used[2 * MAX];

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
    for (int v = 0; v < N; ++v) {
        if (matched[v] >= 0) continue;
        memset(used, false, sizeof(used));
        if (dfs(v)) ++ans;
    }
    return ans;
}

int main() {
    while (scanf("%d", &N) != EOF) {
        for (int i = 0; i < MAX; ++i) graph[i].clear();
        for (int i = 0; i < N; ++i) {
            scanf("%d: (%d)", &uid, &M);
            for (int j = 0; j < M; ++j) {
                scanf("%d", &nei);
                graph[uid].push_back(nei);
            }
        }
        printf("%d\n", N - bipartite_matching());
    }

    return 0;
}