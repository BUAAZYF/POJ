#include <algorithm>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;

const int MAXV = 50005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

typedef pair<ll, int> Pr;

int inline min(int a, int b) {
    return a <= b ? a : b;
}

int inline max(int a, int b) {
    return a >= b ? a : b;
}

int t, N, M, x, y, cost;
int weight[MAXV];
ll dis[MAXV];
vector<Pr> graph[MAXV];

void dijkstra(int s) {
    fill(dis, dis + N + 1, INF);
    dis[s] = 0;
    priority_queue<Pr, vector<Pr>, greater<Pr> > pq;
    pq.push(Pr(0, s));
    while (!pq.empty()) {
        Pr cur = pq.top();
        pq.pop();
        int v = cur.second;
        if (dis[v] < cur.first) continue;
        for (int i = 0; i < graph[v].size(); ++i) {
            Pr& e = graph[v][i];
            if (dis[e.first] > dis[v] + e.second) {
                dis[e.first] = dis[v] + e.second;
                pq.push(Pr(dis[e.first], e.first));
            }
        }
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; ++i) {
            scanf("%d", &weight[i]);
            graph[i].clear();
        }
        while (M--) {
            scanf("%d%d%d", &x, &y, &cost);
            graph[x].push_back(Pr(y, cost));
            graph[y].push_back(Pr(x, cost));
        }
        dijkstra(1);
        bool canbuild = true;
        for (int i = 2; i <= N; ++i) {
            if (dis[i] == INF) {
                canbuild = false;
                break;
            }
        }
        if (!canbuild) printf("No Answer\n");
        else {
            ll ans = 0;
            for (int i = 2; i <= N; ++i) ans += weight[i] * dis[i];
            printf("%lld\n", ans);
        }
    }

    return 0;
}