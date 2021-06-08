#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 8;
const int MOD = 1000000;
const int SEED = 131;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int n, sx, sy, ex, ey, ans;
char c, warehouse[MAX][MAX];
bool visited[MOD + 6];
struct state {
    int x, y, step;
    char grid[MAX][MAX];
    int h;
    state(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
    int hash() {
        h = x * SEED + y;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) h = (h * SEED + grid[i][j]) % MOD;
        return h;
    }
};

bool checkrange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool canreach() {
    memset(visited, false, sizeof(visited));
    state init(sx, sy, 0);
    memcpy(init.grid, warehouse, sizeof(warehouse));
    visited[init.hash()] = true;
    queue<state> q;
    q.push(init);
    while (!q.empty()) {
        state cur = q.front();
        q.pop();
        int nx, ny;
        for (int i = 0; i < 4; ++i) {
            nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (!checkrange(nx, ny)) continue;
            if (cur.grid[nx][ny] >= 1) {
                if (nx == ex && ny == ey) {
                    ans = cur.step + 1;
                    return true;
                }
                state nxt(nx, ny, cur.step + 1);
                memcpy(nxt.grid, cur.grid, sizeof(cur.grid));
                if (visited[nxt.hash()]) continue;
                q.push(nxt);
                visited[nxt.h] = true;
            } else {
                if (cur.grid[cur.x][cur.y] == 1) continue;
                int cnt = cur.grid[cur.x][cur.y];
                if (!checkrange(cur.x + dx[i] * cnt, cur.y + dy[i] * cnt)) continue;
                char ngrid[MAX][MAX];
                memcpy(ngrid, cur.grid, sizeof(cur.grid));
                ngrid[cur.x][cur.y] = 0;
                bool toppled = true;
                nx = cur.x, ny = cur.y;
                for (int _ = 0; _ < cnt; ++_) {
                    nx += dx[i], ny += dy[i];
                    if (ngrid[nx][ny] == 0) ngrid[nx][ny] = 1;
                    else {
                        toppled = false;
                        break;
                    }
                }
                if (!toppled) continue;
                nx = cur.x + dx[i], ny = cur.y + dy[i];
                if (nx == ex && ny == ey) {
                    ans = cur.step + 1;
                    return true;
                }
                state nxt(nx, ny, cur.step + 1);
                memcpy(nxt.grid, ngrid, sizeof(ngrid));
                if (visited[nxt.hash()]) continue;
                q.push(nxt);
                visited[nxt.h] = true;
            }
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d%d\n", &n, &sx, &sy) != EOF && n) {
        --sx, --sy;
        memset(warehouse, 0, sizeof(warehouse));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                c = getchar();
                if (c == '.') continue;
                if (c == 'E') {
                    ex = i, ey = j;
                    warehouse[i][j] = 1;
                } else warehouse[i][j] = c - '0';
            }
            getchar();
        }
        if (canreach()) printf("%d\n", ans);
        else printf("Impossible\n");
    }
    return 0;
}