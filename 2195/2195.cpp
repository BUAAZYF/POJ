#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAX = 205;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int inline abs(int a) {
    return a >= 0 ? a : -a;
}

struct edge {
    int to, cap, cost, rev;
};

int N, M, n, V;
char c;
vector<Pr> man, house;
vector<edge> graph[MAX];
int h[MAX], dis[MAX], prevv[MAX], preve[MAX];

void add_edge(int from, int to, int cap, int cost) {
    graph[from].push_back(edge{to, cap, cost, graph[to].size()});
    graph[to].push_back(edge{from, 0, -cost, graph[from].size() - 1});
}

int cal_distance(Pr& p1, Pr& p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void build_graph() {
    for (int i = 0; i < V; ++i) graph[i].clear();
    int s = 0, t = V - 1;
    for (int i = 1; i <= n; ++i) add_edge(s, i, 1, 0);
    for (int j = 1; j <= n; ++j) add_edge(n + j, t, 1, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) add_edge(i + 1, n + j + 1, 1, cal_distance(man[i], house[j]));
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
    while (scanf("%d%d\n", &N, &M) != EOF && N) {
        man.clear();
        house.clear();
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                c = getchar();
                if (c == 'm') man.push_back(make_pair(i, j));
                else if (c == 'H') house.push_back(make_pair(i, j));
            }
            getchar();
        }
        n = man.size(), V = 2 * n + 2;
        build_graph();
        printf("%d\n", min_cost_flow(0, V - 1, n));
    }

    return 0;
}