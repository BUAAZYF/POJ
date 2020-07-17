#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = 405;
const int MAXA = 40001;

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct block {
    int height;
    int cnt;
    int altitude;
} blocks[MAX];

bool cur[MAXA], nxt[MAXA];

bool cmp(block a, block b) {
    return a.altitude < b.altitude || a.altitude == b.altitude && a.height > b.height;
}
int K, cmax, nmax;

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d", &K);
    for (int i = 0; i < K; ++i) scanf("%d%d%d", &blocks[i].height, &blocks[i].altitude, &blocks[i].cnt);
    sort(blocks, blocks + K, cmp);
    memset(cur, false, sizeof(cur));
    cmax = 0;
    cur[0] = true;
    for (int i = 0; i < K; ++i) {
        nmax = cmax;
        memcpy(nxt, cur, sizeof(cur));
        for (int j = 0; j <= cmax; ++j) {
            if (!cur[j]) continue;
            int c = min(blocks[i].cnt, (blocks[i].altitude - j) / blocks[i].height);
            nmax = max(nmax, j + c * blocks[i].height);
            for (; c >= 1; --c) nxt[j + c * blocks[i].height] = true;
        }
        cmax = nmax;
        memcpy(cur, nxt, sizeof(cur));
    }
    printf("%d\n", cmax);

    return 0;
}