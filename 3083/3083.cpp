#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 40;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};

struct Item {
    int x, y, d;
    Item(int _x, int _y, int _d) : x(_x), y(_y), d(_d) {}
};

int t, w, h, sx, sy, ex, ey;
char maze[MAX][MAX];
bool visited[MAX][MAX];

bool check(int x, int y) {
    return x >= 0 && x < w && y >= 0 && y < h;
}

int go_side(bool left) {
    int d, x, y, nx, ny, ans = 2;
    for (int i = 0; i < 4; ++i) {
        x = sx + dx[i], y = sy + dy[i];
        if (check(x, y) && maze[x][y] == '.') {
            d = i;
            break;
        }
    }
    int shift = (left ? 1 : -1);
    while (!(x == ex && y == ey)) {
        d = (d + 4 + (left ? -1 : 1)) % 4;
        while (true) {
            nx = x + dx[d], ny = y + dy[d];
            if (check(nx, ny) && maze[nx][ny] != '#') break;
            d = (d + 4 + shift) % 4;
        }
        ++ans;
        x = nx, y = ny;
    }
    return ans;
}

int bfs() {
    queue<Item> q;
    q.push(Item(sx, sy, 1));
    visited[sx][sy] = true;
    while (!q.empty()) {
        Item cur = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int x = cur.x + dx[i], y = cur.y + dy[i];
            if (check(x, y) && !visited[x][y] && maze[x][y] != '#') {
                if (x == ex && y == ey) return cur.d + 1;
                visited[x][y] = true;
                q.push(Item(x, y, cur.d + 1));
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d\n", &h, &w);
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                maze[i][j] = getchar();
                if (maze[i][j] == 'S')
                    sx = i, sy = j;
                else if (maze[i][j] == 'E')
                    ex = i, ey = j;
            }
            getchar();
        }
        go_side(true);
        memset(&visited[0][0], false, sizeof(visited));
        printf("%d %d %d\n", go_side(true), go_side(false), bfs());
    }

    return 0;
}