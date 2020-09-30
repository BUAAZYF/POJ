#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 1005;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int n, m, x, y, ans;
vector<int> graph[MAX];
int indegree[MAX];
bool used[MAX];

void dfs(int cmp) {
    int r1 = 0, r2 = 0, cnt = 0;
    for (int i = 1; i <= n; ++i) {
        if (used[i]) {
            ++cnt;
            continue;
        }
        if (indegree[i] == 0) {
            r2 = r1;
            r1 = i;
            if (r2 != 0) break;
        }
    }
    if (cnt == n) {
        ans = max(ans, cmp);
        return;
    }
    if (r1 == 0) return;
    if (r2 == 0) {
        for (int i = 0; i < graph[r1].size(); ++i) --indegree[graph[r1][i]];
        used[r1] = true;
        dfs(cmp);
        used[r1] = false;
        for (int i = 0; i < graph[r1].size(); ++i) ++indegree[graph[r1][i]];
    } else {
        for (int i = 0; i < graph[r1].size(); ++i) --indegree[graph[r1][i]];
        used[r1] = true;
        dfs(cmp + 1);
        used[r1] = false;
        for (int i = 0; i < graph[r1].size(); ++i) ++indegree[graph[r1][i]];
        for (int i = 0; i < graph[r2].size(); ++i) --indegree[graph[r2][i]];
        used[r2] = true;
        dfs(cmp + 1);
        used[r2] = false;
        for (int i = 0; i < graph[r2].size(); ++i) ++indegree[graph[r2][i]];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(indegree, 0, sizeof(indegree));
    while (m--) {
        scanf("%d%d", &x, &y);
        graph[x].push_back(y);
        ++indegree[y];
    }
    memset(used, false, sizeof(used));
    ans = 0;
    dfs(0);
    printf("%d\n", ans);

    return 0;
}