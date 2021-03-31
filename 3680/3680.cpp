#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAXN = 250;
const int MAXV = 500;
const int INF = 0x3f3f3f3f;

int min(int a, int b) {
    return a <= b ? a : b;
}

int max(int a, int b) {
    return a >= b ? a : b;
}

struct edge {
    int to, cap, cost, rev;
};

int T, N, K, M, V, ans;
vector<edge> graph[MAXV];
int h[MAXV], dis[MAXV], prevv[MAXV], preve[MAXV];

struct {
    int a, b, w;
} intervals[MAXN];

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
        scanf("%d%d", &N, &K);
        vector<int> x;
        for (int i = 0; i < N; ++i) {
            scanf("%d%d%d", &intervals[i].a, &intervals[i].b, &intervals[i].w);
            x.push_back(intervals[i].a);
            x.push_back(intervals[i].b);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        M = x.size();
        int s = M, t = s + 1;
        V = t + 1;
        for (int i = 0; i < V; ++i) graph[i].clear();
        ans = 0;
        add_edge(s, 0, K, 0);
        add_edge(M - 1, t, K, 0);
        for (int i = 0; i + 1 < M; ++i) add_edge(i, i + 1, INF, 0);
        for (int i = 0; i < N; ++i) {
            int u = find(x.begin(), x.end(), intervals[i].a) - x.begin();
            int v = find(x.begin(), x.end(), intervals[i].b) - x.begin();
            add_edge(v, u, 1, intervals[i].w);
            add_edge(s, v, 1, 0);
            add_edge(u, t, 1, 0);
            ans -= intervals[i].w;
        }
        ans += min_cost_flow(s, t, N + K);
        printf("%d\n", -ans);
    }

    return 0;
}