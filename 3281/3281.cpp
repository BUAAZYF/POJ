#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 105;
const int MAXV = MAX * 4;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}
struct edge {
    int to, cap, rev;
};

int N, F, D, V, fc, dc;
vector<edge> graph[MAXV];
int level[MAXV], iter[MAXV];

void add_edge(int from, int to, int cap) {
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

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < graph[v].size(); ++i) {
        edge& e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        int f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

int main() {
    while (scanf("%d%d%d", &N, &F, &D) != EOF) {
        int s = 0, t = F + 2 * N + D + 1, food, dish;
        for (int i = 1; i <= F; ++i) add_edge(s, i, 1);
        for (int i = 1; i <= D; ++i) add_edge(F + 2 * N + i, t, 1);
        for (int i = 1; i <= N; ++i) {
            add_edge(F + i, F + N + i, 1);
            scanf("%d%d", &fc, &dc);
            for (int j = 0; j < fc; ++j) {
                scanf("%d", &food);
                add_edge(food, F + i, 1);
            }
            for (int j = 0; j < dc; ++j) {
                scanf("%d", &dish);
                add_edge(F + N + i, F + 2 * N + dish, 1);
            }
        }
        printf("%d\n", max_flow(s, t));
    }

    return 0;
}
