#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 40005;

int N, M, K, x, y, d, ans;
char direction;
vector<Pr> edges[MAX];
bool visited[MAX];

int dfs(int node) {
    visited[node] = true;
    int first = 0, second = 0, cur;
    for (int i = 0; i < edges[node].size(); ++i) {
        if (visited[edges[node][i].first]) continue;
        cur = edges[node][i].second + dfs(edges[node][i].first);
        if (cur >= first) {
            second = first;
            first = cur;
        } else if (cur > second)
            second = cur;
    }
    ans = max(ans, first + second);
    return first;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d %c", &x, &y, &d, &direction);
        edges[x].push_back(Pr(y, d));
        edges[y].push_back(Pr(x, d));
    }
    ans = 0;
    fill(visited, visited + N + 1, false);
    dfs(1);
    printf("%d\n", ans);

    return 0;
}