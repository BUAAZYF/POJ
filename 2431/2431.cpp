#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

using namespace std;

const int MAXN = 10005;

int N, L, P, i, pos, ans;
pair<int, int> stops[MAXN];
priority_queue<int> pq;

int main() {
    scanf("%d", &N);
    for (i = 0; i < N; ++i) scanf("%d%d", &stops[i].first, &stops[i].second);
    scanf("%d%d", &L, &P);
    for (i = 0; i < N; ++i) stops[i].first = L - stops[i].first;
    sort(stops, stops + N);
    i = pos = 0;
    while (pos + P < L) {
        while (i < N && pos + P >= stops[i].first) {
            pq.push(stops[i].second);
            ++i;
        }
        if (pq.empty()) break;
        pos += P;
        P = pq.top();
        pq.pop();
        ++ans;
    }

    printf("%d\n", pos + P >= L ? ans : -1);

    return 0;
}