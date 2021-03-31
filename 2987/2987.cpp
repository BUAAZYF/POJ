#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;
const int MAXV = 5010;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll min(ll a, ll b) {
    return a <= b ? a : b;
}

ll max(ll a, ll b) {
    return a >= b ? a : b;
}

struct edge {
    int to;
    ll cap;
    int rev;
};

int N, M, V, a, b, cnt;
ll w, W, ans;
vector<edge> graph[MAXV];
int level[MAXV], iter[MAXV];
bool visited[MAXV];

void add_edge(int from, int to, ll cap) {
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
            if (e.cap > 0 && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

ll dfs(int v, int t, ll f) {
    if (v == t) return f;
    for (int& i = iter[v]; i < graph[v].size(); ++i) {
        edge& e = graph[v][i];
        if (e.cap > 0 && level[v] < level[e.to]) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t) {
    ll flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        ll f;
        while ((f = dfs(s, t, INF)) > 0) flow += f;
    }
}

void cntleft(int v) {
    ++cnt;
    visited[v] = true;
    for (int i = 0; i < graph[v].size(); ++i) {
        const edge& e = graph[v][i];
        if (e.cap > 0 && !visited[e.to]) cntleft(e.to);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    int s = 0, t = N + 1;
    V = t + 1;
    for (int i = 1; i <= N; ++i) {
        scanf("%lld", &w);
        if (w > 0) {
            W += w;
            add_edge(s, i, w);
        } else add_edge(i, t, -w);
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &a, &b);
        add_edge(a, b, INF);
    }
    ans = W - max_flow(s, t);
    cnt = 0;
    memset(visited, false, sizeof(visited));
    cntleft(s);
    printf("%d %lld\n", --cnt, ans);

    return 0;
}