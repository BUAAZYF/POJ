#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <string>

using namespace std;

const int MAX = 8;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int n, sx, sy, ex, ey, ans;
char c, warehouse[MAX][MAX];
struct state {
    int x, y, step;
    char grid[MAX][MAX];
    string s;
    state(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
    string tostr() {
        s = char(x + '0');
        s += char(y + '0');
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) s += grid[i][j];
        return s;
    }
};

bool checkrange(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool canreach() {
    set<string> visited;
    state init(sx, sy, 0);
    memcpy(init.grid, warehouse, sizeof(warehouse));
    visited.insert(init.tostr());
    queue<state> q;
    q.push(init);
    while (!q.empty()) {
        state cur = q.front();
        q.pop();
        int nx, ny;
        for (int i = 0; i < 4; ++i) {
            nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (!checkrange(nx, ny)) continue;
            if (cur.grid[nx][ny] >= '1') {
                if (nx == ex && ny == ey) {
                    ans = cur.step + 1;
                    return true;
                }
                state nxt(nx, ny, cur.step + 1);
                memcpy(nxt.grid, cur.grid, sizeof(cur.grid));
                if (visited.find(nxt.tostr()) != visited.end()) continue;
                q.push(nxt);
                visited.insert(nxt.s);
            } else {
                if (cur.grid[cur.x][cur.y] == '1') continue;
                int cnt = cur.grid[cur.x][cur.y] - '0';
                if (!checkrange(cur.x + dx[i] * cnt, cur.y + dy[i] * cnt)) continue;
                char ngrid[MAX][MAX];
                memcpy(ngrid, cur.grid, sizeof(cur.grid));
                ngrid[cur.x][cur.y] = '.';
                bool toppled = true;
                nx = cur.x, ny = cur.y;
                for (int _ = 0; _ < cnt; ++_) {
                    nx += dx[i], ny += dy[i];
                    if (ngrid[nx][ny] == '.') ngrid[nx][ny] = '1';
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
                if (visited.find(nxt.tostr()) != visited.end()) continue;
                q.push(nxt);
                visited.insert(nxt.s);
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
                warehouse[i][j] = getchar();
                if (warehouse[i][j] == 'E') {
                    ex = i, ey = j;
                    warehouse[i][j] = '1';
                }
            }
            getchar();
        }
        if (canreach()) printf("%d\n", ans);
        else printf("Impossible\n");
    }
    return 0;
}