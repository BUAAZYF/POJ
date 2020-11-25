#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int MAXX = 205;
const int MAXY = 40005;

struct item {
    item(int _step, int _x, int _y) : step(_step), x(_x), y(_y) {}
    int step, x, y;
};

int P, ans, nx, ny;
bool visited[MAXX][MAXY], inpq[MAXX][MAXY];
queue<item> pq;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int main() {
    scanf("%d\n", &P);
    pq.push(item(0, 0, 1));
    inpq[0][1] = true;
    ans = -1;
    while (!pq.empty()) {
        item cur = pq.front();
        pq.pop();
        if (visited[cur.x][cur.y]) continue;
        visited[cur.x][cur.y] = true;
        int xs[] = {cur.x + cur.x, cur.x + cur.y, cur.y + cur.y, cur.y - cur.x};
        int ys[] = {cur.x, cur.y};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 2; ++j) {
                nx = xs[i];
                ny = ys[j];
                if (nx > ny) swap(nx, ny);
                if (nx >= MAXX || ny >= MAXY) continue;
                if (ny == P) {
                    ans = cur.step + 1;
                    break;
                }
                if (!inpq[nx][ny]) {
                    pq.push(item(cur.step + 1, nx, ny));
                    inpq[nx][ny] = true;
                }
            }
        }
        if (ans != -1) break;
    }
    printf("%d\n", ans);

    return 0;
}