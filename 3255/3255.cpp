#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> Pr;

const int INF = 0x3f3f3f3f;
const int MAX = 5005;

int N, R, a, b, d;
vector<Pr> edges[MAX];
int mindis[MAX], seconddis[MAX];
priority_queue<Pr, vector<Pr>, greater<Pr> > pq;

int main() {
    scanf("%d%d", &N, &R);
    fill(mindis, mindis + N + 1, INF);
    fill(seconddis, seconddis + N + 1, INF);
    for (int i = 0; i < R; ++i) {
        scanf("%d%d%d", &a, &b, &d);
        edges[a].push_back(Pr(b, d));
        edges[b].push_back(Pr(a, d));
    }
    mindis[1] = 0;
    pq.push(Pr(0, 1));
    while (!pq.empty()) {
        Pr p = pq.top();
        pq.pop();
        int v = p.second, d = p.first;
        if (seconddis[v] < d) continue;
        for (int i = 0; i < edges[v].size(); ++i) {
            Pr& edge = edges[v][i];
            int v2 = edge.first, d2 = edge.second + d;
            if (mindis[v2] > d2) {
                swap(mindis[v2], d2);
                pq.push(Pr(mindis[v2], v2));
            }
            if (seconddis[v2] > d2 && mindis[v2] < d2) {
                seconddis[v2] = d2;
                pq.push(Pr(seconddis[v2], v2));
            }
        }
    }
    printf("%d\n", seconddis[N]);

    return 0;
}