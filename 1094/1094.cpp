#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 27;

int n, m, indegree[MAX];
char a, b, ans[MAX];
bool finished, graph[MAX][MAX], reachable[MAX], visited[MAX];

void dfs(int node) {
    reachable[node] = true;
    for (int i = 0; i < n; ++i)
        if (graph[node][i] && !reachable[i]) dfs(i);
}

bool uniquetoglogicalsort() {
    int degree[MAX];
    memcpy(degree, indegree, sizeof(indegree));
    int src;
    for (int k = 0; k < n; ++k) {
        src = -1;
        for (int i = 0; i < n; ++i) {
            if (degree[i] == 0) {
                if (src != -1) return false;
                src = i;
            }
        }
        if (src == -1) return false;
        degree[src] = -1;
        for (int i = 0; i < n; ++i)
            if (graph[src][i]) --degree[i];
        ans[k] = char(src + 'A');
    }
    ans[n] = '\0';
    return true;
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF && n) {
        memset(indegree, 0, sizeof(indegree));
        memset(graph, false, sizeof(graph));
        finished = false;
        for (int i = 1; i <= m; ++i) {
            getchar();
            scanf("%c<%c", &a, &b);
            if (finished) continue;
            a -= 'A';
            b -= 'A';
            graph[a][b] = true;
            ++indegree[b];
            memset(reachable, false, sizeof(reachable));
            dfs(b);
            if (reachable[a]) {
                printf("Inconsistency found after %d relations.\n", i);
                finished = true;
                continue;
            }
            if (uniquetoglogicalsort()) {
                printf("Sorted sequence determined after %d relations: %s.\n", i, ans);
                finished = true;
                continue;
            }
        }
        if (!finished) printf("Sorted sequence cannot be determined.\n");
    }

    return 0;
}