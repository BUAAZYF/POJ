#include <algorithm>
#include <cstdio>

using namespace std;

typedef pair<int, int> Pr;

const int MAXN = 10005;
const int MAXR = 50005;
const int MAXC = 10000;

int t, N, M, R, V, ans;
struct edge {
    int x, y, cost;
    friend bool operator<(const edge& a, const edge& b) {
        return a.cost < b.cost;
    }
} edges[MAXR];
int uni[2 * MAXN];

void init_uni() {
    for (int i = 0; i < V; ++i) uni[i] = i;
}

int find(int x) {
    if (x == uni[x]) return x;
    else return uni[x] = find(uni[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    x > y ? uni[x] = y : uni[y] = x;
}

bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &N, &M, &R);
        V = M + N;
        init_uni();
        for (int i = 0; i < R; ++i) {
            scanf("%d%d%d", &edges[i].x, &edges[i].y, &edges[i].cost);
            edges[i].y += N;
            edges[i].cost = -edges[i].cost;
        }
        sort(edges, edges + R);
        ans = 0;
        for (int i = 0; i < R; ++i) {
            if (!same(edges[i].x, edges[i].y)) {
                merge(edges[i].x, edges[i].y);
                ans += edges[i].cost;
            }
        }
        ans += MAXC * V;
        printf("%d\n", ans);
    }

    return 0;
}