#include <algorithm>
#include <bitset>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int MAXN = 1005;
const int MAXP = 10005;

int N, P, K, x, y, len, ans, edges[MAXP];
vector<Pr> graph[MAXN];

bool check(int bound) {
    bitset<MAXN> used;
    priority_queue<Pr> pq;
    pq.push(make_pair(K, 1));
    int node, free;
    while (!pq.empty()) {
        int node = pq.top().second, free = pq.top().first;
        pq.pop();
        if (used[node]) continue;
        used[node] = true;
        if (node == N) return true;
        for (int i = 0; i < graph[node].size(); ++i) {
            if (!used[graph[node][i].first]) {
                if (graph[node][i].second <= bound) pq.push(make_pair(free, graph[node][i].first));
                else if (graph[node][i].second > bound && free > 0) pq.push(make_pair(free - 1, graph[node][i].first));
            }
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d%d", &N, &P, &K) != EOF) {
        edges[0] = 0;
        for (int i = 1; i <= N; ++i) graph[i].clear();
        for (int i = 0; i < P; ++i) {
            scanf("%d%d%d", &x, &y, &len);
            graph[x].push_back(make_pair(y, len));
            graph[y].push_back(make_pair(x, len));
            edges[i + 1] = len;
        }
        sort(edges, edges + P + 1);
        ans = -1;
        int low = 0, high = P, mid;
        while (low <= high) {
            mid = (low + high) >> 1;
            if (check(edges[mid])) {
                if (ans == -1 || ans > mid) ans = mid;
                high = mid - 1;
            } else low = mid + 1;
        }
        printf("%d\n", ans == -1 ? -1 : edges[ans]);
    }

    return 0;
}