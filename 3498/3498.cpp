#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 205;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to, cap, rev;
};

int T, N, V, s, pcnt, cordx[MAX], cordy[MAX], penguins[MAX], jumps[MAX];
vector<int> ans;
double D;
vector<edge> graph[MAX];
int level[MAX], iter[MAX];

void add_edge(int from, int to, int cap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, 0, graph[from].size() - 1});
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

bool canreach(int i1, int i2) {
    return sqrt(pow(cordx[i1] - cordx[i2], 2) + pow(cordy[i1] - cordy[i2], 2)) <= D;
}

void build_grah() {
    for (int i = 0; i < V; ++i) graph[i].clear();
    for (int i = 0; i < N; ++i) {
        add_edge(s, i, penguins[i]);
        add_edge(i, N + i, jumps[i]);
    }
    for (int i = 0; i < N; ++i)
        for (int j = i + 1; j < N; ++j)
            if (canreach(i, j)) {
                add_edge(N + i, j, INF);
                add_edge(N + j, i, INF);
            }
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lf", &N, &D);
        pcnt = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d%d%d%d", &cordx[i], &cordy[i], &penguins[i], &jumps[i]);
            pcnt += penguins[i];
        }
        V = 2 * N + 1, s = V - 1;
        ans.clear();
        for (int i = 0; i < N; ++i) {
            build_grah();
            if (max_flow(s, i) == pcnt) ans.push_back(i);
        }
        if (ans.empty())
            printf("-1\n");
        else {
            for (int i = 0; i < (int)ans.size() - 1; ++i) printf("%d ", ans[i]);
            printf("%d\n", ans[ans.size() - 1]);
        }
    }
    return 0;
}