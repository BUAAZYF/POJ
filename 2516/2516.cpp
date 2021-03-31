#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 210;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to, cap, cost, rev;
};

int N, M, K, V, in[MAXN][MAXN], out[MAXN][MAXN], flows[MAXN];
vector<edge> graph[MAXN];
int h[MAXN], dis[MAXN], prevv[MAXN], preve[MAXN];

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
    while (scanf("%d%d%d", &N, &M, &K) != EOF && N) {
        V = 2 + N + M;
        int s = 0, t = V - 1, flow = 0, cost, ans = 0;
        memset(flows, 0, sizeof(flows));
        for (int i = 1; i <= N; ++i)
            for (int k = 1; k <= K; ++k) {
                scanf("%d", &in[i][k]);
                flows[k] += in[i][k];
            }
        for (int i = 1; i <= M; ++i)
            for (int k = 1; k <= K; ++k) scanf("%d", &out[i][k]);
        for (int k = 1; k <= K; ++k) {
            if (ans >= 0) {
                for (int i = 0; i < V; ++i) graph[i].clear();
                for (int i = 1; i <= N; ++i) add_edge(s, i, in[i][k], 0);
                for (int i = 1; i <= M; ++i) add_edge(i + N, t, out[i][k], 0);
                for (int i = 1; i <= N; ++i) {
                    for (int j = 1; j <= M; ++j) {
                        scanf("%d", &cost);
                        add_edge(i, N + j, INF, cost);
                    }
                }
                int tmp = min_cost_flow(0, V - 1, flows[k]);
                if (tmp == -1) ans = -1;
                else ans += tmp;
            } else {
                for (int i = 1; i <= N; ++i)
                    for (int j = 1; j <= M; ++j) scanf("%d", &cost);
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}