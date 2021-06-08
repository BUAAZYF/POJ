#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXV = 105;
const int MAXE = 5000;
const int INF = 0x3f3f3f3f;

struct edge {
    int x, y, cost;
    edge() {}
    edge(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
} graph[MAXE];

bool operator<(const edge& e1, const edge& e2) { return e1.cost < e2.cost; }

int n, m, ans;
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
    while (scanf("%d%d", &n, &m) != EOF && n) {
        for (int i = 0; i < m; ++i) scanf("%d%d%d", &graph[i].x, &graph[i].y, &graph[i].cost);
        sort(graph, graph + m);
        ans = INF;
        for (int k = 0; k <= m - (n - 1); ++k) {
            if (k > 0 && graph[k].cost == graph[k - 1].cost || graph[k + n - 2].cost - graph[k].cost >= ans) continue;
            init();
            int cnt = 0, mw = graph[k].cost;
            for (int i = k; i < m; ++i) {
                if (!same(graph[i].x, graph[i].y)) {
                    ++cnt;
                    merge(graph[i].x, graph[i].y);
                    mw = graph[i].cost;
                }
            }
            if (cnt != n - 1) break;
            ans = min(ans, mw - graph[k].cost);
        }
        printf("%d\n", ans == INF ? -1 : ans);
    }

    return 0;
}