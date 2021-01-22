#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX = 205;
const int MAXP = 40405;
const ll INF = 0x3f3f3f3f3f3f3f;
const int IINF = 0x3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

struct edge {
    int to, cap, rev;
};

int F, P, V, cows[MAX], shelter[MAX];
ll mat[MAX][MAX];
vector<edge> graph[MAXP];
int level[MAXP], iter[MAXP];

void add_edge(int from, int to, int cap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, 0, graph[from].size() - 1});
}

void build_graph(ll thershold) {
    int s = 0, t = V - 1;
    for (int i = 0; i < V; ++i) graph[i].clear();
    for (int i = 1; i <= F; ++i) {
        add_edge(s, i, cows[i]);
        add_edge(F + i, t, shelter[i]);
    }
    for (int i = 1; i <= F; ++i)
        for (int j = F + 1; j <= 2 * F; ++j)
            if (mat[i][j - F] <= thershold) add_edge(i, j, IINF);
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
        while ((f = dfs(s, t, IINF)) > 0) flow += f;
    }
}

void warshall_floyd() {
    for (int k = 1; k <= F; ++k)
        for (int i = 1; i <= F; ++i)
            for (int j = 1; j <= F; ++j) mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
}

int main() {
    while (scanf("%d%d", &F, &P) != EOF) {
        int s = 0, t = 2 * F + 1, cs = 0, ss = 0;
        V = 2 * F + 2;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 1; i <= F; ++i) {
            scanf("%d%d", &cows[i], &shelter[i]);
            cs += cows[i];
            ss += shelter[i];
        }
        fill(&mat[0][0], &mat[0][0] + MAX * MAX, INF);
        for (int i = 1; i <= F; ++i) mat[i][i] = 0;
        int x, y;
        ll path;
        for (int i = 0; i < P; ++i) {
            scanf("%d%d%lld", &x, &y, &path);
            if (path < mat[x][y]) mat[x][y] = mat[y][x] = path;
        }
        if (cs > ss) {
            printf("-1\n");
            continue;
        }
        warshall_floyd();
        ll lo = 0, hi = 0;
        for (int i = 1; i <= F; ++i)
            for (int j = i + 1; j <= F; ++j)
                if (mat[i][j] != INF) hi = max(hi, mat[i][j]);
        ll ans = INF;
        while (lo <= hi) {
            ll mid = (lo + hi) / 2;
            build_graph(mid);
            if (max_flow(s, t) == cs) {
                ans = min(ans, mid);
                hi = mid - 1;
            } else lo = mid + 1;
        }
        printf("%lld\n", ans == INF ? -1 : ans);
    }

    return 0;
}
