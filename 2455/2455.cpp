#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

const int MAX = 40005;
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

struct trail {
    int x, y, len;
    bool friend operator<(const trail& t1, const trail& t2) {
        return t1.len < t2.len;
    }
} trails[MAX];

int N, P, T;
vector<edge> graph[MAX * 2];
int level[MAX * 2], iter[MAX * 2];

void add_edge(int from, int to, int cap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, cap, graph[from].size() - 1});
}

void build_graph(int thershold) {
    for (int i = 1; i <= N; ++i) graph[i].clear();
    for (int i = 0; i < P; ++i) {
        if (trails[i].len > thershold) break;
        add_edge(trails[i].x, trails[i].y, 1);
    }
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
    while (scanf("%d%d%d\n", &N, &P, &T) != EOF) {
        int lo = INF, hi = 0;
        for (int i = 0; i < P; ++i) {
            scanf("%d%d%d", &trails[i].x, &trails[i].y, &trails[i].len);
            lo = min(lo, trails[i].len);
            hi = max(hi, trails[i].len);
        }
        sort(trails, trails + P);
        int ans = INF;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            build_graph(mid);
            if (max_flow(1, N) >= T) {
                ans = min(ans, mid);
                hi = mid - 1;
            } else lo = mid + 1;
        }
        printf("%d\n", ans);
    }

    return 0;
}
