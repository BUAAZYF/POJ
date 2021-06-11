#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 405;
const int T = 84;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int n, V, t, p, q;
vector<int> graph[MAX];
int matched[MAX];
bool used[MAX];

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
    while (scanf("%d", &n) != EOF) {
        V = n + T;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 0; i < n; ++i) {
            scanf("%d", &t);
            while (t--) {
                scanf("%d%d", &p, &q);
                add_edge(T + i, (p - 1) * 12 + (q - 1));
            }
        }
        printf("%d\n", bipartite_matching());
    }

    return 0;
}
