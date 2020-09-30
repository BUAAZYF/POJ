#include <cstdio>
#include <vector>

using namespace std;

const int MAX = 105;
const int INF = 0x3f3f3f3f;

int n, m, nei, src, dst, ans;
bool visited[MAX];
vector<int> graph[MAX];

void dfs(int node, int change) {
    if (change >= ans) return;
    if (node == dst) {
        ans = min(ans, change);
        return;
    }
    visited[node] = true;
    for (int i = 0; i < graph[node].size(); ++i) {
        if (visited[graph[node][i]]) continue;
        dfs(graph[node][i], change + int(i != 0));
    }
    visited[node] = false;
}

int main() {
    scanf("%d%d%d", &n, &src, &dst);
    for (int i = 1; i <= n; ++i) {
        visited[i] = false;
        graph[i].clear();
        scanf("%d", &m);
        while (m--) {
            scanf("%d", &nei);
            graph[i].push_back(nei);
        }
    }
    ans = INF;
    dfs(src, 0);
    printf("%d\n", ans == INF ? -1 : ans);

    return 0;
}