#include <cstdio>
#include <cstring>
#include <queue>
#include <string>

using namespace std;

const int MAX = 6;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

struct Item {
    int x, y;
    string path;
    Item(int _x, int _y, string p = "") : x(_x), y(_y), path(p) {}
};

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const char direction[4] = {'W', 'E', 'N', 'S'};

int sx, sy, ex, ey, wx1, wx2, wy1, wy2;
bool visited[MAX + 1][MAX + 1], walls[MAX + 1][MAX + 1][MAX + 1][MAX + 1];
string ans;

int main() {
    while (scanf("%d%d", &sx, &sy) != EOF && sx) {
        scanf("%d%d", &ex, &ey);
        memset(&walls[0][0][0][0], false, sizeof(walls));
        for (int _ = 0; _ < 3; ++_) {
            scanf("%d%d%d%d", &wx1, &wy1, &wx2, &wy2);
            if (wx1 == wx2) {
                if (wx1 == 0 || wx1 == 6) continue;
                ++wy1;
                while (wy1 <= wy2) {
                    walls[wx1][wy1][wx1 + 1][wy1] = walls[wx1 + 1][wy1][wx1][wy1] = true;
                    ++wy1;
                }
            } else {
                if (wy1 == 0 || wy1 == 6) continue;
                ++wx1;
                while (wx1 <= wx2) {
                    walls[wx1][wy1][wx1][wy1 + 1] = walls[wx1][wy1 + 1][wx1][wy1] = true;
                    ++wx1;
                }
            }
        }
        queue<Item> q;
        memset(&visited[0][0], false, sizeof(visited));
        visited[sx][sy] = true;
        q.push(Item(sx, sy));
        ans = "";
        while (!q.empty() && ans.empty()) {
            Item cur = q.front();
            q.pop();
            for (int i = 0; i < 4; ++i) {
                int nx = cur.x + dx[i], ny = cur.y + dy[i];
                if (nx < 1 || nx > 6 || ny < 1 || ny > 6 || visited[nx][ny] || walls[cur.x][cur.y][nx][ny]) continue;
                if (nx == ex && ny == ey) {
                    ans = cur.path + direction[i];
                    break;
                }
                visited[nx][ny] = true;
                q.push(Item(nx, ny, cur.path + direction[i]));
            }
        }
        printf("%s\n", ans.c_str());
    }

    return 0;
}