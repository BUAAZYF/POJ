#include <cstdio>
#include <queue>

using namespace std;

int main() {
    // freopen("in.txt", "r", stdin);
    int n;
    long long plank, ans = 0, x, y;
    priority_queue<long long, vector<long long>, greater<long long> > pq;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &plank);
        pq.push(plank);
    }
    while (pq.size() > 1) {
        x = pq.top();
        pq.pop();
        y = pq.top();
        pq.pop();
        ans += x + y;
        pq.push(x + y);
    }
    printf("%lld\n", ans);

    return 0;
}