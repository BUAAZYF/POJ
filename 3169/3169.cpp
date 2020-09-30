#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX = 10005;
const int INF = 0x3f3f3f3f;

int N, ML, MD;
bool updated;
int AL[MAX], BL[MAX], DL[MAX];
int AD[MAX], BD[MAX], DD[MAX];
int dis[MAX];

void update(int& x, int y) {
    if (x > y) {
        x = y;
        updated = true;
    }
}

void bellmanford() {
    for (int k = 0; k <= N; ++k) {
        updated = false;
        for (int i = 0; i + 1 < N; ++i)
            if (dis[i + 1] < INF) update(dis[i], dis[i + 1]);
        for (int i = 0; i < ML; ++i)
            if (dis[AL[i] - 1] < INF) update(dis[BL[i] - 1], dis[AL[i] - 1] + DL[i]);
        for (int i = 0; i < MD; ++i)
            if (dis[BD[i] - 1] < INF) update(dis[AD[i] - 1], dis[BD[i] - 1] - DD[i]);
    }
}

int main() {
    scanf("%d%d%d", &N, &ML, &MD);
    for (int i = 0; i < ML; ++i) scanf("%d%d%d", &AL[i], &BL[i], &DL[i]);
    for (int i = 0; i < MD; ++i) scanf("%d%d%d", &AD[i], &BD[i], &DD[i]);
    fill(dis, dis + N, 0);
    bellmanford();
    if (updated) printf("-1\n");
    else {
        fill(dis, dis + N, INF);
        dis[0] = 0;
        bellmanford();
        printf("%d\n", dis[N - 1] == INF ? -2 : dis[N - 1]);
    }

    return 0;
}