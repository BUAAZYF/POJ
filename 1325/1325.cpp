#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 205;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int N, M, P, V, job, x, y;
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
    for (int v = 0; v < V; ++v) {
        if (matched[v] >= 0) continue;
        memset(used, false, sizeof(used));
        if (dfs(v)) ++ans;
    }
    return ans;
}

int main() {
    while (scanf("%d", &N) != EOF && N) {
        scanf("%d%d", &M, &P);
        V = M + N;
        for (int i = 0; i < V; ++i) graph[i].clear();
        while (P--) {
            scanf("%d%d%d", &job, &x, &y);
            if (x * y != 0) add_edge(x, N + y);
        }
        printf("%d\n", bipartite_matching());
    }

    return 0;
}
