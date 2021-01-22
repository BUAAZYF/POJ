#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 55;
const int MAXN = 1005;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int R, C, V;
char grid[MAX][MAX];
vector<int> graph[MAXN];
map<Pr, int> rows, cols;
int matched[MAXN];
bool used[MAXN];

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
    while (scanf("%d%d\n", &R, &C) != EOF) {
        rows.clear();
        cols.clear();
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) grid[r][c] = getchar();
            getchar();
        }
        int cur = -1;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == '.') continue;
                if (c == 0 || grid[r][c - 1] == '.') ++cur;
                rows[make_pair(r, c)] = cur;
            }
        }
        for (int c = 0; c < C; ++c) {
            for (int r = 0; r < R; ++r) {
                if (grid[r][c] == '.') continue;
                if (r == 0 || grid[r - 1][c] == '.') ++cur;
                cols[make_pair(r, c)] = cur;
            }
        }
        V = cur + 1;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == '.') continue;
                add_edge(rows[make_pair(r, c)], cols[make_pair(r, c)]);
            }
        }
        printf("%d\n", bipartite_matching());
    }

    return 0;
}
