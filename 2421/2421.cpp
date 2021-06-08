#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX = 105;

struct edge {
    int x, y, cost;
    edge(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
};

bool operator<(const edge& e1, const edge& e2) { return e1.cost < e2.cost; }

int N, Q, cost, x, y, ans;
vector<edge> graph;
int uni[MAX];

void init() {
    for (int i = 0; i < N; ++i) uni[i] = i;
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
    while (scanf("%d", &N) != EOF && N) {
        graph.clear();
        init();
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                scanf("%d", &cost);
                if (i < j) graph.push_back(edge(i, j, cost));
            }
        sort(graph.begin(), graph.end());
        scanf("%d", &Q);
        while (Q--) {
            scanf("%d%d", &x, &y);
            --x, --y;
            merge(x, y);
        }
        ans = 0;
        for (int i = 0; i < graph.size(); ++i) {
            if (!same(graph[i].x, graph[i].y)) {
                merge(graph[i].x, graph[i].y);
                ans += graph[i].cost;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}