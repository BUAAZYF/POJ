#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 235;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

struct edge {
    int to, cap, rev;
};

int K, C, M, V, ans;
vector<edge> graph[MAX];
int mat[MAX][MAX], level[MAX], iter[MAX];

void warshall_floyd() {
    for (int k = 1; k <= K + C; ++k)
        for (int i = 1; i <= K + C; ++i)
            for (int j = 1; j <= K + C; ++j) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}

void add_edge(int from, int to, int cap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, 0, graph[from].size() - 1});
}

void build_graph(int cost) {
    int s = 0, t = V - 1;
    for (int i = 0; i < V; ++i) graph[i].clear();
    for (int i = 1; i <= K; ++i) add_edge(s, i, M);
    for (int j = K + 1; j <= K + C; ++j) add_edge(j, t, 1);
    for (int i = 1; i <= K; ++i)
        for (int j = K + 1; j <= K + C; ++j)
            if (mat[i][j] <= cost) add_edge(i, j, 1);
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
    while (scanf("%d%d%d", &K, &C, &M) != EOF) {
        V = K + C + 2;
        for (int i = 1; i <= K + C; ++i) {
            for (int j = 1; j <= K + C; ++j) {
                scanf("%d", &mat[i][j]);
                if (mat[i][j] == 0 && i != j) mat[i][j] = INF;
            }
        }
        warshall_floyd();
        int lo = INF, hi = 0, mid;
        for (int i = 1; i <= K; ++i) {
            for (int j = K + 1; j <= K + C; ++j) {
                if (mat[i][j] == INF) continue;
                lo = min(lo, mat[i][j]);
                hi = max(hi, mat[i][j]);
            }
        }
        ans = INF;
        int s = 0, t = V - 1;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            build_graph(mid);
            if (max_flow(s, t) == C) {
                ans = min(ans, mid);
                hi = mid - 1;
            } else lo = mid + 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}