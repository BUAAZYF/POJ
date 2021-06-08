#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAXN = 1005;
const int MAXM = 15005;

struct edge {
    int x, y, cost;
    edge() {}
    edge(int _x, int _y, int _cost):x(_x), y(_y), cost(_cost) {}
};

bool operator<(const edge& e1, const edge& e2) {return e1.cost < e2.cost;}

int N, M, ans, me;
edge graph[MAXM];
int uni[MAXN];
vector<Pr> cables;

void init() {
    for (int i = 1; i <= N; ++i) uni[i] = i;
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
    while (scanf("%d%d", &N, &M) != EOF && N) {
        for (int i = 0; i < M; ++i) scanf("%d%d%d", &graph[i].x, &graph[i].y, &graph[i].cost);
        sort(graph, graph + M);
        ans = me = 0;
        cables.clear();
        init();
        for (int i = 0; i < M; ++i) {
            if (!same(graph[i].x, graph[i].y)) {
                merge(graph[i].x, graph[i].y);
                cables.push_back(make_pair(graph[i].x, graph[i].y));
                ans += graph[i].cost;
                me = graph[i].cost;
            }
        }
        printf("%d\n%d\n", me, cables.size());
        for (int i = 0; i < cables.size(); ++i) printf("%d %d\n", cables[i].first, cables[i].second);
    }
    return 0;
}