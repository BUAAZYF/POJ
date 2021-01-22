#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 605;
const int INF = 0x3f3f3f3f;
const double EPS = 1E-9;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

struct edge {
    int to;
    double cap;
    int rev;
};

int T, m, n, V, l, r, c;
double cost;
vector<edge> graph[MAX];
int level[MAX], iter[MAX];

void add_edge(int from, int to, double cap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, 0, graph[from].size() - 1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < graph[v].size(); ++i) {
            edge& e = graph[v][i];
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

double dfs(int v, int t, double f) {
    if (v == t || f < EPS) return f;
    for (int& i = iter[v]; i < graph[v].size(); ++i) {
        edge& e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            double d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

double max_flow(int s, int t) {
    double flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        double f;
        while ((f = dfs(s, t, INF)) > EPS) flow += f;
    }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &m, &n, &l);
        V = m + n + 2;
        int s = 0, t = V - 1;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (r = 1; r <= m; ++r) {
            scanf("%lf", &cost);
            add_edge(s, r, log(cost));
        }
        for (c = 1; c <= n; ++c) {
            scanf("%lf", &cost);
            add_edge(m + c, t, log(cost));
        }
        for (int i = 1; i <= l; ++i) {
            scanf("%d%d", &r, &c);
            add_edge(r, m + c, INF);
        }
        printf("%.4f\n", exp(max_flow(s, t)));
    }

    return 0;
}