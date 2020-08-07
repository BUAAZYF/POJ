#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXV = 2005;
const int MAXE = 10005;

int inline max(int a, int b){
    return a >= b ? a : b;
}

int V, E, cost, ans;
struct edge {
    edge():x(0), y(0), cost(0) {}
    edge(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
    int x, y, cost;
    friend bool operator<(const edge& a, const edge& b) {
        return a.cost < b.cost;
    }
} edges[MAXE];
int uni[MAXV];

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
    scanf("%d%d", &V, &E);
    init_uni();
    for (int i = 0; i < E; ++i)
        scanf("%d%d%d", &edges[i].x, &edges[i].y, &edges[i].cost);
    sort(edges, edges + E);
    ans = 0;
    for (int i = 0; i < E; ++i) {
        if (!same(edges[i].x, edges[i].y)) {
            merge(edges[i].x, edges[i].y);
            ans = max(0, edges[i].cost);
        }
    }
    printf("%d\n", ans);

    return 0;
}