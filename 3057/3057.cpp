#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 15;
const int MAXV = 50005;
const int INF = 0x3f3f3f;

const int ex[4] = {-1, 1, 0, 0};
const int ey[4] = {0, 0, -1, 1};

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int T, R, C, V;
char grid[MAX][MAX];
vector<int> graph[MAXV], px, py, dx, dy;
int matched[MAXV], dis[MAX][MAX][MAX][MAX];
bool used[MAXV];

void bfs(int x, int y) {
    queue<int> qx, qy, q;
    qx.push(x);
    qy.push(y);
    dis[x][y][x][y] = 0;
    while (!qx.empty()) {
        int x1 = qx.front(), y1 = qy.front();
        qx.pop(), qy.pop();
        for (int i = 0; i < 4; ++i) {
            int x2 = x1 + ex[i], y2 = y1 + ey[i];
            if (x2 >= 0 && x2 < R && y2 >= 0 && y2 < C && grid[x2][y2] == '.' && dis[x][y][x2][y2] == -1) {
                dis[x][y][x2][y2] = dis[x][y][x1][y1] + 1;
                qx.push(x2);
                qy.push(y2);
            }
        }
    }
}

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

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d\n", &R, &C);
        dx.clear(), dy.clear();
        px.clear(), py.clear();
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                grid[i][j] = getchar();
                if (grid[i][j] == 'D') {
                    dx.push_back(i);
                    dy.push_back(j);
                } else if (grid[i][j] == '.') {
                    px.push_back(i);
                    py.push_back(j);
                }
            }
            getchar();
        }
        int n = R * C, d = dx.size(), p = px.size();
        if (p == 0) {
            printf("0\n");
            continue;
        }
        memset(dis, -1, sizeof(dis));
        for (int i = 0; i < dx.size(); ++i) bfs(dx[i], dy[i]);
        V = n * d + p;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < p; ++j) {
                if (dis[dx[i]][dy[i]][px[j]][py[j]] < 0) continue;
                for (int k = dis[dx[i]][dy[i]][px[j]][py[j]]; k <= n; ++k)
                    add_edge((k - 1) * d + i, n * d + j);
            }
        }
        int num = 0;
        bool sloved = false;
        memset(matched, -1, sizeof(matched));
        for (int v = 0; v < n * d; ++v) {
            memset(used, false, sizeof(used));
            if (dfs(v)) {
                if (++num == p) {
                    printf("%d\n", v / d + 1);
                    sloved = true;
                    break;
                }
            }
        }
        if (!sloved) printf("impossible\n");
    }

    return 0;
}
