#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 5010;
const int INF = 1010;

typedef pair<int, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to, cap, cost, rev;
};

int N, K, V;
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
        fill(dis, dis + V, INF * INF);
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
    while (scanf("%d%d", &N, &K) != EOF && N) {
        V = N * N * 2 + 2;
        int s = V - 2, t = V - 1, cost, shift = N * N;
        for (int i = 0; i < V; ++i) graph[i].clear();
        add_edge(s, 0, K, INF);
        add_edge(N * N * 2 - 1, t, K, INF);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                scanf("%d", &cost);
                if (cost != 0) add_edge(i * N + j, shift + i * N + j, 1, INF - cost);
                add_edge(i * N + j, shift + i * N + j, K, INF);
                if (i + 1 < N) add_edge(shift + i * N + j, (i + 1) * N + j, K, INF);
                if (j + 1 < N) add_edge(shift + i * N + j, i * N + j + 1, K, INF);
            }
        }
        printf("%d\n", K * (4 * N - 1) * INF - min_cost_flow(s, t, K));
    }

    return 0;
}