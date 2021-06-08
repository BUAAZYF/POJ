#include <cstdio>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 8;

struct Item {
    int x, y, step;
    Item(int _x, int _y, int _step) : x(_x), y(_y), step(_step) {}
};

bool operator<(const Item& a, const Item& b) {
    return a.step > b.step;
}

const int dx[MAX] = {-1, -1, 1, 1, -2, -2, 2, 2};
const int dy[MAX] = {-2, 2, -2, 2, -1, 1, -1, 1};

char start[3], end[3];
int sx, sy, ex, ey;
bool visited[MAX][MAX];

bool checkrange(int x, int y) {
    return x >= 0 && x < MAX && y >= 0 && y < MAX;
}

int spfa() {
    if (sx == ex && sy == ey) return 0;
    priority_queue<Item> pq;
    pq.push(Item(sx, sy, 0));
    memset(visited, false, sizeof(visited));
    visited[sx][sy] = true;
    int nx, ny;
    while (true) {
        Item cur = pq.top();
        pq.pop();
        for (int i = 0; i < MAX; ++i) {
            nx = cur.x + dx[i], ny = cur.y + dy[i];
            if (!checkrange(nx, ny) || visited[nx][ny]) continue;
            if (nx == ex && ny == ey) return cur.step + 1;
            visited[nx][ny] = true;
            pq.push(Item(nx, ny, cur.step + 1));
        }
    }
    return 0;
}

int main() {
    while (scanf("%s %s", start, end) != EOF) {
        sx = start[0] - 'a', sy = start[1] - '1';
        ex = end[0] - 'a', ey = end[1] - '1';
        printf("To get from %s to %s takes %d knight moves.\n", start, end, spfa());
    }
    return 0;
}