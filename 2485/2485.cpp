#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXV = 505;
const int MAXE = 125005;

struct edge {
    int x, y, cost;
    edge() {}
    edge(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
} graph[MAXE];

bool operator<(const edge& e1, const edge& e2) { return e1.cost < e2.cost; }

int t, n, m, cost, ans;
int uni[MAXV];

void init() {
    for (int i = 1; i <= n; ++i) uni[i] = i;
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
        scanf("%d", &n);
        m = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                scanf("%d", &cost);
                if (i < j) graph[m++] = edge(i, j, cost);
            }
        sort(graph, graph + m);
        init();
        ans = 0;
        for (int i = 0; i < m; ++i) {
            if (!same(graph[i].x, graph[i].y)) {
                merge(graph[i].x, graph[i].y);
                ans = graph[i].cost;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}