#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

typedef pair<bool, int> Pr;

const int MAXV = 105;
const int MAXE = 5000;
const int INF = 0x3f3f3f3f;

struct edge {
    int x, y, cost;
    edge() {}
    edge(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
} graph[MAXE], ngraph[MAXE];

bool operator<(const edge& e1, const edge& e2) { return e1.cost < e2.cost; }

int t, n, m, ans;
int uni[MAXV], mst[MAXV];

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

Pr kruskal(edge g[MAXE], bool store_edges = false) {
    int res = 0, cnt = 0;
    init();
    for (int i = 0; i < m; ++i) {
        if (!same(g[i].x, g[i].y)) {
            if (store_edges) mst[cnt] = i;
            ++cnt;
            merge(g[i].x, g[i].y);
            res += g[i].cost;
        }
    }
    return make_pair(cnt == n - 1, res);
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < m; ++i) scanf("%d%d%d", &graph[i].x, &graph[i].y, &graph[i].cost);
        sort(graph, graph + m);
        Pr ret = kruskal(graph, true);
        bool unique = ret.first;
        ans = ret.second;
        if (unique) {
            for (int i = 0; i < n - 1; ++i) {
                memcpy(ngraph, graph, sizeof(graph));
                ++ngraph[mst[i]].cost;
                sort(ngraph, ngraph + m);
                ret = kruskal(ngraph);
                if (!ret.first) break;
                if (ret.second == ans) {
                    unique = false;
                    break;
                }
            }
        }
        if (unique) printf("%d\n", ans);
        else printf("Not Unique!\n");
    }

    return 0;
}