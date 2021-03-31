#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 20005;
const int INF = 0x3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to, cap, rev;
};

int N, M, A, B, a, b, w;
vector<edge> graph[MAX * 2];
int level[MAX * 2], iter[MAX * 2];

void add_edge(int from, int to, int cap, int rcap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, rcap, graph[from].size() - 1});
}

void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
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
    scanf("%d%d", &N, &M);
    int s = 0, t = N + 1;
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &A, &B);
        add_edge(s, i, A, 0);
        add_edge(i, t, B, 0);
    }
    while (M--) {
        scanf("%d%d%d", &a, &b, &w);
        add_edge(a, b, w, w);
    }
    printf("%d\n", max_flow(s, t));

    return 0;
}