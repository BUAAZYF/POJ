#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 6005;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

struct edge {
    int to, cap, cost, rev;
};

int N, M, K, V;
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
        V = 2 + N + M + N * K + M * K;
        int s = 0, t = V - 1, flow = 0, f;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 1; i <= N; ++i) add_edge(s, i, INF, 0);
        for (int i = N + 1; i <= N + M; ++i) add_edge(i, t, INF, 0);
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= K; ++j) {
                scanf("%d", &f);
                flow += f;
                if (f > 0) add_edge(i, N + M + (i - 1) * K + j, f, 0);
            }
        }
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= K; ++j) {
                scanf("%d", &f);
                if (f > 0) add_edge(N + M + N * K + (i - 1) * K + j, i + N, f, 0);
            }
        }
        for (int k = 1; k <= K; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    scanf("%d", &f);
                    add_edge(N + M + K * i + k, N + M + N * K + K * j + k, INF, f);
                }
            }
        }
        printf("%d\n", min_cost_flow(0, V - 1, flow));
    }

    return 0;
}