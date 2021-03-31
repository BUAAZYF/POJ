#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int MAXN = 105;
const int MAXV = 210;
const int INF = 0x3f3f3f3f;

typedef pair<int, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline abs(int a) {
    return a >= 0 ? a : -a;
}

struct edge {
    int to, cap, cost, rev;
};

struct point {
    int x, y;
};

int N, M, V, F, C, cost, cap;
point buildings[MAXN], shelters[MAXN];
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
    while (scanf("%d%d", &N, &M) != EOF) {
        V = N + M + 2;
        int s = 0, t = V - 1;
        for (int i = 0; i < V; ++i) graph[i].clear();
        F = 0;
        for (int i = 1; i <= N; ++i) {
            scanf("%d%d%d", &buildings[i].x, &buildings[i].y, &cap);
            add_edge(s, i, cap, 0);
            F += cap;
        }
        for (int j = 1; j <= M; ++j) {
            scanf("%d%d%d", &shelters[j].x, &shelters[j].y, &cap);
            add_edge(N + j, t, cap, 0);
        }
        C = 0;
        for (int i = 1; i <= N; ++i) {
            for (int j = 1; j <= M; ++j) {
                scanf("%d", &cap);
                cost = abs(buildings[i].x - shelters[j].x) + abs(buildings[i].y - shelters[j].y) + 1;
                C += cost * cap;
                add_edge(i, N + j, INF, cost);
            }
        }
        if (min_cost_flow(s, t, F) < C) {
            printf("SUBOPTIMAL\n");
            for (int i = 1; i <= N; ++i)
                for (int j = 1; j <= M; ++j) printf("%d%c", graph[N + j][i].cap, j == M ? '\n' : ' ');
        } else
            printf("OPTIMAL\n");
    }
    return 0;
}