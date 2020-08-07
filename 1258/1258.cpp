#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 105;

int V, E, cost, ans;
struct edge {
    edge():x(0), y(0), cost(0) {}
    edge(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
    int x, y, cost;
    friend bool operator<(const edge& a, const edge& b) {
        return a.cost < b.cost;
    }
} edges[MAXN * MAXN / 2];
int uni[MAXN];

void init_uni() {
    for (int i = 0; i < V; ++i) uni[i] = i;
}

int find(int x) {
    if (x == uni[x])
        return x;
    else
        return uni[x] = find(uni[x]);
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
    while (scanf("%d", &V) != EOF) {
        E = 0;
        init_uni();
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                scanf("%d", &cost);
                if (i > j) edges[E++] = edge(i, j, cost);
            }
        }
        sort(edges, edges + E);
        ans = 0;
        for (int i = 0; i < E; ++i) {
            if (!same(edges[i].x, edges[i].y)) {
                merge(edges[i].x, edges[i].y);
                ans += edges[i].cost;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}