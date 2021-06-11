#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

const int MAX = 805;
const int INF = 0x3f3f3f3f;

int inline min(int a, int b) {
    return a <= b ? a : b;
}
struct edge {
    int to, cap, rev;
};

int n, m, p, V;
string dev, tp, tp1[MAX], tp2[MAX];
vector<edge> graph[MAX];
int level[MAX], iter[MAX];

void add_edge(int from, int to, int cap) {
    graph[from].push_back(edge{to, cap, graph[to].size()});
    graph[to].push_back(edge{from, 0, graph[from].size() - 1});
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
    map<string, int> plugs, devices, idxs;
    set<string> types;
    while (scanf("%d", &n) != EOF) {
        plugs.clear(), devices.clear(), types.clear();
        while (n--) {
            cin >> tp;
            types.insert(tp);
            if (plugs.find(tp) == plugs.end()) plugs[tp] = 1;
            else ++plugs[tp];
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            cin >> dev >> tp;
            types.insert(tp);
            if (devices.find(tp) == devices.end()) devices[tp] = 1;
            else ++devices[tp];
        }
        scanf("%d", &p);
        for (int i = 0; i < p; ++i) {
            cin >> tp1[i] >> tp2[i];
            types.insert(tp1[i]);
            types.insert(tp2[i]);
        }
        n = types.size();
        V = n * 2 + 2;
        int s = V - 2, t = V - 1;
        for (int i = 0; i < V; ++i) graph[i].clear();
        for (int i = 0; i < n; ++i) add_edge(i, i + n, INF);
        int i = 0;
        for (set<string>::iterator it = types.begin(); it != types.end(); ++it, ++i) {
            idxs[*it] = i;
            if (plugs.find(*it) != plugs.end()) add_edge(s, i, plugs[*it]);
            if (devices.find(*it) != devices.end()) add_edge(i + n, t, devices[*it]);
        }
        for (int i = 0; i < p; ++i) add_edge(idxs[tp2[i]], idxs[tp1[i]], INF);
        printf("%d\n", m - max_flow(s, t));
    }

    return 0;
}