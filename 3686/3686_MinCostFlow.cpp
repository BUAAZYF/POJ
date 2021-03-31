#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 55;
const int MAXV = 2600;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> Pr;

int min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to, cap, cost, rev;
};

int T, N, M, V, Z[MAXN][MAXN];
vector<edge> graph[MAXV];
int h[MAXV], dis[MAXV], prevv[MAXV], preve[MAXV];

void add_edge(int from, int to, int cap, int cost) {
    graph[from].push_back(edge{to, cap, cost, graph[to].size()});
    graph[to].push_back(edge{from, 0, -cost, graph[from].size() - 1});
}

int min_cost_flow(int s, int t, int f) {
    int ans = 0;
    memset(h, 0, sizeof(h));
    while (f > 0) {
        priority_queue<Pr, vector<Pr>, greater<Pr> > pq;
        fill(dis, dis + V, INF);
        dis[s] = 0;
        pq.push(Pr(0, s));
        while (!pq.empty()) {
            Pr cur = pq.top();
            pq.pop();
            int v = cur.second;
            if (dis[v] < cur.first) continue;
            for (int i = 0; i < graph[v].size(); ++i) {
                edge& e = graph[v][i];
                if (e.cap > 0 && dis[e.to] > dis[v] + e.cost + h[v] - h[e.to]) {
                    dis[e.to] = dis[v] + e.cost + h[v] - h[e.to];
                    prevv[e.to] = v;
                    preve[e.to] = i;
                    pq.push(Pr(dis[e.to], e.to));
                }
            }
        }
        if (dis[t] == INF) return -1;
        for (int v = 0; v < V; ++v) h[v] += dis[v];
        int d = f;
        for (int v = t; v != s; v = prevv[v]) d = min(d, graph[prevv[v]][preve[v]].cap);
        f -= d;
        ans += d * h[t];
        for (int v = t; v != s; v = prevv[v]) {
            edge& e = graph[prevv[v]][preve[v]];
            e.cap -= d;
            graph[v][e.rev].cap += d;
        }
    }
    return ans;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &M);
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j) scanf("%d", &Z[i][j]);
        int s = N + M * N, t = s + 1;
        V = t + 1;
        for (int v = 0; v < V; ++v) graph[v].clear();
        for (int i = 0; i < N; ++i) add_edge(s, i, 1, 0);
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k < N; ++k) {
                add_edge(N + j * N + k, t, 1, 0);
                for (int i = 0; i < N; ++i) {
                    add_edge(i, N + j * N + k, 1, (k + 1) * Z[i][j]);
                }
            }
        }
        printf("%0.6f\n", double(min_cost_flow(s, t, N)) / N);
    }

    return 0;
}