#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

const int MAX = 35;
const int DIRECTION = 6;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

int L, R, C, ans;
char cell;
bool maze[MAX][MAX][MAX];
int dx[DIRECTION] = {-1, 1, 0, 0, 0, 0};
int dy[DIRECTION] = {0, 0, -1, 1, 0, 0};
int dz[DIRECTION] = {0, 0, 0, 0, -1, 1};
struct point {
    int x, y, z;
    point() {}
    point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
} start, end;

bool checkrange(int x, int y, int z) {
    return x >= 0 && x < R && y >= 0 && y < C && z >= 0 && z < L;
}

void solve() {
    queue<pair<point, int> > q;
    q.push(make_pair(start, 0));
    maze[start.x][start.y][start.z] = false;
    while (!q.empty()) {
        pair<point, int> cur = q.front();
        q.pop();
        int x = cur.first.x, y = cur.first.y, z = cur.first.z, nx, ny, nz;
        int step = cur.second + 1;
        for (int i = 0; i < DIRECTION; ++i) {
            nx = x + dx[i], ny = y + dy[i], nz = z + dz[i];
            if (nx == end.x && ny == end.y && nz == end.z) {
                ans = step;
                return;
            }
            if (checkrange(nx, ny, nz) && maze[nx][ny][nz]) {
                maze[nx][ny][nz] = false;
                q.push(make_pair(point(nx, ny, nz), step));
            }
        }
    }
}

int main() {
    while (scanf("%d%d%d\n", &L, &R, &C) != EOF && L) {
        for (int l = 0; l < L; ++l) {
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    cell = getchar();
                    maze[r][c][l] = cell == '#' ? false : true;
                    if (cell == 'S') start = point(r, c, l);
                    if (cell == 'E') end = point(r, c, l);
                }
                getchar();
            }
            getchar();
        }
        ans = -1;
        solve();
        if (ans == -1) printf("Trapped!\n");
        else printf("Escaped in %d minute(s).\n", ans);
    }

    return 0;
}