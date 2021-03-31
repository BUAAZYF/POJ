#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 110;
const double INF = 0x3f3f3f3f;
const double EPS = 1e-8;

int min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to;
    double cap;
    int rev;
};

int N, M, V, degree[MAX], s, t, ans;
bool visited[MAX];
vector<edge> graph[MAX];
int level[MAX], iter[MAX];

struct point {
    int x, y;
} points[MAX * 10];

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
            if (e.cap > EPS && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

double dfs(int v, int t, double f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < graph[v].size(); ++i) {
        edge& e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            double d = dfs(e.to, t, min(f, e.cap));
            if (d > EPS) {
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

void construct_graph(double g) {
    for (int i = 0; i < V; ++i) graph[i].clear();
    for (int i = 1; i <= N; ++i) {
        add_edge(s, i, M);
        add_edge(i, t, M + 2 * g - degree[i]);
    }
    for (int i = 0; i < M; ++i) {
        add_edge(points[i].x, points[i].y, 1.0);
        add_edge(points[i].y, points[i].x, 1.0);
    }
}

void dfs_travel(int v) {
    ++ans;
    visited[v] = true;
    vector<edge>& gv = graph[v];
    for (vector<edge>::iterator it = gv.begin(); it != gv.end(); ++it) {
        const edge& e = *it;
        if (e.cap > EPS && !visited[e.to]) dfs_travel(e.to);
    }
}

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        if (M == 0) {
            printf("1\n1\n");
            continue;
        }
        memset(degree, 0, sizeof(degree));
        memset(visited, false, sizeof(visited));
        s = 0, t = N + 1, V = t + 1;
        for (int i = 0; i < M; ++i) {
            scanf("%d%d", &points[i].x, &points[i].y);
            ++degree[points[i].x];
            ++degree[points[i].y];
        }
        double lb = 0, ub = M, mid, hg;
        const double precision = 1.0 / N / N;
        while (ub - lb >= precision) {
            mid = (lb + ub) / 2;
            construct_graph(mid);
            hg = (N * M - max_flow(s, t)) / 2;
            (hg > EPS ? lb : ub) = mid;
        }
        construct_graph(lb);
        max_flow(s, t);
        ans = 0;
        dfs_travel(0);
        printf("%d\n", ans - 1);
        for (int i = 1; i <= N; ++i)
            if (visited[i] == true) printf("%d\n", i);
    }
    return 0;
}