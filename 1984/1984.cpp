#include <algorithm>
#include <cstdio>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 40005;
const int MAXK = 10005;

int parent[MAX];
Pr rel[MAX];

int N, M, K;
int ans[MAXK];

struct info {
    char direction;
    int x, y, len;
} infos[MAX];

struct query {
    int idx, x, y, k;
} queris[MAXK];

bool query_cmp(const query a, const query b){
    return a.idx < b.idx;
}

int inline abs(int x) {
    return x >= 0 ? x : -x;
}

void init() {
    for (int i = 1; i <= N; ++i) {
        parent[i] = i;
        rel[i] = make_pair(0, 0);
    }
}

int find(int x) {
    if (x != parent[x]) {
        int y = parent[x];
        parent[x] = find(parent[x]);
        rel[x].first += rel[y].first;
        rel[x].second += rel[y].second;
    }
    return parent[x];
}

void handle_info(int info_idx) {
    int x = find(infos[info_idx].x), y = find(infos[info_idx].y);
    int dx = 0, dy = 0, len = infos[info_idx].len;
    switch (infos[info_idx].direction) {
        case 'N': dy = len; break;
        case 'S': dy = -len; break;
        case 'E': dx = len; break;
        case 'W': dx = -len; break;
        default: break;
    }
    parent[y] = x;
    rel[y].first += dx - rel[infos[info_idx].y].first + rel[infos[info_idx].x].first;
    rel[y].second += dy - rel[infos[info_idx].y].second + rel[infos[info_idx].x].second;
}

int main() {
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    init();
    for (int i = 1; i <= M; ++i)
        scanf("%d %d %d %c", &infos[i].x, &infos[i].y, &infos[i].len, &infos[i].direction);
    scanf("%d", &K);
    for (int i = 0; i < K; ++i) {
        scanf("%d%d%d", &queris[i].x, &queris[i].y, &queris[i].idx);
        queris[i].k = i;
    }

    sort(queris, queris + K, query_cmp);
    int info_idx = 1;
    for (int i = 0; i < K; ++i) {
        while (info_idx <= queris[i].idx) {
            handle_info(info_idx);
            ++info_idx;
        }
        if (find(queris[i].x) != find(queris[i].y))
            ans[queris[i].k] = -1;
        else
            ans[queris[i].k] = abs(rel[queris[i].x].first - rel[queris[i].y].first) +
                               abs((rel[queris[i].x].second - rel[queris[i].y].second));
    }

    for (int i = 0; i < K; ++i) printf("%d\n", ans[i]);

    return 0;
}